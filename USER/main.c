#include "variate.h"

extern flag Flag;
extern time Tim;
extern Gyro gyro;
extern uint8_t  tx2[];
extern uint8_t tx1[];
extern char rub[];
extern int A1;
extern int get_image_bz;
int	time_int_flag=0;
int lukou_bz=0;
int lukour_bz=0;
int lukouqr_bz=0;
int lukouql_bz=0;
int main(void)
{
	Init();
	while(1)
	{
		Scan();
		oled_show();
		if(time_int_flag==1)
		{				
			time_int_flag=0;
			panduan();	
			if(GRAYZL==0&&lukou_bz==0){lukou_bz=1;}
			else if(lukou_bz==1&&GRAYZL==1){lukou_bz=0;Flag.lukou+=1;}
			
			if(GRAYZR==0&&lukour_bz==0){lukour_bz=1;}
			else if(lukour_bz==1&&GRAYZR==1){lukour_bz=0;Flag.lukour+=1;}
			
			if(GRAYQR==0&&lukouqr_bz==0){lukouqr_bz=1;}
			else if(lukouqr_bz==1&&GRAYQR==1){lukouqr_bz=0;Flag.lukouqr+=1;}
			
			if(GRAYQL==0&&lukouql_bz==0){lukouql_bz=1;}
			else if(lukouql_bz==1&&GRAYQL==1){lukouql_bz=0;Flag.lukouql+=1;}
		}
		if(Tim.cnt>=400){Tim.num+=1;Led_Test=~Led_Test;Tim.cnt=0;}			
		
		switch(Flag.step)
			{
			//出发
			case 1:	
//				go_platform2();
				Start();
//				Flag.step=75;
 //					pid_zhixian(6);	
//					if(cant)Stop();
				break;
			
			case 2:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(5);
				if(Flag.lukou>=1&&(GRAYQR==0||GRAYQL==0))Next_Step(1);
				break;
			//////////上桥/////////////
			case 3:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 4:
				Go_Blind(130,140);
				if(gyro.x_angle>=177&&Tim.num>=1){Next_Step(1);}			
				break;
			///////////走桥/////////////
			case 5:
				Go_Blind(150,150);
				if(GRAYQR==0)Go_Blind(180,150);
				if(GRAYQL==0)Go_Blind(150,180);
				if(Tim.num>=2&&Tim.cnt>=100)Next_Step(1);
				break;
				
			case 6:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
//				Go_Blind(100,100);
//				if(GRAYQR==0)Go_Blind(120,100);
//				if(GRAYQL==0)Go_Blind(100,120);
//				if(gyro.x_angle>=181){Next_Step(1);}
				break;
				
			case 7:
				Go_Blind(100,100);
				if(can)
				{
					pid_zhixian(0);
					if(GRAYZL==1&&GRAYZR==1){Next_Step(1);}
				}
				break;
				
			case 8:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(4);
				if((GRAYQR==0||GRAYQL==0)&&Flag.lukou>=1){Next_Step(1);}
				break;
		
			case 9:	
				go_platform2();
				break;
      ////////路口///////////					
			case 10:
				pid_zhixian(1);
				if(GRAYQR==0)Next_Step(1);
				break;
				
			case 11:
				pid_zhixian(1);
//				Stop();	
//				A1=gyro.z_angle;	
				if(Tim.cnt>=100)Next_Step(1);				
				break;

			case 12:
				Turn(1,180,180);
				if((G4||G5)&&Flag.lukouql>=1)Next_Step(1);
//				youzhuan_po(30,0.2);
				break;
			
			case 13:
				Stop();
				if(Tim.cnt>=10)Go_Step(200);
				break;
			
			case 200:
				pid_zhixian(2);
				if(Tim.num>=1&&(GRAYQL==0||GRAYQR==0))Go_Step(14);
				break;
			
			case 14:
				Stop();
				if(Tim.cnt>=10)Next_Step(1);		
				break;
      ////////减速带/////////			
			case 15:
				pid_zhixian(0);
				if(Tim.num>=4&&GRAYZL==1&&GRAYZR==1)Next_Step(1);	
				break;
			////////上斜坡//////////
			case 16:
				pid_zhixian(2);
				if(cant)Next_Step(1);
				break;
			
			case 17:
				Stop();
				if(Tim.cnt>=10)Next_Step(1);	
				break;		
			
			case 18:
				Go_Blind(140,170);
				if((HG5||HG6||HG7||HG8)&&GRAYZL==0&&GRAYZR==0&&gyro.x_angle<=175)Go_Step(253);//(G4||G5)
				break;
			////////斜坡转//////
			case 253:
				Stop();
				if(Tim.cnt>=10)Go_Step(19);	
				break;
			
			case 19:
				Turn(0,150,150);
				if(GRAYQL==0)Next_Step(1);
//				else if(GRAYQR==0)Go_Step(251);
				break;
			
			case 20:
				Stop();
				if(Tim.cnt>=10)Go_Step(251);	
				break;
			
			case 251:
				Go_Blind(150,170);
				if(can)Go_Step(21);		
				break;			
			
			case 21:
				pid_zhixian(1);
				if(gyro.x_angle<=180&&hou_can)Next_Step(1);
				break;
			
			case 22:
				pid_zhixian(2);
				if(Tim.num>=1)pid_zhixian(12);
				if(Tim.num>=3)Go_Step(270);
				break;
			
			case 270:
				Stop();
				if(Tim.cnt>=20)Go_Step(269);					
				break;
			
			case 269:
				pid_zhixian(2);
				if((GRAYQL==0||GRAYQR==0))Go_Step(23);	
				break;
			//上台
			case 23:
				go_platform4();
				break;
			//到斜坡
			case 24:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(4);	
				if(Flag.lukou>=2)Go_Step(278);
				break;
			
			case 278:
				Stop();
				if(Tim.cnt>=20)Go_Step(231);				
				break;
			
			case 231:
				pid_zhixian(1);	
				if(Tim.cnt>=20)Go_Step(209);				
				break;
			
			case 209:
				Stop();
				if(Tim.cnt>=20)Go_Step(230);
				break;
			
			case 230:
				pid_zhixian(1);
				if(GRAYQL==0)Go_Step(234);
				break;
			
			case 234:
				Stop();
				if(Tim.cnt>=20)Go_Step(25);				
				break;
			
			case 25:
				pid_zhixian(1);
				if(cant)Next_Step(1);//hou_cant&&GRAYZL==0&&GRAYZR==0   gyro.y_angle<178
				break;
			
			case 26:
				Go_Blind(130,100);
				if(GRAYZL==0&&GRAYZR==0&&gyro.y_angle<164)Next_Step(1);
				break;
			
			case 27:
				Go_Blind(110,100);
				if(gyro.y_angle>166)Next_Step(1);
				break;
			
			case 28:
				Go_Blind(120,100);
				if(can&&gyro.x_angle<=185)Next_Step(1);
				break;
			//出斜坡
			case 29:
				pid_zhixian(1);
				if(Tim.num>=1)Next_Step(1);
				break;
			
			case 30:
				pid_zhixian(1);				
				if(Tim.num>=1)pid_zhixian(12);
				if(Tim.num>=3)Go_Step(271);
				break;
			
			case 271:
				Stop();
				if(Tim.cnt>=20)Go_Step(272);				
				break;
			
			case 272:
				pid_zhixian(2);
				if((GRAYQL==0||GRAYQR==0))Go_Step(31);
				break;

			case 31:
				go_platform3();	
				break;
				
			case 32:
				pid_zhixian(1);				
				if(Tim.num>=1)pid_zhixian(5);
				if(GRAYQL==0){Go_Step(210);}
				break;
				
			case 210:
				Stop();
				if(Tim.cnt>=30)Go_Step(33);
				break;
							
			//路口			
			case 33:
				pid_zhixian(1);
				if(GRAYQR==0)Go_Step(203);
				break;
			
			case 203:
				pid_zhixian(1);
				if(Tim.cnt>=100)Go_Step(34);
				break;
			
			case 34:
				Stop();
				A1=gyro.z_angle;
				if(Tim.cnt>=30){Next_Step(1);}
				break;
	
			case 35:
				youzhuan_po(40,0.3);
				break;
			
			case 36:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);	
				break;			
      //////障碍////////				
			case 37:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(3);
				if((GRAYQL==0||GRAYQR==0)&&Tim.num>=2)Next_Step(1);
				break;
			
			case 38:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 39:
				pid_zhixian(0);
//				Go_Blind(100,110);				
				if(GRAYZL==1&&GRAYZR==1&&Tim.num>=2)Next_Step(1);
				break;
			
			case 40:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(5);
				if(Flag.lukou>=1&&GRAYQR==0)Go_Step(223);
				break;
			
			case 223:
				Stop();
				if(Tim.cnt>=20)Go_Step(41);
				break;
			
			case 41:
				Go_Blind(80,80);
				if(GRAYZR==0)Next_Step(1);					
				break;
			
			case 42:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 43:
				zuozhuan_di(30,0.3);				
				break;
			
			case 44:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;						
			
			case 45:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(12);
				if(Tim.num>=3)Go_Step(273);
				break;
			
			case 273:
				Stop();
				if(Tim.cnt>=20)Go_Step(274);				
				break;
			
			case 274:
				pid_zhixian(2);
				if(GRAYQL==0||GRAYQR==0)Go_Step(46);
				break;
	
			case 46:
				go_platform5();		
				break;
      ////尽头/////////					
			case 47:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(12);
				if(Flag.lukou>=3)Go_Step(240);	
				break;
			
			case 240:
				pid_zhixian(12);
				if(Flag.lukour>=1)Go_Step(222);
				break;
			
			case 222:
				Stop();
				if(Tim.cnt>=30)Go_Step(48);				
				break;
			
			case 48:
				pid_zhixian(2);
				if(Tim.cnt>=60)Go_Step(211);
				break;
			
			case 211:
				pid_zhixian(1);
				if(cant)Go_Step(49);//GRAYQL==0
				break;
			
			case 49:
				Go_Blind(80,80);
				if(Tim.cnt>=50)Next_Step(1);
				break;
			
			case 50:
				Stop();			
				A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 51:
				zuozhuan(80,0.3);				
				break;
			
			case 52:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;		
			
			case 53:
				pid_zhixian(1);
				if(G1&&Tim.num>=1)Next_Step(1);
				break;
			
			case 54:
				pid_zhixian(7);
				if(Tim.cnt>=100)Next_Step(1);
				break;
			
			case 55:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 56:
				zuozhuan(80,0.5);
				break;
			
			case 57:
				Stop();
				Servo_scene();
				if(Tim.cnt>=20)Next_Step(1);
				break;				
			
			case 58:
				pid_zhixian(1);
				if(Tim.num>=2)Next_Step(1);
				break;			
			
			case 59:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;		
			
			case 60:
				Back_Blind(110,100);
				if(GRAYZL==0)Next_Step(1);
				break;
			
			case 61:
				Stop();
				Servo_return();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);		
				break;
			
			case 62:
				zuozhuan(80,0.5);		
				break;

			case 63:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;	
			
			case 64:
				pid_zhixian(1);
				if(cant&&Tim.num>=1)Next_Step(1);//GRAYQR==0&&Tim.num>=1
				break;
			
			case 65:
				Go_Blind(80,80);
				if(Tim.cnt>=80)Next_Step(1);
				break;

			case 66:
				Stop();
				A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);				
				break;
			
			case 67:
				Turn(1,200,200);
				if(G4||G5)Next_Step(1);
