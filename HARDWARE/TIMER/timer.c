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
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);  	//TIM3ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); 	//ʹ��GPIOCʱ��	
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3); //GPIOC7����Ϊ��ʱ��3
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM3); //GPIOC7����Ϊ��ʱ��3
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;           //GPIOC7
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOC,&GPIO_InitStructure);              //��ʼ��PC7
	  
	TIM_TimeBaseStructure.TIM_Prescaler=36-1;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=1000-1;  //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);//��ʼ����ʱ��3
	
	//��ʼ��TIM Channel PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
	
	TIM_OC1Init(TIM3,&TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC1
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM3 OC2
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
	
  TIM_ARRPreloadConfig(TIM3,ENABLE);//ARPEʹ�� 
 
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3
////									  
} 


void Servo111_Init(unsigned int arr, unsigned int psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_11|GPIO_Pin_13;           //GPIOA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PA8
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;  //20201020
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	//��ʼ��TIM1 Channel1 PWMģʽ	
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;//20201020	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCNPolarity= TIM_OCPolarity_High;//20201020
  TIM_OCInitStructure.TIM_OCIdleState= 0x00000000U  ;//20201020    
	TIM_OCInitStructure.TIM_OCNIdleState=0x00000000U;//20201020
 
	TIM_OCInitStructure.TIM_Pulse=300;
//	TIM_SetCompare1(TIM1,CCR1_Val);// channel 1   20201020	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1 
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1 	
	
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
 	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���	
	
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);    //20201020
} 











