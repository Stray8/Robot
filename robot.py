# coding:utf-8
# ! /usr/bin/env python3
"""
单应性匹配：
    两幅图像中的一幅 出现投影畸变的时候，他们还能彼此匹配
"""
import sys
import time
import cv2
import numpy as np
import threading
import math
from threading import Thread
import serial
import struct
import warnings

# 最小匹配数量设为10个， 大于这个数量从中筛选出10个最好的
MIN_MATCH_COUNT = 15
cap = cv2.VideoCapture(0)
# cap.set(cv2.CAP_PROP_FRAME_WIDTH, 200)
# cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 200)
# cap.set(cv2.CAP_PROP_BRIGHTNESS,20)
sift = cv2.xfeatures2d.SIFT_create()
mode = 2

tran_info = 1

class SerialPort(object):
    def __init__(self, port="/dev/serial0", baudrate=115200, timeout=None):
        # print('__init__')
        #超时设置,None：永远等待操作，0为立即返回请求结果，其他值为等待超时时间(单位为秒)
        self.__sp = serial.Serial(port, baudrate, timeout=timeout)
        self.__sendDict = {
            "_byte": [],
            "_short": [],
            "_int": [],
            "_float": [],
            "_longlong": [],
            "_double": [],
        }
        self.__receiveDict = {
            "byte": [],
            "short": [],
            "int": [],
            "float": [],
            "long long": [],
            "double": [],
        }
    
    def __enter__(self):
        # print('__enter__')
        return self

    def __exit__(self, _type, _value, _trace):
        # print('__exit__', _type, _value, _trace)
        if self.__sp.is_open:
            self.__sp.close()

    def __clearReceiveBuffer(self):
        for buf in self.__receiveDict.values():
            buf.clear()

    def clearBuffer(self):
        for buf in self.__sendDict.values():
            buf.clear()

    def setData(self, **vardict):
        for key, value in vardict.items():
            if type(value) in [list, tuple]:
                if self.__sendDict.get(key, None) != None:
                    self.__sendDict[key] = value
                else:
                    warnings.warn(f"wrong key: {key}")
            else:
                if self.__sendDict.get(key, None) != None:
                    self.__sendDict[key] = [value]
                else:
                    warnings.warn(f"wrong key: {key}")

    def appendData(self, **vardict):
        for key, value in vardict.items():
            if type(value) in [list, tuple]:
                if self.__sendDict.get(key, None) != None:
                    self.__sendDict[key].extend(value)
                else:
                    warnings.warn(f"wrong key: {key}")
            else:
                if self.__sendDict.get(key, None) != None:
                    self.__sendDict[key].append(value)
                else:
                    warnings.warn(f"wrong key: {key}")

    def getReceive(self):
        return self.__receiveDict

    def sendData(self, **vardict):
        if vardict:
            self.clearBuffer()
            self.setData(**vardict)
        # 包头
        _message = b'\xa5'
        # 数据数量
        lByte = len(self.__sendDict["_byte"])
        lShort = len(self.__sendDict["_short"])
        lInt = len(self.__sendDict["_int"])
        lFloat = len(self.__sendDict["_float"])
        lLongLong = len(self.__sendDict["_longlong"])
        lDouble = len(self.__sendDict["_double"])
        # 数据格式
        _message += struct.pack('BBBBBB', lByte, lShort, lInt, lFloat, lLongLong, lDouble)
        _format = '>' + 'B'*lByte + 'h'*lShort + 'i'*lInt + 'f'*lFloat + 'q'*lLongLong + 'd'*lDouble
        # 数据本体
        tmpList = [value for key, values in self.__sendDict.items() if values for value in values]
        _message += struct.pack(_format, *tmpList)
        # 校验和
        checksum = sum(_message[1:])
        _message += struct.pack('B', checksum%256)
        # 包尾 
        _message += b'\x5a'
        # 发送数据
        self.__sp.write(_message)

    def receiveData(self):
        bt = self.__sp.read()
        #print(bt.hex())
        # 检测包头
        if bt != b'\xa5':
            return False
        # 获取数据数量
        _message = self.__sp.read(6)
        num = sum(map((lambda x, y: x*y), [1, 2, 4, 4, 8, 8], _message))
        # 获取数据本体
        _message += self.__sp.read(num)
        # 检测校验和
        checksum = struct.pack('B', sum(_message)%256)
        if checksum == self.__sp.read():
            # 检测包尾
            bw = self.__sp.read()
            if bw == b'\x5a':
                # 解包数据数量
                lByte, lShort, lInt, lFloat, lLongLong, lDouble = struct.unpack('BBBBBB', _message[:6])
                # 清空接收缓存
                self.__clearReceiveBuffer()
                # 解包数据本体
                _format = '>' + 'B'*lByte + 'h'*lShort + 'i'*lInt + 'f'*lFloat + 'q'*lLongLong + 'd'*lDouble
                receiveUnpack = struct.unpack(_format, _message[6:])
                receiveUnpack=list(reversed(receiveUnpack))
                # print(receiveUnpack)
                # 将解包后的数据填入接收缓存
                if lByte:
                    while lByte:
                        self.__receiveDict["byte"].append(receiveUnpack.pop())
                        lByte -= 1
                if lShort:
                    while lShort:
                        self.__receiveDict["short"].append(receiveUnpack.pop())
                        lShort -= 1
                if lInt:
                    while lInt:
                        self.__receiveDict["int"].append(receiveUnpack.pop())
                        lInt -= 1
                if lFloat:
                    while lFloat:
                        self.__receiveDict["float"].append(receiveUnpack.pop())
                        lFloat -= 1
                if lLongLong:
                    while lLongLong:
                        self.__receiveDict["long long"].append(receiveUnpack.pop())
                        lLongLong -= 1
                if lDouble:
                    while lDouble:
                        self.__receiveDict["double"].append(receiveUnpack.pop())
                        lDouble -= 1
                return True
        return False
        
        
