#include "gray.h"
u8 Gray[10];
u8 HouGray[10];


void GRAY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	//前灰度初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5 | GPIO_Pin_6|GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	//后灰度初始化
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7| GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_10; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_Init(GPIOF,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1| GPIO_Pin_3| GPIO_Pin_5; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_Init(GPIOE,&GPIO_InitStructure);
} 

void Gray_Scan(void)
{	 	  
	if(GRAY1==0) Gray[0]=0;
	else				 Gray[0]=1;
	if(GRAY2==0) Gray[1]=0;
	else				 Gray[1]=1;
	if(GRAY3==0) Gray[2]=0;
	else				 Gray[2]=1;
	if(GRAY4==0) Gray[3]=0;
	else				 Gray[3]=1;
	if(GRAY5==0) Gray[4]=0;
	else				 Gray[4]=1;
	if(GRAY6==0) Gray[5]=0;
	else				 Gray[5]=1;
	if(GRAY7==0) Gray[6]=0;
	else				 Gray[6]=1;
	if(GRAY8==0) Gray[7]=0;
	else				 Gray[7]=1;


	if(HOUGRAY1==0) HouGray[0]=0;
	else				 HouGray[0]=1;
	if(HOUGRAY2==0) HouGray[1]=0;
	else				 HouGray[1]=1;
	if(HOUGRAY3==0) HouGray[2]=0;
	else				 HouGray[2]=1;
	if(HOUGRAY4==0) HouGray[3]=0;
	else				 HouGray[3]=1;
	if(HOUGRAY5==0) HouGray[4]=0;
	else				 HouGray[4]=1;
	if(HOUGRAY6==0) HouGray[5]=0;
	else				 HouGray[5]=1;
	if(HOUGRAY7==0) HouGray[6]=0;
	else				 HouGray[6]=1;
	if(HOUGRAY8==0) HouGray[7]=0;
	else				 HouGray[7]=1;
	
}