//				youzhuan(90,0.5);			
				break;
			
			case 68:
				Stop();
				if(Tim.cnt>=10)Next_Step(1);
				break;				
			///////走圈//////////////			
			case 69:
				circle();				
				break;
			
			case 70:
				Stop();
				if(Tim.cnt>=10)Go_Step(201);
				break;						
			
			case 201:		
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(6);
				if(Flag.lukour>=1)Go_Step(239);//Flag.lukou>=3
				break;
			
			case 239:
				pid_zhixian(6);
				if(Tim.cnt>=50)Go_Step(228);
				break;
			
			case 228:
				Stop();
				if(Tim.cnt>=20)Go_Step(202);			
				break;
			
			case 202:		
				pid_zhixian(2);
				if(GRAYQR==0)Go_Step(71);
				break;		
			
			case 71:
				pid_zhixian(7);
				if(Tim.cnt>=100)Next_Step(1);
				break;
			
			case 72:
				Stop();
				A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=30)Next_Step(1);
				break;
			//上斜坡
			case 73:	
				youzhuan(90,0.3);
				break;

			case 74:
				Stop();
				if(Tim.cnt>=30)Next_Step(1);
				break;				
			
			case 75:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(4);
				if(Flag.lukouqr>=1)pid_zhixian(2);
				if(Flag.lukouqr>=2)Go_Step(236);
				break;
			
			case 236:
				Stop();
				if(Tim.cnt>=20)Go_Step(76);
				break;
			
			case 76:
				Go_Blind(150,150);
				if((GRAYQL==0||GRAYQR==0)&&gyro.x_angle<=168)Next_Step(1);
				break;				
			
			case 77:				
				Go_Blind(80,80);
				if(Tim.cnt>=150)Next_Step(1);		
				break;
			//斜坡转
			case 78:
				Stop();
				A1=gyro.z_angle;   //当前角度				
				if(Tim.cnt>=30)Next_Step(1);	
				break;
			
			case 79:
				youzhuan_po(80,0.3);
				break;
			
			case 80:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;							
			
			case 81:
				Go_Blind(120,100);
				if(gyro.y_angle>=175)Next_Step(1);;//gyro.y_angle>=177&&Tim.num>2
				break;
			
			case 82:
				Go_Blind(110,100);
				if(can)Next_Step(1);
				break;			
		  //走高台
			case 83:
				high_profile();
				break;
			//斜坡			
			case 84:
				Go_Blind(150,165);
				if(GRAYQR==0)Next_Step(1);//gyro.y_angle>180
				break;
			//上斜坡
			case 85:
				Go_Blind(100,110);
				if(GRAYZL==0&&GRAYZR==0&&gyro.y_angle>=193)Next_Step(1);
				break;
			//走斜坡
			case 86:
				Go_Blind(100,100);
				if(gyro.y_angle<=195&&Tim.num>=1)Next_Step(1);
				break;
			//下斜坡
			case 87:
				Go_Blind(100,110);
				if(gyro.x_angle>=178&&gyro.y_angle<=180)Next_Step(1);
				break;
			//出斜坡		
			case 88:
				Go_Blind(100,100);
				if(can)Next_Step(1);
				break;
		
			case 89:
				pid_zhixian(0);
				if(Tim.num>=1)pid_zhixian(1);
				if((GRAYQL==0||GRAYQR==0)&&Flag.lukour>=1)Next_Step(1);
				break;
			
			case 90:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;		
			//减速带
			case 91:
				pid_zhixian(0);
				if(Tim.num>=7&&GRAYZL==1&&GRAYZR==1)Next_Step(1);
				break;
			
			case 92:
				pid_zhixian(2);
				if(GRAYQL==0||GRAYQR==0)Next_Step(1);
				break;
				//上低台			
			case 93:
				pid_zhixian(2);
				if(cant)Next_Step(1);
				break;

			case 94:
				Go_Blind(140,150);
				get_image_bz=0;
				if(gyro.x_angle>=177&&(GRAYQL==0&&GRAYQR==0)&&Tim.num>=1&&hou_on_line)Go_Step(96);
				break;
					
			case 95:
				Next_Step(1);
