#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F407开发板
//按键输入驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2014/5/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	 

#define Key1 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1) //PE2
#define Key2 			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_3) //PE2
#define Key3 			GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_1) //PE2
#define Key4 			GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4) //PE2
#define Key5 			GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) //PE2
//#define Key5 			GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5) //PE2
void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数		
void Key_Scan(void);
#endif
