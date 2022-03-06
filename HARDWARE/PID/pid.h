#ifndef __PID_H
#define __PID_H 
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"

extern u8 Gray[10]; 
extern u8 HouGray[10]; 


void pid_zhixian(u8 run_d);
void Pid_Calc(void);
void Pid_Calc1(void);
void panduan(void);
void PID_Init(void);
void line(int mode);
void pid_circle(u8 run_d);

#define all  			Gray[0]==0&&Gray[1]==0&&Gray[2]==0&&Gray[3]==0&&Gray[4]==0&&Gray[5]==0&&Gray[6]==0&&Gray[7]==0
#define hou_all  			HouGray[0]==0&&HouGray[1]==0&&HouGray[2]==0&&HouGray[3]==0&&HouGray[4]==0&&HouGray[5]==0&&HouGray[6]==0&&HouGray[7]==0
#define can 			Gray[0]==0||Gray[1]==0||Gray[2]==0||Gray[3]==0||Gray[4]==0||Gray[5]==0||Gray[6]==0||Gray[7]==0
#define hou_can 			HouGray[0]==0||HouGray[1]==0||HouGray[2]==0||HouGray[3]==0||HouGray[4]==0||HouGray[5]==0||HouGray[6]==0||HouGray[7]==0
#define cant			Gray[0]==1&&Gray[1]==1&&Gray[2]==1&&Gray[3]==1&&Gray[4]==1&&Gray[5]==1&&Gray[6]==1&&Gray[7]==1
#define hou_cant			HouGray[0]==1&&HouGray[1]==1&&HouGray[2]==1&&HouGray[3]==1&&HouGray[4]==1&&HouGray[5]==1&&HouGray[6]==1&&HouGray[7]==1
#define hou_on_line HouGray[0]+HouGray[1]+HouGray[2]+HouGray[3]+HouGray[4]+HouGray[5]+HouGray[6]+HouGray[7]<=4

#define HG23 			HouGray[1]==0&&HouGray[2]==0
#define HG34  		HouGray[2]==0&&HouGray[3]==0
#define HG12  		HouGray[0]==0&&HouGray[1]==0
#define HG4  			HouGray[3]==0
#define HG1  			HouGray[0]==0
#define HG8  			HouGray[7]==0
#define HG7  			HouGray[6]==0
#define HG6  			HouGray[5]==0
#define HG5  			HouGray[4]==0
#define HG4  			HouGray[3]==0
#define HG3  			HouGray[2]==0

#define G45 			Gray[3]==0&&Gray[4]==0
#define G456  		Gray[3]==0&&Gray[4]==0&&Gray[5]==0
#define G345  		Gray[2]==0&&Gray[3]==0&&Gray[4]==0
#define G45 			Gray[3]==0&&Gray[4]==0
#define G456  		Gray[3]==0&&Gray[4]==0&&Gray[5]==0
#define G345  		Gray[2]==0&&Gray[3]==0&&Gray[4]==0
#define G4  			Gray[3]==0
#define G5  			Gray[4]==0
#define G34 			Gray[2]==0&&Gray[3]==0
#define G56 			Gray[4]==0&&Gray[5]==0
#define G3 	 			Gray[2]==0
#define G6  			Gray[5]==0
#define G23  			Gray[1]==0&&Gray[2]==0
#define G67  			Gray[5]==0&&Gray[6]==0
#define G2   			Gray[1]==0
#define G7 	 			Gray[6]==0
#define G12  			Gray[0]==0&&Gray[1]==0
#define G78  			Gray[6]==0&&Gray[7]==0
#define G1  		  Gray[0]==0
#define G1_cant  		  Gray[0]==1
#define G8   			Gray[7]==0
#define on_line 	Gray[0]+Gray[1]+Gray[2]+Gray[3]+Gray[4]+Gray[5]+Gray[6]+Gray[7]>=4
#define out_line  Gray[0]+Gray[1]+Gray[2]+Gray[3]+Gray[4]+Gray[5]+Gray[6]+Gray[7]< 4
#define fencha  Gray[0]+Gray[1]+Gray[2]+Gray[3]+Gray[4]+Gray[5]+Gray[6]+Gray[7]<=6
#define location  Gray[8]+Gray[9]<=1
#define no_location  Gray[8]+Gray[9]==2



#endif