//				Stop();
//				if(rub[0]==7){Servo();}
//				else {Next_Step(1);}		
				break;
				
			case 96:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 97:
				Back_Blind(100,110);
				if(Tim.cnt>=80)Next_Step(1);
				break;
			//下低台
			case 98:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);	
				break;
			
			case 99:
				zuozhuan(170,0.3);		
				break;	

			case 100:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);	
				break;
			
			case 101:
				Stop();
				if(rub[0]==7){Servo();}
				else {Next_Step(1);}					
				break;
			
			case 102:
				Go_Blind(80,80);
				if(gyro.x_angle>=182)Go_Step(190);	
				break;
			
			case 190:
				pid_zhixian(7);
				if(gyro.x_angle<=180&&GRAYZL==1&&GRAYZR==1)Go_Step(299);
				break;
			//减速带			
			case 299:
				pid_zhixian(1);
				if(GRAYQL==0||GRAYQR==0)Go_Step(103);
				break;
			
			case 103:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);;
				break;		
			
			case 104:		
				pid_zhixian(0);
				if(Tim.num>=8&&GRAYZL==1&GRAYZR==1)Next_Step(1);
				break;
			
			case 105:
				pid_zhixian(2);
				if(cant)Next_Step(1);
				break;
			//斜坡
			case 106:
				Go_Blind(150,150);
				if(GRAYQL==0)Next_Step(1);
				break;
			
			case 107:
				Go_Blind(110,100);
				if(gyro.y_angle<=163&&gyro.x_angle<=177)Next_Step(1);
				break;
			
			case 108:
				Go_Blind(100,110);
				if(gyro.x_angle>=177)Next_Step(1);
				break;
			
			case 109:
				Go_Blind(100,100);
				if(Tim.num>=1)Next_Step(1);//&&Tim.cnt>=100
				break;
			
			case 110:
				Stop();
				A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=30)Next_Step(1);
				break;
			//斜坡转
			case 111:
				youzhuan(80,0.5);
				break;
			
			case 112:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;					
			
			case 113:
				pid_zhixian(0);
				if(can)Next_Step(1);
				break;
			
			case 114:
				pid_zhixian(2);
				if((GRAYQL==0||GRAYQR==0)&&Tim.num>=1)Next_Step(1);//
				break;
			
			case 115:
				pid_zhixian(1);
				if(Tim.cnt>=100)Next_Step(1);//GRAYZL==0||GRAYZR==0
				break;
			
			case 116:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 117:
				zuozhuan_di(90,0.5);
				break;
			
			case 118:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;				
			
			case 119:
//				pid_zhixian(1);
////				if(Tim.num>=1)pid_zhixian(2);
//				if(GRAYQL==0)
				Next_Step(1);
				break;
			
			case 120:
//				pid_zhixian(6);
//				if(GRAYZL==0)
					Next_Step(1);
				break;
			
			case 121:
//				Stop();
//			  A1=gyro.z_angle;   //当前角度
//				if(Tim.cnt>=10)
					Next_Step(1);
				break;
			
			case 122:
//				zuozhuan(85,0.5);
				Next_Step(1);
				break;
			
			case 123:
//				Stop();if(Tim.cnt>=20)
				Next_Step(1);
				break;	
			
			case 124:
//				pid_zhixian(0);
//				if(cant&&Tim.num>=1)
					Next_Step(1);
				break;
			
			case 125:
//				Back_Blind(100,110);
//				if(GRAYZL==0||GRAYZR==0)
					Next_Step(1);
				break;
			
			case 126:
//				Stop();
//			  A1=gyro.z_angle;   //当前角度
//				if(Tim.cnt>=10)
					Next_Step(1);
				break;
			
			case 127:
				Next_Step(1);
//				zuozhuan(90,0.5);
				break;
			
			case 128:
//				Stop();if(Tim.cnt>=20)
				Next_Step(1);
				break;					
			
			case 129:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(2);
				if(GRAYQR==0)Go_Step(298);//
				break;
			
			case 298:
				pid_zhixian(1);
				if(cant)Go_Step(292);
				break;
			
			case 292:
				Stop();
				if(Tim.cnt>=30)Go_Step(130);				
				break;
			
			case 130:
				Go_Blind(80,80);
				if(Tim.cnt>=20)Next_Step(1);	
				break;
			
			case 131:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);
				break;
			
			case 132:
				youzhuan(80,0.5);
				break;
			
			case 133:
				Stop();
				if(Tim.cnt>=20)Go_Step(143);
				break;					
			
			case 134:
				pid_zhixian(1);
				if(G1&&Tim.num>=1)Next_Step(1);
				break;
			
			case 135:
				pid_zhixian(7);
				if(Tim.cnt>=100)Next_Step(1);
				break;
			
			case 136:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=50)Next_Step(1);
				break;
			
			case 137:
				zuozhuan(90,0.5);
				break;
			
			case 138:
				Stop();
				Servo_scene();
				if(Tim.cnt>=20)Next_Step(1);
				break;				
			
			case 139:
				pid_zhixian(1);
				if(Key5==0)Next_Step(1);
				break;
			
			case 140:
				Back_Blind(100,110);
				if(GRAYZL==0||GRAYZR==0)Go_Step(226);
				break;
			
			case 226:
				Stop();
				Servo_return();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=10)Go_Step(141);
				break;
			
			case 141:
				youzhuan(90,0.5);
				break;
			
			case 142:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;				
			//障碍
			case 143:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(4);
				if(Flag.lukou>=2&&(GRAYQL==0||GRAYQR==0))Go_Step(216);
				break;
			
			case 216:
				Stop();
				if(Tim.cnt>=20)Go_Step(144);
				break;	
			
			case 144:			
				pid_zhixian(0);
