#include "variate.h"
#include "math.h"
#include "stdlib.h"

time Tim;
flag Flag;
pid Pid;
u16 pwm_val_left,pwm_val_right;
extern int A1;
extern u8 Gray[10];
extern int get_image_bz;
extern char rub[];
uint8_t tx1[]={0xA5,0x01,0x00, 0x00 ,0x00, 0x00 ,0x00, 0x01, 0x02, 0x5A};
uint8_t tx2[]={0xA5,0x01,0x00, 0x00 ,0x00, 0x00 ,0x00, 0x02, 0x03, 0x5A};

void Init(void)
{
 	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	delay_init(168);		
	Uart1_Init(115200);
	Uart2_Init(115200);
	GYRO_Init();
	GRAY_Init();
	KEY_Init();
	LED_Init();
	OLED_Init();
	TIM4_Init(1000-1,84-1);
	PWM_Init();
	Servo111_Init(200-1,7200-1);
	Motor_Init();
  variate_Init();
	sendbuf(USART1,tx1,10);	
	PID_Init();
	TIM_SetCompare1(TIM1,160); //对应180度   min130  max190
	TIM_SetCompare2(TIM1,160); //对应180度   min130  max190
	TIM_SetCompare3(TIM1,160); //对应180度   min130  max190
}	
void variate_Init(void)
{		
	Flag.num=0;
	Flag.pid_start=0;
	Flag.Oled_Time=10;
	Flag.pid_cant=0;
	Flag.step=0;
	Flag.line=0;
	Flag.out=0;
	Flag.cnt=0;
	Flag.time=0;
	Flag.light=0;
	Flag.oled=0;

}
void Scan(void)
{
	Gray_Scan();
	Key_Scan();
}
void Go_Step(int Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.servo=0;
	Flag.lukou=0;
	Flag.lukour=0;
	Flag.lukouqr=0;
	Flag.high_profile_Step=0;
	Flag.platform_Step=0;
	Flag.circle_Step=0;
	Flag.step=Dir;
}
void Next_Step(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.servo=0;
	Flag.lukou=0;
	Flag.lukour=0;
	Flag.lukouqr=0;
	Flag.lukouql=0;
	Flag.high_profile_Step=0;
	Flag.platform_Step=0;
	Flag.circle_Step=0;
	get_image_bz=0;
	if(Dir==1) Flag.step++;
	if(Dir==0) Flag.step--;
}
void Next_Step_platform(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	if(Dir==1) Flag.platform_Step++;
	if(Dir==0) Flag.platform_Step--;
}
void Go_Step_platform(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	Flag.platform_Step=Dir;
}
void Next_Step_circle(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	if(Dir==1) Flag.circle_Step++;
	if(Dir==0) Flag.circle_Step--;
}
void Go_Step_circle(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	Flag.circle_Step=Dir;
}
void Next_Step_high_profile(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	if(Dir==1) Flag.high_profile_Step++;
	if(Dir==0) Flag.high_profile_Step--;
}
void Go_Step_high_profile(u8 Dir)
{
	Tim.num=0;
	Tim.cnt=0;
	Flag.cnt=0;
	Flag.lukou=0;
	Flag.lukour=0;
	get_image_bz=0;
	Flag.high_profile_Step=Dir;
}
void Start(void)
{
	if(GRAY_Start==0)Stop();
	if(GRAY_Start==1)Go_Blind(100,110);
	if(gyro.x_angle>=183)pid_zhixian(1);
	if(GRAYZL==1&&GRAYZR==1){Next_Step(1);}	
}

