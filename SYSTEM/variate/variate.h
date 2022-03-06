#ifndef __VARIATE_H
#define __VARIATE_H	
#include "sys.h" 
#include "servo.h"
#include "gray.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "key.h"
#include "led.h"
#include "oled.h"
#include "motor.h"
#include "timer.h"
#include "pid.h"
#include "gyro.h"

#define low		 0
#define high	 1
#define right	 0
#define left	 1
#define back	 1
#define come	 0
#define off 	 0

void Start(void);
void variate_Init(void);
void Init(void);
void Scan(void);
void Next_Step(u8 Dir);
void Next_Step_high_profile(u8 Dir);
void Next_Step_circle(u8 Dir);
void Next_Step_platform(u8 Dir);
void go_platform(void);
void circle(void);
void high_profile(void);
void Go_Step(int Dir);
void Servo(void);
void Servo_circle(void);
void Servo_high(void);
void Servo_platform(void);
void Servo_scene(void);
void Servo_return(void);
void Go_Step_high_profile(u8 Dir);
void Go_Step_circle(u8 Dir);
void Go_Step_platform(u8 Dir);
void go_platform2(void);   //走平台
void go_platform3(void);   //走平台
void go_platform4(void);   //走平台
void go_platform5(void);   //走平台
void Servo_plat(void);
typedef struct Time
{
	int Flag;
	int cnt;
	int num;
}	time;
typedef struct Flag
{
	int start;         //
	int stop;
	int num;
	int Oled_Time;	
	int pid_start;
	int pid_cant;
	int step;
	int voice;
	int voice_choose;
	int start_judge;
	int line;
	int out;
	int cnt;
	int white;
	int black;
	int time;
	int light;
	int servo;
	int dmp;
	int target;
	int oled;
	int type;
	int cat;
	int image;
	int lukou;
	int lukour;
	int lukouqr;
	int platform_Step;
	int high_profile_Step;
	int circle_Step;
	int lukouql;
}	flag;
typedef struct Pid
{
	float Sv;     // 设定值
	float Pv;
	float Kp;
	float T;
	float Ti;
	float Td;
	float Ek;   //本次偏差
	float dkp;
	float dki;
	float dkd;
	
	float Ek_1;   //上次偏差
	float SEK;    //历史偏差之和
	float OUT0;
	float OUT;
	float pwmcycle;
	u16 C1ms;
}	pid;
typedef struct Receive
{
	int  type;
	int  area;
}	receive;


#endif





