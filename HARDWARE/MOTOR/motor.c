#include "motor.h" 
#include "variate.h" 
#include "delay.h" 
#include "key.h" 

extern int step ;
extern int Mode;
extern time Tim;
extern pid Pid;
extern flag Flag;
int A1=0,A2=0,A3=0,A4=0,A5=0,A6=0;


void Motor_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOF时钟
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOF时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure);//初始化1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化1
}
 
void Motor_Left(u8 DIR)
{
	switch(DIR)
	{
		case Motor_Front:
			Motor_Left_Front_High;
			Motor_Left_Back_Low;
		break;
			
		case Motor_Back:
			Motor_Left_Front_Low;
			Motor_Left_Back_High;			
		break;
		case Motor_Stop:
			Motor_Left_Front_Low;
			Motor_Left_Back_Low;
		break;
	}
}
void Motor_Right(u8 DIR)
{
	switch(DIR)
	{
		case Motor_Front:
			Motor_Right_Front_High;
			Motor_Right_Back_Low;
		break;
			
		case Motor_Back:
			Motor_Right_Front_Low;
			Motor_Right_Back_High;	
		break;
		case Motor_Stop:
			Motor_Right_Front_Low;
			Motor_Right_Back_Low;
		break;
	}
}
void Stop(void)
{
		Motor_Left(Motor_Stop);
		Motor_Right(Motor_Stop);
}
void Go_Blind(u16 speed_l,u16 speed_r)
{
	Motor_Left(0);
	Motor_Right(0);
	TIM_SetCompare1(TIM3,speed_l);   //右
	TIM_SetCompare2(TIM3,speed_r);   //左

	//右  左100 110   150 165   200 220
}
void Back_Blind(u16 speed_l,u16 speed_r)
{
	Motor_Left(1);
	Motor_Right(1);
	TIM_SetCompare1(TIM3,speed_l);
	TIM_SetCompare2(TIM3,speed_r);
}
void Turn(u8 Dir,u16 ls,u16 rs)
{
	switch(Dir){
		
		case left:
			Motor_Left_Front_Low;
			Motor_Left_Back_High;			
			TIM_SetCompare2(TIM3,ls);
			Motor_Right_Front_High;
			Motor_Right_Back_Low;
			TIM_SetCompare1(TIM3,rs);
		break;
		
		case right:
			Motor_Left_Front_High;
			Motor_Left_Back_Low;			
			TIM_SetCompare2(TIM3,ls);
			Motor_Right_Front_Low;
			Motor_Right_Back_High;
			TIM_SetCompare1(TIM3,rs);
		break;
	}
}

///90 0.3///45 0.2////左转
void zuozhuan(int B,float C)
{
//	if(Tim.num==0)
//	{
		 A2=A1+B;           //目标角度
		 A3=A1+C*B;         //
		 A4=A2-360;
		 A5=A3-360;
		 A6=A1+90;
//	}
//	else if(Tim.num>=1)
//	{
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,270,250);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,220,200);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step(1);}
		 else Turn(0,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,270,250);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,180,160);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(0,220,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,270,250);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,170,150);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(0,220,200);
		 } 
//	 }
	}
}
void zuozhuan_po(int B,float C)
{
//	if(Tim.num==0)
//	{
		 A2=A1+B;           //目标角度
		 A3=A1+C*B;         //
		 A4=A2-360;
		 A5=A3-360;
		 A6=A1+90;
//	}
//	else if(Tim.num>=1)
//	{
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,270,250);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,220,200);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step(1);}
		 else Turn(0,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,270,250);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,180,160);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(0,220,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,270,250);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,170,150);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(0,220,200);
		 } 
//	 }
	}
}
void zuozhuan_di(int B,float C)
{
//	if(Tim.num==0)
//	{
		 A2=A1+B;           //目标角度
		 A3=A1+C*B;         //
		 A4=A2-360;
		 A5=A3-360;
		 A6=A1+90;
//	}
//	else if(Tim.num>=1)
//	{
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,250,250);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,200,200);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step(1);}
		 else Turn(1,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,250,250);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,200,200);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,160,160);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(1,200,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,250,250);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,200,200);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,150,150);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step(1);}
			 else Turn(1,200,200);
		 } 