void go_platform2(void)   //走平台
{
	switch(Flag.platform_Step)
	{
		case 0:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 1:
			pid_zhixian(0);
			if(cant)Next_Step_platform(1);
			break;
			
		case 2:
			Go_Blind(100,110);
			if(gyro.x_angle>=176&&(GRAYQL==0&&GRAYQR==0)&&Tim.num>=1&&cant&&hou_on_line){Next_Step_platform(1);}//(GRAYQL==0||GRAYQR==0)&&hou_cant(GRAYQL==1||GRAYQR==1)
			break;
			
		case 3:
			Stop();
			if(Tim.num>=2)Next_Step_platform(1);				
			break;
			
		case 4:			
			if(get_image_bz==0){sendbuf(USART1,tx2,10);}//get_image_bz=1;
			if(get_image_bz==2){Next_Step_platform(1);}
			break;			
			
		case 5:
//			Back_Blind(100,100);
//			if(Tim.cnt>=100)
				Next_Step_platform(1);			
			break;
				
		case 6:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 7:
			zuozhuan_platform(170,0.3);		
			break;
	  
		case 8:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);			
			break;

		case 9:
			Stop();	
			if(rub[0]!=0){Servo_plat();}
//			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 10:
			Go_Blind(100,100);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 11:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
	}
}
void go_platform3(void)   //走平台
{
	switch(Flag.platform_Step)
	{
		case 0:
			Stop();
			if(Tim.cnt>=30)Next_Step_platform(1);
			break;
		
		case 1:
			pid_zhixian(1);
			if(cant)Next_Step_platform(1);
			break;
			
		case 2:
			Go_Blind(100,110);
			if(gyro.x_angle>=176&&(GRAYQL==0&&GRAYQR==0)&&Tim.num>=1&&cant&&hou_on_line){Next_Step_platform(1);}//(GRAYQL==0||GRAYQR==0)&&hou_cant(GRAYQL==1||GRAYQR==1)
			break;
			
		case 3:
			Stop();
			if(rub[0]==3){Next_Step_platform(1);}
			else {Go_Step_platform(99);}			
			break;
			
		case 99:
			Stop();			
			if(Tim.cnt>=20)Go_Step_platform(13);	
			break;
			
		case 4:
			Stop();
			if(Tim.num>=3)Next_Step_platform(1);				
			break;
			
		case 5:
			if(get_image_bz==0){sendbuf(USART1,tx2,10);}//get_image_bz=1;
			if(get_image_bz==2){Next_Step_platform(1);}
			break;			
			
		case 6:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);					
			break;
				
		case 7:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 8:
			zuozhuan_platform(175,0.3);		
			break;

		case 9:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 10:
			Servo_platform();
			break;
		
		case 11:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 12:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
		
		case 13:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);					
			break;
				
		case 14:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 15:
			zuozhuan_platform(175,0.3);		
			break;

		case 16:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 17:
			Next_Step_platform(1);
			break;
		
		case 18:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 19:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
	}
}
void go_platform4(void)   //走平台
{
	switch(Flag.platform_Step)
	{
		case 0:
			Stop();
			if(Tim.cnt>=30)Next_Step_platform(1);
			break;
		
		case 1:
			pid_zhixian(1);
			if(cant)Next_Step_platform(1);
			break;
			
		case 2:
			Go_Blind(100,110);
			if(gyro.x_angle>=176&&(GRAYQL==0||GRAYQR==0)&&Tim.num>=1&&cant&&hou_on_line){Next_Step_platform(1);}//(GRAYQL==0||GRAYQR==0)&&hou_cant(GRAYQL==1||GRAYQR==1)
			break;
			
		case 3:
			Stop();	
			if(rub[0]==4){Next_Step_platform(1);}
			else {Go_Step_platform(99);}			
			break;
			
		case 99:
			Stop();			
			if(Tim.cnt>=20)Go_Step_platform(13);	
			break;
						
		case 4:
			Stop();
			if(Tim.num>=3)Next_Step_platform(1);				
			break;
			
		case 5:
			if(get_image_bz==0){sendbuf(USART1,tx2,10);}//get_image_bz=1;
			if(get_image_bz==2){Next_Step_platform(1);}
			break;		

		case 6:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);		
			break;
				
		case 7:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 8:
			zuozhuan_platform(175,0.3);		
			break;

		case 9:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 10:
			Servo_platform();
			break;
		
		case 11:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 12:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
		
		case 13:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);		
			break;
				
		case 14:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 15:
			zuozhuan_platform(175,0.3);		
			break;

		case 16:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 17:
			Next_Step_platform(1);
			break;
		
		case 18:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 19:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
	}
}
void go_platform5(void)   //走平台
{
	switch(Flag.platform_Step)
	{
		case 0:
			Stop();
			if(Tim.cnt>=40)Next_Step_platform(1);
			break;
		
		case 1:
			pid_zhixian(1);
			if(cant)Next_Step_platform(1);
			break;
			
		case 2:
			Go_Blind(100,110);
			if(gyro.x_angle>=176&&(GRAYQL==0&&GRAYQR==0)&&Tim.num>=1&&cant&&hou_on_line){Next_Step_platform(1);}//(GRAYQL==0||GRAYQR==0)&&hou_cant(GRAYQL==1||GRAYQR==1)
			break;
			
		case 3:
			Stop();
			if(rub[0]==5){Next_Step_platform(1);}
			else {Go_Step_platform(99);}			
			break;
			
		case 99:
			Stop();			
			if(Tim.cnt>=20)Go_Step_platform(13);	
			break;
						
		case 4:
			Stop();
			if(Tim.num>=3)Next_Step_platform(1);				
			break;
			
		case 5:
			if(get_image_bz==0){sendbuf(USART1,tx2,10);}//get_image_bz=1;
			if(get_image_bz==2){Next_Step_platform(1);}
			break;			
		
		case 6:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);				
			break;
		
		case 7:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 8:
			zuozhuan_platform(175,0.3);		
			break;

		case 9:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 10:
			Servo_platform();
			break;
		
		case 11:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 12:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
		
		case 13:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_platform(1);				
			break;
		
		case 14:
			Stop();
			A1=gyro.z_angle;   //当前角度
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 15:
			zuozhuan_platform(175,0.3);		
			break;

		case 16:
			Stop();
			if(Tim.cnt>=20)Next_Step_platform(1);
			break;
		
		case 17:
			Next_Step_platform(1);
			break;
		
		case 18:
			Go_Blind(100,110);			
			if(gyro.x_angle>=185)Next_Step_platform(1);
			break;
		
		case 19:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step(1);			
			break;
	}
}

