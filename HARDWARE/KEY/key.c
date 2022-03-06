#include "key.h"
#include "delay.h" 
#include "variate.h" 
extern flag Flag;
//������ʼ������
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//ʹ��GPIOA,GPIOEʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��GPIOA,GPIOEʱ��
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_4; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_3; //KEY0 KEY1 KEY2��Ӧ����
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//��ͨ����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOC, &GPIO_InitStructure);//��ʼ��GPIOE2,3,4
}
//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode) key_up=1;  //֧������		  
	if(key_up&&(Key1==0||Key2==0||Key3==0||Key4==0))
	{
		delay_ms(10);//ȥ���� 
		key_up=0;
				 if(Key1==0)return 1;
		else if(Key2==0)return 2;
		else if(Key3==0)return 3;
		else if(Key4==0)return 4;
	}	else if(Key1==1&&Key2==1&&Key3==1&&Key4==1)key_up=1; 	    
										return 0;// �ް�������
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