//	 }
	}
}
void zuozhuan_platform(int B,float C)
{
	 A2=A1+B;           //目标角度
	 A3=A1+C*B;         //
	 A4=A2-360;
	 A5=A3-360;
	 A6=A1+90;
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,250,270);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,200,220);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step_platform(1);}
		 else Turn(0,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,250,270);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,200,220);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,150,170);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_platform(1);}
			 else Turn(0,200,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,250,270);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,200,220);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,150,170);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_platform(1);}
			 else Turn(0,200,200);
		 } 
	}
}
void zuozhuan_high_profile(int B,float C)
{
//	if(Tim.num==0)
//	{
//		 A1=gyro.z_angle;   //当前角度
		 A2=A1+B;           //目标角度
		 A3=A1+C*B;         //
		 A4=A2-360;
		 A5=A3-360;
		 A6=A1+90;
//	}
//	else if(Tim.num>=1)
//	{
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,250,250);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,200,200);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step_high_profile(1);}
		 else Turn(0,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,250,250);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,200,200);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,160,160);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_high_profile(1);}
			 else Turn(0,200,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,250,250);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,200,200);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,150,150);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_high_profile(1);}
			 else Turn(0,200,200);
		 } 
//	 }
	}
}
void zuozhuan_circle(int B,float C)
{
//	if(Tim.num==0)
//	{
//		 A1=gyro.z_angle;   //当前角度
		 A2=A1+B;           //目标角度
		 A3=A1+C*B;         //
		 A4=A2-360;
		 A5=A3-360;
		 A6=A1+90;
//	}
//	else if(Tim.num>=1)
//	{
	 if((A1>=0)&&(A1<=359-B))
	 {
		 if(gyro.z_angle>=A1&&gyro.z_angle<=A3)
			 Turn(0,270,250);
		 else if(gyro.z_angle>=A3&&gyro.z_angle<=A2-2)
			 Turn(0,220,200);
		 else if(gyro.z_angle>=A2-4&&gyro.z_angle<=A2+5)
			 {A1=A2=A3=A4=A5=0;Next_Step_circle(1);}
		 else Turn(0,200,200);
	 }
	 else if(A1>=359-B&&A1<=359)
	 {
		 if(A5>=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=359)
					Turn(0,270,250);
			 else if(gyro.z_angle>=0&&gyro.z_angle<=A5)
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A5&&gyro.z_angle<=A4-2)
				 Turn(0,180,160);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_circle(1);}
			 else Turn(0,220,200);
		 }
		 if(A5<=0)
		 {
			 if(gyro.z_angle>=A1&&gyro.z_angle<=A6)
				 Turn(0,270,250);
			 else if(gyro.z_angle>=A6&&gyro.z_angle<=A3) 
				 Turn(0,220,200);
			 else if(gyro.z_angle>=A3&&gyro.z_angle<=359)
				 Turn(0,170,150);
			 else if(gyro.z_angle>=A4-4&&gyro.z_angle<=A4+5)
				{A1=A2=A3=A4=A5=0;Next_Step_circle(1);}
			 else Turn(0,220,200);
		 } 
//	 }
	}
}
void youzhuan(int B,float C)///90 0.3///45 0.2////右转
{
//	if(Tim.num==0)
//	{
		A2=A1-B;
		A3=A1-C*B;
		A4=360-B+A1;
		A5=360+A1-C*B;
		A6=360-B+A1;
//	}
//	if(Tim.num>=1)
//	{
		if((A1>=B+2)&&(A1<=359))
		{
		 if(gyro.z_angle<=A1&&gyro.z_angle>=A3)
			 Turn(1,310,300);
		 else if(gyro.z_angle<=A3&&gyro.z_angle>=A2+2)
			 Turn(1,150,150);
		 else if(gyro.z_angle<=A2+3&&gyro.z_angle>=A2-5)
			 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
		 else Turn(0,165,150);
		}
		else if(A1>=0&&A1<=B+1)
		{
		 if(C*B>A1)
		 {
			 if(gyro.z_angle>=0&&gyro.z_angle<=A1)
				 Turn(1,270,250);
			 else if(gyro.z_angle>A5&&gyro.z_angle<=360)
				 Turn(1,220,200);
			 else if(gyro.z_angle>=A6+2&&gyro.z_angle<=A5)
				 Turn(1,140,120);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5) 
				{A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
			 else Turn(0,170,150);
		 }
		 if(C*B<=A1)
		 {
			 if(gyro.z_angle<=A1&&gyro.z_angle>A3)
				 Turn(1,270,250);
			 else if(gyro.z_angle<=A3&&gyro.z_angle>=0)
				 Turn(1,220,200);
			 else if(gyro.z_angle<=360&&gyro.z_angle>=A6+2)
				 Turn(1,140,120);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5)
				 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
			 else Turn(0,170,150);
		 }
//		}
	}
}