def load_model():
    des = np.array([np.load('/home/pi/Desktop/workspace/tz1.npy'), np.load('/home/pi/Desktop/workspace/tz2.npy'), np.load('/home/pi/Desktop/workspace/tz3.npy'), np.load('/home/pi/Desktop/workspace/tz4.npy'), np.load('/home/pi/Desktop/workspace/tz5.npy'),
                    np.load('/home/pi/Desktop/workspace/tz6.npy')])
    kp = np.array([np.load('/home/pi/Desktop/workspace/kp1.npy'), np.load('/home/pi/Desktop/workspace/kp2.npy'), np.load('/home/pi/Desktop/workspace/kp3.npy'), np.load('/home/pi/Desktop/workspace/kp4.npy'), np.load('/home/pi/Desktop/workspace/kp5.npy'),
                   np.load('/home/pi/Desktop/workspace/kp6.npy')])
    kp1 = []
    kp2 = []
    for j in range(6):
        if j > 0:
            kp2.append(kp1)
            kp1 = []
        for i in range(len(kp[j])):
            temp = cv2.KeyPoint(x=kp[j][i][0], y=kp[j][i][1], _size=kp[j][i][2], _angle=kp[j][i][3],
                                _response=kp[j][i][4], _octave=int(kp[j][i][5]), _class_id=int(kp[j][i][6]))
            kp1.append(temp)
    kp2.append(kp1)
    kp1 = []
    return des, kp2