void circle(void)   //////走圈
{
	switch(Flag.circle_Step)
	{
		case 0:
			pid_zhixian(2);
			if(Flag.lukou>=1)pid_zhixian(1);
			if(G1&&Flag.lukou>=1)Next_Step_circle(1);
			break;
		
		case 1:
			Turn(0,150,150);
			if(G4&&G1_cant)Next_Step_circle(1);
			break;
		////跷跷板////
		case 2:
			pid_circle(1);
			if(cant)Next_Step_circle(1);
			break;
		
		case 3:
			Go_Blind(80,80);
			if(Tim.cnt>=60)Next_Step_circle(1);
			break;
			
		case 4:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=50)Next_Step_circle(1);
			break;
			
		case 5:
			zuozhuan_circle(30,0.3);			
			break;
		
		case 6:
			Go_Blind(160,160);
			if(Tim.num>=3)Next_Step_circle(1);
			break;
		
		case 7:
			Stop();
			if(Tim.num>=2)Next_Step_circle(1);
			break;
		//出跷跷板
		case 8:
			Turn(0,150,150);
			if(G4||G5)Next_Step_circle(1);
			break;
		
		case 9:
			pid_circle(14);
			if(GRAYQL==0&&Tim.num>=2)Next_Step_circle(1);
			break;
		
		case 10:
			pid_circle(14);
			if(Tim.cnt>=200)Next_Step_circle(1);
			break;
		
		case 11:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=50)Next_Step_circle(1);
			break;
		//准备上第六个台
		case 12:
			zuozhuan_circle(85,0.6);
			break;
		
		case 13:
			Stop();
			if(Tim.cnt>=20)Next_Step_circle(1);			
			break;
		
		case 14:
			pid_zhixian(1);
			if((GRAYQL==0||GRAYQR==0)&&Tim.num>=1)Next_Step_circle(1);
			break;
		
		case 15:
			pid_zhixian(1);
			if(cant)Next_Step_circle(1);
			break;
			
		case 16:
			Go_Blind(100,110);
			get_image_bz=0;
			if(gyro.x_angle>=176&&(GRAYQL==0&&GRAYQR==0)&&Tim.num>=1&&cant&&hou_on_line){Next_Step_circle(1);}//gyro.x_angle>=176&&(GRAYQL==0||GRAYQR==0)&&hou_cant(GRAYQL==1||GRAYQR==1)
			break;
			
		case 17:
			Stop();
			if(rub[0]==6){Next_Step_circle(1);}
			else{Go_Step_circle(39);}					
			break;
			
		case 18:
			Stop();
			if(Tim.num>=3)Next_Step_circle(1);						
			break;
			
		case 19:
			if(get_image_bz==0){sendbuf(USART1,tx2,10);}//get_image_bz=1;
			if(get_image_bz==2){Next_Step_circle(1);}
			break;	
			
		case 20:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_circle(1);	
			break;

		case 21:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=50)Next_Step_circle(1);
			break;
		
		case 22:
			zuozhuan_circle(175,0.3);		
			break;

		case 23:
			Stop();
			if(Tim.cnt>=20)Next_Step_circle(1);
			break;
		
		case 60:
			Servo_circle();
			break;
		
		case 24:
			Go_Blind(100,110);
			if(gyro.x_angle>=185)Next_Step_circle(1);
			break;
		
		case 25:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Next_Step_circle(1);
			break;
		
		case 39:
			Back_Blind(100,110);
			if(Tim.cnt>=100)Next_Step_circle(1);	
			break;

		case 40:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=50)Next_Step_circle(1);
			break;
		
		case 41:
			zuozhuan_circle(175,0.3);		
			break;

		case 42:
			Stop();
			if(Tim.cnt>=20)Next_Step_circle(1);
			break;
		
		case 43:
			Go_Blind(100,110);
			if(gyro.x_angle>=185)Next_Step_circle(1);
			break;
		
		case 44:
			pid_zhixian(0);
			if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Go_Step_circle(26);
			break;
		
		case 26:
			pid_zhixian(1);
			if(cant)Next_Step_circle(1);
			break;
		
		case 27:
			Go_Blind(80,80);
			if(Tim.cnt>=100)Next_Step_circle(1);
			break;
		
		case 28:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=10)Next_Step_circle(1);
			break;
		
		case 29:
			zuozhuan_circle(100,0.6);
			break;
		
		case 30:
			pid_circle(14);
			if(GRAYQL==0)Next_Step_circle(1);			
			break;		
		
		case 31:
			Go_Blind(100,120);
			if(G1)Next_Step_circle(1);
			break;
		
		case 32:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=10)Next_Step_circle(1);
			break;
		
		case 33:
			zuozhuan_circle(20,0.8);		
			break;
		//减速带
		case 34:
			Stop();
			if(Tim.cnt>=10)Next_Step_circle(1);	
			break;
		
		case 35:
			pid_circle(0);
			if(Tim.num>=5&&GRAYZL==1&&GRAYZR==1)Next_Step_circle(1);
			break;
		
		case 36:
			pid_circle(1);
			if(G6)Next_Step_circle(1);
			break;
		
		case 37:
			pid_circle(1);
			if(Tim.num>=1&&G7)Next_Step_circle(1);
			break;
		
		case 38:
			Turn(1,180,180);
			if(Tim.cnt>=20&&(G4||G5))Next_Step(1);
			break;
	}
}

