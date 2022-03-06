#include "pid.h"
#include "gray.h"
#include "oled.h"
#include "motor.h"
#include "variate.h"
#include "math.h"
extern pid Pid;
extern flag Flag;
extern u8 Gray[10];
extern u8 HouGray[10];

float pp,kk,pp1,pp2,k,j;
int i1[8],i[8],temp1[8],temp[8];
int indef,pd,late;	
int lates[8];
int zxkg=1;	
float mangzou_bz=1;
float pwm1=700,pwm2=700;
extern u16 pwm_val_left,pwm_val_right;


void PID_Init()
{
	Pid.Sv=0;
	Pid.Kp=30;
	Pid.T=15;
	Pid.Ti=7600;
	Pid.Td=7500;
	Pid.pwmcycle=1000;
}
//////
void Pid_Calc()
{
	float DelEk;
	float ti;
	float ki;
	float td;
	float kd;
	float Iout;
	float Pout;
	float Dout;

	if(Pid.C1ms<(Pid.T))
	{
		return;
	}
	else
	{
		Pid.Ek=Pid.Pv-Pid.Sv;
	
		Pid.SEK+=Pid.Ek;
	
		DelEk=Pid.Ek-Pid.Ek_1;
	
		ti=Pid.T/Pid.Ti;
		ki=ti*Pid.Kp;
	
		td=Pid.Td/Pid.T;
		kd=td;
		
		Iout=Pid.SEK*ki*Pid.dki;       //积分输出
		Pout=Pid.Kp*Pid.Ek*Pid.dkp;    //比例输出
		Dout=kd*DelEk*Pid.dkd;         //微分输出
	
		Pid.OUT=Pout+Iout+Dout;
	
		if(Pid.OUT>Pid.pwmcycle)
		{
			Pid.OUT=Pid.pwmcycle;
		}
		if(Pid.OUT<-Pid.pwmcycle)
		{
			Pid.OUT=-Pid.pwmcycle;
		}
	
		Pid.Ek_1=Pid.Ek;                              //历史值
		Pid.C1ms=0;                                   //计时重新刷新		       
	}
}
/////PD计算
void Pid_Calc1()
{
	float DelEk;
	float td;
	float kd;
	float Pout;
	float Dout;

	if(Pid.C1ms<(Pid.T))
	{
		return;
	}
	else
	{
		Pid.Ek=Pid.Pv-Pid.Sv;
	
		Pid.SEK+=Pid.Ek;
	
		DelEk=Pid.Ek-Pid.Ek_1;
	
		
		td=Pid.Td/Pid.T;
		kd=td;
		
	
		Pout=Pid.Kp*Pid.Ek*Pid.dkp;    //比例输出
		Dout=kd*DelEk*Pid.dkd;         //微分输出
	
		Pid.OUT=Pout+Dout;
	
		if(Pid.OUT>Pid.pwmcycle)
		{
			Pid.OUT=Pid.pwmcycle;
		}
		if(Pid.OUT<-Pid.pwmcycle)
		{
			Pid.OUT=-Pid.pwmcycle;
		}
	
		Pid.Ek_1=Pid.Ek;                              //历史值
		Pid.C1ms=0;                                   //计时重新刷新		       
	}
}
void panduan()
{	
/////////////////////////////////////////////////////////////////////////////////////////////////// 灰度扫描
	i[0]=GRAY1;
	i[1]=GRAY2;
	i[2]=GRAY3;
	i[3]=GRAY4;
	i[4]=GRAY5;
	i[5]=GRAY6;
	i[6]=GRAY7;
	i[7]=GRAY8;
	
	pp=i[0]+i[1]+i[2]+i[3]+i[4]+i[5]+i[6]+i[7];

	////////////////////////////////////////////////////////////////////////////////////////////////////路口屏蔽 
	if(zxkg==1)
	{
	if(pp==6)
	{
		for(indef=0;indef<8;indef++)
		{
			if(i[indef]==0)
			{
				pd+=(indef+1)*pow(-1,indef+1);
			}
		}
	}
	if(pp<6||(pd!=1&&pd!=-1))
	{
			for(indef=0;indef<8;indef++)
		{	
			lates[indef]=temp[indef];
			if(temp[indef]==0)
			{
			  if((indef-1)!=-1)
				{
					lates[indef-1]=0;
				}
				if((indef+1)!=8)
				{
					lates[indef+1]=0;
				}
			}
		}
		for(indef=0;indef<8;indef++)
		{
			i[indef]=i[indef]||lates[indef];
		}
		pp2=i[0]+i[1]+i[2]+i[3]+i[4]+i[5]+i[6]+i[7];
		if(pp2<6)
		{
			for(indef=0;indef<8;indef++)
			{
				i[indef]=temp[indef];
			}
		}
		pd=0;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////直线误差

	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==0&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=1;  Pid.dkp=1.0;  Pid.dki=1.0;  Pid.dkd=1.0;  temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=0;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==0&&i[5]==1&&i[6]==1&&i[7]==1)  {j=-1; Pid.dkp=1.0;  Pid.dki=1.0;  Pid.dkd=1.0;  temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=0;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==0&&i[3]==0&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=2;  Pid.dkp=1.04;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=1;temp[2]=0;temp[3]=0;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==0&&i[5]==0&&i[6]==1&&i[7]==1)  {j=-2; Pid.dkp=1.04;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=0;temp[5]=0;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==0&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=3;  Pid.dkp=1.08;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=1;temp[2]=0;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==0&&i[6]==1&&i[7]==1)  {j=-3; Pid.dkp=1.08;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=0;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==0&&i[2]==0&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=4;  Pid.dkp=1.12;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=0;temp[2]=0;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==0&&i[6]==0&&i[7]==1)  {j=-4; Pid.dkp=1.12;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=0;temp[6]=0;temp[7]=1;}
	if(i[0]==1&&i[1]==0&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=5;  Pid.dkp=1.26;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=1;temp[1]=0;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==0&&i[7]==1)  {j=-5; Pid.dkp=1.26;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=0;temp[7]=1;}
	if(i[0]==0&&i[1]==0&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=6;  Pid.dkp=1.60;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=0;temp[1]=0;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==0&&i[7]==0)  {j=-6; Pid.dkp=1.60;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=0;temp[7]=0;}
	if(i[0]==0&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==1)  {j=7;  Pid.dkp=1.74;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=0;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=1;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==1&&i[4]==1&&i[5]==1&&i[6]==1&&i[7]==0)  {j=-7; Pid.dkp=1.74;  Pid.dki=0;  Pid.dkd=1.0;   temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=1;temp[4]=1;temp[5]=1;temp[6]=1;temp[7]=0;}
	if(i[0]==1&&i[1]==1&&i[2]==1&&i[3]==0&&i[4]==0&&i[5]==1&&i[6]==1&&i[7]==1)  {j=0;  Pid.dkp=1.00;  Pid.dki=1.0;  Pid.dkd=1.0; temp[0]=1;temp[1]=1;temp[2]=1;temp[3]=0;temp[4]=0;temp[5]=1;temp[6]=1;temp[7]=1;}
}
/////////速度模式
void speed(int mode)
{
	switch(mode)
   {
			case 0:
			{
				Pid.Kp=15;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=100;   ///right
				pwm2=110; ///left
			}break;
			
			case 1:
			{
				Pid.Kp=14;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=150;   ///right
				pwm2=150; ///left
			}break;
			
			case 2:
			{
				Pid.Kp=12;
				Pid.Ti=8000;
				Pid.Td=2000;
				pwm1=200;
				pwm2=200;
			} break;
			
			case 3:
			{
				Pid.Kp=10;
				Pid.Ti=7000;
				Pid.Td=2000;
				pwm1=250;
				pwm2=255;
			} break;

			case 4:
			{
				Pid.Kp=5;
				Pid.Ti=7000;
				Pid.Td=4000;
				pwm1=300;     //right
				pwm2=305;   //left
			} break;

			case 5:
			{
				Pid.Kp=8;
				Pid.Ti=7000;
				Pid.Td=6000;
				pwm1=400;
				pwm2=400;
			} break;
			
			case 6:
			{
				Pid.Kp=8;
				Pid.Ti=7000;
				Pid.Td=5000;
				pwm1=450;
				pwm2=450;
			} break;
			
			case 7:
			{
				Pid.Kp=15;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=80;
				pwm2=80;
			} break;
			
			case 8:
			{
				Pid.Kp=15;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=70;
				pwm2=70;
			} break;	
			
			case 9:
			{
				Pid.Kp=15;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=60;
				pwm2=60;
			} break;
			
			case 10:
			{
				Pid.Kp=15;
				Pid.Ti=7000;
				Pid.Td=1000;
				pwm1=100;   ///right
				pwm2=105; ///left
			}break;
		case 11:
			{
				Pid.Kp=10;
				Pid.Td=1000;
				pwm1=150;   ///right
				pwm2=150; ///left
			}break;
			
		case 12:
			{
				Pid.Kp=8;
				Pid.Ti=7000;
				Pid.Td=5000;
				pwm1=500;
				pwm2=500;
			} break;
		case 13:
			{
				Pid.Kp=8;
				Pid.Ti=7000;
				Pid.Td=5000;
				pwm1=600;
				pwm2=600;
			} break;
		case 14:
			{
				Pid.Kp=20;
				Pid.Td=4000;
				pwm1=150;   ///right
				pwm2=150; ///left
			}break;
  }
}
///////直线
void line(int mode)   
{    speed(mode);
	   mangzou_bz=0;	 	
		 zxkg=1;
		 Motor_Left(0);
		 Motor_Right(0);		
     TIM_SetCompare1(TIM3,pwm_val_left);	///left
	   TIM_SetCompare2(TIM3,pwm_val_right);	///right		
}

void pid_zhixian(u8 run_d)
{
	panduan();Pid_Calc();line(run_d);
} 

void pid_circle(u8 run_d)
{
	panduan();Pid_Calc1();line(run_d);
} 