//				Go_Blind(100,110);
				if(GRAYZL==1&&GRAYZR==1&&Tim.num>=3)Next_Step(1);
				break;
			
			case 145:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(2);
				if(GRAYQR==0)Go_Step(229);
				break;
			
			case 229:
				Stop();
				if(Tim.cnt>=20)Go_Step(218);		
				break;
			
			case 218:
				pid_zhixian(1);
				if(cant)Go_Step(219);//GRAYQL==0
				break;
			
			case 219:Go_Step(146);
//				Go_Blind(80,80);
//				if(Tim.cnt>=50)Go_Step(146);//GRAYQL==0
				break;			
			
			case 146:
				Stop();
				A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=20)Next_Step(1);		
				break;

			case 147:
				Turn(1,180,180);
				if(G4||G5)Next_Step(1);
//				youzhuan(90,0.3);
				break;
			
			case 148:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;					
			//斜坡			
			case 149:
				pid_zhixian(1);
				if(Tim.num>=1)pid_zhixian(2);
				if(GRAYQR==0)Next_Step(1);
				break;
			
			case 150:
				Go_Blind(100,130);
				if(GRAYZL==0&&GRAYZR==0&&gyro.y_angle>=194)Next_Step(1);
				break;
				
			case 151:
				Go_Blind(80,80);
				if(Tim.num>=1){Next_Step(1);}				
				break;
			
			case 152:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=50){Next_Step(1);}		
				break;
			
			case 153:
				zuozhuan(30,0.5);
				break;
			
			case 154:
				Stop();
				if(Tim.cnt>=30)Next_Step(1);
				break;						
			
			case 155:
				Go_Blind(100,130);
				if(can)Next_Step(1);
				break;
			//走跷跷板
			case 156:
				pid_zhixian(0);
				if(GRAYQL==0||GRAYQR==0){Next_Step(1);}
				break;
			
			case 157:
				Go_Blind(170,160);
				if(Tim.num>=3)Next_Step(1);
				break;
			//出跷跷板
			case 158:
				Stop();
				if(Tim.num>=2)Next_Step(1);	
				break;
			
			case 159:
				pid_zhixian(1);
				if(GRAYQR==0)Next_Step(1);		
				break;
			
			case 160:
				Go_Blind(150,160);
				if(GRAYZL==0)Next_Step(1);
				break;
			
			case 161:
				Stop();		
				A1=gyro.z_angle;
				if(Tim.cnt>=10)Next_Step(1);
				break;
			
			case 162:
				youzhuan(30,0.3);
				break;
			
			case 163:
				Stop();
				if(Tim.cnt>=20)Next_Step(1);
				break;		
			
			case 164:
				pid_zhixian(2);
				if(GRAYQL==0||GRAYQR==0)Next_Step(1);
				break;
				
			case 165:
				pid_zhixian(1);
				if(cant)Next_Step(1);
				break;
				
			case 166:
				Go_Blind(150,160);
				if(gyro.x_angle>=176&&(GRAYQL==1||GRAYQR==1)&&Tim.num>=1){Next_Step(1);}
				break;
				
			case 167:
				Back_Blind(100,110);
				if(Tim.cnt>=50)Next_Step(1);
				break;
			
			case 168:
				Stop();
			  A1=gyro.z_angle;   //当前角度
				if(Tim.cnt>=50)Next_Step(1);
				break;
			
			case 169:
				zuozhuan(170,0.3);
				break;
			
			case 170:
				Stop();
				if(GRAY_Start==0)Go_Step(1);
				break;
			}
	}
}

