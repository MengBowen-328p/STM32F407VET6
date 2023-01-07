#ifndef __PID_H__
#define __PID_H__
#include "main.h"

typedef struct
{
    float Set_Voltage;	  	//定义设定值
    float Actual_Voltage;	//定义实际值
    float err;			    //定义偏差值
    float err_last;		  	//定义上一个偏差值
    float Kp,Ki,Kd;		  	//定义比例、积分、微分系数
    float result;		    //pid计算结果
    float voltage;		  	//定义电压值（控制执行器的变量）
    float integral;		  	//定义积分值
}pid_p; 

void PID_init( void);
float PID_realize( float v, float v_r);

#endif
