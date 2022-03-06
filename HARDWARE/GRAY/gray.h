#ifndef __GRAY_H
#define __GRAY_H 
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
 
#define High    1
#define Low     0
 
#define HOUGRAY1		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_3) //PE4
#define HOUGRAY2 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_4)	//PE3 
#define HOUGRAY3		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_5) //PE2
#define HOUGRAY4			GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_6)	//PA0
#define HOUGRAY5 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_7) //PE4
#define HOUGRAY6 		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_8)	//PE3 
#define HOUGRAY7  		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9) //PE2
#define HOUGRAY8		GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_10)	//PA0

#define GRAYZL 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3) //PE2
#define GRAYZR 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)	//PA0


#define GRAYQL 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) //PE2
#define GRAYQR 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5)	//PA0

#define GRAY1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0) //PE4
#define GRAY2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)	//PE3 
#define GRAY3  		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) //PE2
#define GRAY4		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)	//PA0
#define GRAY5		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4) //PE4
#define GRAY6 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)	//PE3 
#define GRAY7		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PE2
#define GRAY8 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)	//PA0

#define GRAY_Start 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)	//PA0

void GRAY_Init(void);
void Gray_Scan(void);
#endif