void high_profile(void)				//////高台
{
	 switch(Flag.high_profile_Step)
	 {
		case 0:
			pid_zhixian(0);
			if(GRAYQL==0||GRAYQR==0)Next_Step_high_profile(1);
			break;
		
		case 1:
			pid_zhixian(2);
			if(gyro.x_angle<=163)Next_Step_high_profile(1);
			break;
		
		case 2:
			pid_zhixian(1);
			if(gyro.x_angle>167)Next_Step_high_profile(1);
			break;
		
		case 3:
			pid_zhixian(2);
			if(GRAYQL==0||GRAYQR==0)Next_Step_high_profile(1);
			break;
		
		case 4:
			pid_zhixian(2);
			if(gyro.x_angle<=163)Next_Step_high_profile(1);
			break;
		
		case 5:
			pid_zhixian(2);
			if(cant)Next_Step_high_profile(1);	
			break;
		
		case 6:
			Go_Blind(100,110);
			get_image_bz=0;	
			if(Tim.num>=1&&gyro.x_angle>=177&&(GRAYQL==0&&GRAYQR==0)&&hou_on_line){Next_Step_high_profile(1);}
			break;
			
		case 7:
			Next_Step_high_profile(1);
//			Stop();	
//			if(rub[0]==8){Next_Step_high_profile(1);}
//			else {Go_Step_high_profile(10);}					
			break;
			
		case 8:
			Stop();
			if(Tim.cnt>=20)Go_Step_high_profile(9);	
			break;
				
		case 9:
			Next_Step_high_profile(1);
			break;
			
		case 10:
			Back_Blind(100,110);
			if(Tim.cnt>=50)Next_Step_high_profile(1);
			break;
			
		case 11:
			Stop();
			A1=gyro.z_angle;
			if(Tim.cnt>=20)Next_Step_high_profile(1);
			break;
		
		case 12:
			zuozhuan_high_profile(170,0.3);		
			break;
		
		case 13:
			Stop();
			if(Tim.cnt>=20)Next_Step_high_profile(1);
			break;
		
		case 14:
			Stop();
			if(rub[0]==8){Servo_high();}
			else {Next_Step_high_profile(1);}
			break;
		
		case 15:
			Go_Blind(70,70);
			if(gyro.x_angle>=182)Next_Step_high_profile(1);			
			break;
		//下高台
		case 16:
			pid_zhixian(9);
			if(Tim.num>=1&&gyro.x_angle>=200)Next_Step_high_profile(1);//gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1
			break;
		
		case 17:
			pid_zhixian(9);
			if(gyro.x_angle<=200)Next_Step_high_profile(1);//gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1
			break;
		
		case 18:
			pid_zhixian(0);
			if(gyro.x_angle>182)Next_Step_high_profile(1);
			break;
		
		case 19:
			pid_zhixian(9);
			if(gyro.x_angle<=181&&gyro.x_angle>175&&GRAYZL==1&&GRAYZR==1)Next_Step_high_profile(1);//gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1			
			break;
		
		case 20:
			Stop();
			if(Tim.cnt>=200)Next_Step_high_profile(1);
			break;
		
		case 21:
			pid_zhixian(0);
			if(cant)Next_Step(1);
			break;
	 }
}
void Servo(void)
{
	TIM_SetCompare2(TIM1, 180); //对应45度	
	delay_ms(400);
	TIM_SetCompare2(TIM1, 160); //对应45度	
	delay_ms(400);	
	TIM_SetCompare1(TIM1, 140); //对应45度	
	delay_ms(400);
	TIM_SetCompare1(TIM1, 160); //对应1 
	Next_Step(1);
}
void Servo_platform(void)
{
	TIM_SetCompare2(TIM1, 180); //对应45度	
	delay_ms(400);
	TIM_SetCompare2(TIM1, 160); //对应45度	
	delay_ms(400);	
	TIM_SetCompare1(TIM1, 140); //对应45度	
	delay_ms(400);
	TIM_SetCompare1(TIM1, 160); //对应1 
	Next_Step_platform(1);
}
void Servo_high(void)
{
	TIM_SetCompare2(TIM1, 180); //对应45度	
	delay_ms(400);
	TIM_SetCompare2(TIM1, 160); //对应45度	
	delay_ms(400);	
	TIM_SetCompare1(TIM1, 140); //对应45度	
	delay_ms(400);
	TIM_SetCompare1(TIM1, 160); //对应1 
	Next_Step_high_profile(1);
}
void Servo_circle(void)
{
	TIM_SetCompare2(TIM1, 180); //对应45度	
	delay_ms(400);
	TIM_SetCompare2(TIM1, 160); //对应45度	
	delay_ms(400);	
	TIM_SetCompare1(TIM1, 140); //对应45度	
	delay_ms(400);
	TIM_SetCompare1(TIM1, 160); //对应1 
	Go_Step_circle(24);
}
void Servo_scene(void)
{
	TIM_SetCompare1(TIM1, 148); //对应45度	
	TIM_SetCompare2(TIM1, 170); //对应45度	
	delay_ms(400);
}
void Servo_return(void)
{
	TIM_SetCompare1(TIM1, 160); //对应45度	
	TIM_SetCompare2(TIM1, 160); //对应45度	
	delay_ms(400);
}
void Servo_plat(void)
{
		TIM_SetCompare3(TIM1,130); //对应180度   min130  max190
		delay_ms(400);
		TIM_SetCompare3(TIM1,190); //对应180度   min130  max190
		delay_ms(400);
		TIM_SetCompare3(TIM1,160); //对应180度   min130  max190				
		Next_Step_platform(1);		
}
