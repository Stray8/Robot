#include "timer.h"
#include "delay.h" 
#include "string.h"
#include "usart.h"
#include "motor.h"
#include "led.h"
#include "variate.h"
#include "gyro.h"
#include "oled.h"

int Mode=0;
extern time Tim;
extern pid Pid;
extern flag Flag;
extern Gyro gyro;
extern float j,pwm1,pwm2,mangzou_bz;
extern u16 time_int_flag;
extern u16 pwm_val_left,pwm_val_right;

void TIM4_Init(unsigned int arr, unsigned int psc)
{
	NVIC_InitTypeDef NVIC_InitStructe;
	TIM_TimeBaseInitTypeDef TIM4_Int;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	TIM4_Int.TIM_Period=arr;
	TIM4_Int.TIM_Prescaler=psc;
	TIM4_Int.TIM_CounterMode=TIM_CounterMode_Up;
	TIM4_Int.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM4,&TIM4_Int);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
	
	NVIC_InitStructe.NVIC_IRQChannel=TIM4_IRQn;
	NVIC_InitStructe.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructe.NVIC_IRQChannelSubPriority=0x03;
	NVIC_InitStructe.NVIC_IRQChannelPreemptionPriority=0x01;
	NVIC_Init(&NVIC_InitStructe);
}

void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
	 TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	 time_int_flag=1;
	 Tim.cnt++;
	 if(mangzou_bz==0)
	   {
			  Pid.Pv=j;
			  Pid.C1ms++;
			  pwm_val_left=pwm1+Pid.OUT;
			  pwm_val_right=pwm2-Pid.OUT;
     }
		if(gyro.flag==1){GYRO_Calc();}
	}

}

void PWM_Init(void)
{		 					 
	//此部分需手动修改IO口设置
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//使能GPIOC时钟	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOC7复用为定时器3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOC7复用为定时器3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //上拉
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //初始化PC7
	  
	TIM_TimeBaseStructure.TIM_Prescaler=36-1;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=1000-1;  //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//初始化定时器3
	
	//初始化TIM Channel PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性低
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC1
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM3 OC2
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //使能TIM3在CCR1上的预装载寄存器
	
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPE使能 
 
	TIM_Cmd(TIM3, ENABLE);  //使能TIM3
////									  
} 


void Servo111_Init(unsigned int arr, unsigned int psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//使能PORTA时钟	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOA8复用为定时器1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOA8复用为定时器1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); //GPIOA8复用为定时器1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;           //GPIOA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //上拉
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //初始化PA8
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;  //20201020
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//初始化定时器1
	
	//初始化TIM1 Channel1 PWM模式	
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;//20201020	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //输出极性:TIM输出比较极性低
	TIM_OCInitStructure.TIM_OCNPolarity= TIM_OCPolarity_High;//20201020
  TIM_OCInitStructure.TIM_OCIdleState= 0x00000000U  ;//20201020    
	TIM_OCInitStructure.TIM_OCNIdleState=0x00000000U;//20201020
 
	TIM_OCInitStructure.TIM_Pulse=300;
//	TIM_SetCompare1(TIM1,CCR1_Val);// channel 1   20201020	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1 
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM1 4OC1 	
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
 	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器	
	
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);    //20201020
} 











