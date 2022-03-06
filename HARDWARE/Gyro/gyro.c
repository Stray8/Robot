#include "gyro.h"
#include "sys.h"

Gyro gyro;

void GYRO_Init(void)/////陀螺仪初始化
{
	gyro.flag=1;
	
}

void GYRO_Calc(void)//////陀螺仪数值转化
{
	 gyro.z_angle=((short)((gyro.z_high<<8)|gyro.z_low))/31415.00*180+180;
//    if(gyro.z_angle<=31415)
//      gyro.z_angle=gyro.z_angle/31415.00*180.00;
//    if(gyro.z_angle>=34121)
//	    gyro.z_angle=(31415-65536+gyro.z_angle)/31415.00*180+180;
		//////////////////////////////////////
	 gyro.x_angle=((short)(gyro.x_high<<8)|gyro.x_low)/31415.00*180+180;
//    if(gyro.x_angle<=31415)
//      gyro.x_angle=gyro.x_angle/31415.00*180.00;
//    if(gyro.x_angle>=34121)
//    	gyro.x_angle=(31415-65536+gyro.x_angle)/31415.00*180+180;
//		///////////////////////////////////////
		 gyro.y_angle=((short)(gyro.y_high<<8)|gyro.y_low)/31415.00*180+180;
//    if(gyro.y_angle<=31415)
//      gyro.y_angle=gyro.y_angle/31415.00*180.00;
//    if(gyro.y_angle>=34121)
//    	gyro.y_angle=(31415-65536+gyro.y_angle)/31415.00*180+180;
}