void youzhuan_di(int B,float C)///90 0.3///45 0.2////右转
{
//	if(Tim.num==0)
//	{
//		A1=gyro.z_angle;
		A2=A1-B;
		A3=A1-C*B;
		A4=360-B+A1;
		A5=360+A1-C*B;
		A6=360-B+A1;
//	}
//	if(Tim.num>=1)
//	{
		if((A1>=B+2)&&(A1<=359))
		{
		 if(gyro.z_angle<=A1&&gyro.z_angle>=A3)
			 Turn(1,300,310);
		 else if(gyro.z_angle<=A3&&gyro.z_angle>=A2+2)
			 Turn(1,150,160);
		 else if(gyro.z_angle<=A2+3&&gyro.z_angle>=A2-5)
			 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
		 else Turn(1,150,160);
		}
		else if(A1>=0&&A1<=B+1)
		{
		 if(C*B>A1)
		 {
			 if(gyro.z_angle>=0&&gyro.z_angle<=A1)
				 Turn(1,250,260);
			 else if(gyro.z_angle>A5&&gyro.z_angle<=360)
				 Turn(1,200,210);
			 else if(gyro.z_angle>=A6+2&&gyro.z_angle<=A5)
				 Turn(1,120,130);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5) 
				{A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
//			 else Turn(0,150,160);
		 }
		 if(C*B<=A1)
		 {
			 if(gyro.z_angle<=A1&&gyro.z_angle>A3)
				 Turn(1,250,260);
			 else if(gyro.z_angle<=A3&&gyro.z_angle>=0)
				 Turn(1,200,210);
			 else if(gyro.z_angle<=360&&gyro.z_angle>=A6+2)
				 Turn(1,120,130);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5)
				 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
//			 else Turn(0,150,160);
		 }
//		}
	}
}
void youzhuan_po(int B,float C)///90 0.3///45 0.2////右转
{
//	if(Tim.num==0)
//	{
//		A1=gyro.z_angle;
		A2=A1-B;
		A3=A1-C*B;
		A4=360-B+A1;
		A5=360+A1-C*B;
		A6=360-B+A1;
//	}
//	if(Tim.num>=1)
//	{
		if((A1>=B+2)&&(A1<=359))
		{
		 if(gyro.z_angle<=A1&&gyro.z_angle>=A3)
			 Turn(1,250,250);
		 else if(gyro.z_angle<=A3&&gyro.z_angle>=A2+2)
			 Turn(1,150,150);
		 else if(gyro.z_angle<=A2+3&&gyro.z_angle>=A2-5)
			 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
		 else Turn(1,170,150);
		}
		else if(A1>=0&&A1<=B+1)
		{
		 if(C*B>A1)
		 {
			 if(gyro.z_angle>=0&&gyro.z_angle<=A1)
				 Turn(1,250,250);
			 else if(gyro.z_angle>A5&&gyro.z_angle<=360)
				 Turn(1,200,200);
			 else if(gyro.z_angle>=A6+2&&gyro.z_angle<=A5)
				 Turn(1,150,120);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5) 
				{A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
			 else Turn(0,200,200);
		 }
		 if(C*B<=A1)
		 {
			 if(gyro.z_angle<=A1&&gyro.z_angle>A3)
				 Turn(1,250,250);
			 else if(gyro.z_angle<=A3&&gyro.z_angle>=0)
				 Turn(1,200,200);
			 else if(gyro.z_angle<=360&&gyro.z_angle>=A6+2)
				 Turn(1,150,120);
			 else if(gyro.z_angle<=A6+3&&gyro.z_angle>=A6-5)
				 {A1=A2=A3=A4=A5=A6=0;Next_Step(1);}
			 else Turn(0,200,200);
		 }
//		}
	}
}

