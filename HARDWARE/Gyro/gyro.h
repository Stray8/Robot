#ifndef __GYRO_H
#define __GYRO_H	
#include "sys.h"

typedef struct 
{
	u16 z_high;
	u16 z_low;
	s16 z_angle;
	u16 y_high;
	u16 y_low;
	s16 y_angle;
	u16 x_high;
	u16 x_low;
	s16 x_angle;
  u16 flag;
}Gyro;
	

extern Gyro gyro;


void GYRO_Calc(void);//Õ”¬›“«º∆À„
void GYRO_Init(void);//Õ”¬›“«≥ı ºªØ


	 				    
#endif