def recognition_image(ret, img, des, kp, mode):
    global tran_info
    # 读入两幅图片 图片中有相同部分
    # ret, img2 = cap.read(cv2.IMREAD_GRAYSCALE)

    # img = cv2.imread("C:/Users/20863/Desktop/robot/3/0.jpg", cv2.IMREAD_GRAYSCALE)

    # 获取sift特征检测器

    # 检测关键点 计算描述符

    kp2, des2 = sift.detectAndCompute(img, None)
    result =[]
    # print(len(kp2))
    # kdtree建立索引方式的常量参数
    if len(kp2) > 20:
        FLANN_INDEX_KDTREE = 0
        index_params = dict(algorithm=FLANN_INDEX_KDTREE, trees=5)
        search_params = dict(checks=5)  # checks指定索引树要被遍历的次数
        flann = cv2.FlannBasedMatcher(index_params, search_params)
        # 进行匹配搜索
        y = 0
        x = 0
        count = []
        num = []
        for i in range(6):
            matches = flann.knnMatch(des[i], des2, k=2)
            good = []
            for m, n in matches:
                if m.distance < 0.6 * n.distance:
                    good.append(m)
            # 如果足够多  就筛选
            if len(good) > MIN_MATCH_COUNT:
                # print(len(good))
                # # 通过距离近的描述符 找到两幅图片的关键点
                #  kp3=kp2[i]
                # print(i)
                src_pts = np.float32([kp[i][m.queryIdx].pt for m in good]).reshape(-1, 1, 2)
                dst_pts = np.float32([kp2[m.trainIdx].pt for m in good]).reshape(-1, 1, 2)
                # 单应性匹配图关键点匹配线。。不懂啥意思
                M, mask = cv2.findHomography(src_pts, dst_pts, cv2.RANSAC, 2.0)
                # print(type(M))
                # matchesMask = mask.ravel().tolist()

                # h, w = img1.shape
                if M is not None and mode == 2:
                    h = 200
                    w = 200
                    # print(len(good))
                    # 计算第二张图相对于第一张图的畸变
                    pts = np.float32([[30, 20], [30, h + 20], [w + 30, 20]]).reshape(-1, 1, 2)
                    dst = cv2.perspectiveTransform(np.float32(pts), np.float32(M))
                    x = (dst[1][0][0] + dst[2][0][0]) / 2
                    y = (dst[1][0][1] + dst[2][0][1]) / 2
                    r = math.sqrt(
                        math.pow((dst[1][0][0] - dst[2][0][0]), 2) + math.pow((dst[1][0][1] - dst[2][0][1]), 2))
                    img2 = cv2.circle(img, (int(x), int(y)), int(r / 2), (255, 0, 0), 3)
                    count.append(len(good))
                    num.append(i + 3)
        if len(count) > 0:
            image_number = num[np.argmax(count)]
            # print('匹配特征数:')
            # print(max(count))
            # print('图像号码为:')
            #print(image_number)
            #print(type(image_number))
            img = cv2.putText(img, str(image_number), (int(x), int(y)), cv2.FONT_HERSHEY_SIMPLEX, 1 * r / 200,
                              (255, 255, 255), 2)  # 添加文字，1.2表示字体大小，（0,40）是初始的位置，(255,255,255)表示颜色，2表示粗细
            # t = [int(c) for c in image_number]
            
            #sp.sendData(_byte=image_number)
            tran_info = image_number
            print(image_number)
        else:
            img = cv2.putText(img, 'nothing', (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255),
                              2)  # 添加文字，1.2表示字体大小，（0,40）是初始的位置，(255,255,255)表示颜色，2表示粗细
            #sp.sendData(_byte=1)
            tran_info = 1
            print(1)
    else:
        # print('无匹配图像')
        img = cv2.putText(img, 'nothing', (10, 50), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255),
                          2)  # 添加文字，1.2表示字体大小，（0,40）是初始的位置，(255,255,255)表示颜色，2表示粗细
        #sp.sendData(_byte=1)    
        tran_info = 1
        print(1)

def detect():
    des, kp = load_model()
    
    while True:
        ret, frame = cap.read()

        if ret != 0:
            frame = cv2.resize(frame, (320, 240), interpolation=cv2.INTER_CUBIC)
            recognition_image(ret, frame, des, kp, mode)
            cv2.imshow("img",frame)
            cv2.waitKey(1)


def main():
    global tran_info
    with SerialPort() as sp:
        while True:
            if sp.receiveData():
                try:
                    detect_type = sp.getReceive()['byte'][0]
                    #print(detect_type)
                    if detect_type == 2:
                        sp.sendData(_byte=tran_info)
                except:
                    pass
                    
                  
if __name__ == '__main__':
    task_detect = Thread(target=detect)
    task_serial = Thread(target=main)
    task_detect.start()
    task_serial.start()
