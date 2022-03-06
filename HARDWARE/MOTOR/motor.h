#ifndef __MOTOR_H
#define __MOTOR_H	 
#include "sys.h" 
#define Motor_Front 0
#define Motor_Back  1
#define Motor_Stop  2

#define	Motor_Left_Front_High		(GPIO_SetBits(GPIOC, GPIO_Pin_8))////IN1
#define	Motor_Left_Front_Low		(GPIO_ResetBits(GPIOC, GPIO_Pin_8))////IN1
#define	Motor_Left_Back_High		(GPIO_SetBits(GPIOG, GPIO_Pin_6))
#define	Motor_Left_Back_Low			(GPIO_ResetBits(GPIOG, GPIO_Pin_6))

#define	Motor_Right_Front_High	(GPIO_SetBits(GPIOG, GPIO_Pin_4))////IN1
#define	Motor_Right_Front_Low		(GPIO_ResetBits(GPIOG, GPIO_Pin_4))////IN1
#define	Motor_Right_Back_High		(GPIO_SetBits(GPIOC, GPIO_Pin_9))
#define	Motor_Right_Back_Low		(GPIO_ResetBits(GPIOC, GPIO_Pin_9))

void Motor_Init(void);	
void Motor_Left(u8 DIR);
void Motor_Right(u8 DIR);
void Stop(void);
void Go_Blind(u16 speed_l,u16 speed_r);
void Back_Blind(u16 speed_l,u16 speed_r); 
void Turn(u8 Dir,u16 ls,u16 rs);
void TurnAngle(u8 Dir,u8 angle);
void zuozhuan(int B,float C);
void zuozhuan_di(int B,float C);
void youzhuan(int B,float C);///90 0.3///45 0.2////срв╙
void youzhuan_di(int B,float C);///90 0.3///45 0.2////срв╙
void youzhuan_po(int B,float C);///90 0.3///45 0.2////срв╙
void zuozhuan_platform(int B,float C);
void zuozhuan_circle(int B,float C);
void zuozhuan_po(int B,float C);
void zuozhuan_high_profile(int B,float C);
//				GPIO_SetBits(GPIOB, GPIO_Pin_13);
//				GPIO_ResetBits(GPIOB, GPIO_Pin_15);
//				GPIO_SetBits(GPIOB, GPIO_Pin_14);
//				GPIO_ResetBits(GPIOB, GPIO_Pin_12);
#endif

















