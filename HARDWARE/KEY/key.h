#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//����������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define Key1 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //PE2
#define Key2 			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) //PE2
#define Key3 			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) //PE2
#define Key4 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //PE2
#define Key5 			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) //PE2
//#define Key5 			GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5) //PE2
void KEY_Init(void);	//IO��ʼ��
u8 KEY_Scan(u8);  		//����ɨ�躯��		
void Key_Scan(void);
#endif
