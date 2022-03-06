#include "key.h"
#include "delay.h" 
#include "variate.h" 
extern flag Flag;
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA,GPIOE时钟
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOE2,3,4
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化GPIOE2,3,4
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode) key_up=1;  //支持连按		  
	if(key_up&&(Key1==0||Key2==0||Key3==0||Key4==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
				 if(Key1==0)return 1;
		else if(Key2==0)return 2;
		else if(Key3==0)return 3;
		else if(Key4==0)return 4;
	}	else if(Key1==1&&Key2==1&&Key3==1&&Key4==1)key_up=1; 	    
										return 0;// 无按键按下
}

void Key_Scan(void)
{	 
		int Key=0;
		Key=KEY_Scan(0);
		if(Key==1) 	Next_Step(1);
		if(Key==2) 	{if(Flag.oled==0)Flag.oled=1;else if(Flag.oled==1)Flag.oled=0; OLED_Clear();}
		if(Key==3) {Flag.voice_choose++;if(Flag.voice_choose==8)Flag.voice_choose=1;Flag.voice=1;}
		if(Key==4) OLED_Init();
}










