#include "pid.h"
#include "stdio.h"

pid_p pid;  

//pid位置式
void PID_init()
{
    printf("PID_init begin \n");
    pid.Set_Voltage= 0.0;		  	// 设定的预期电压值
    pid.Actual_Voltage= 0.0;		// adc实际电压值
    pid.err= 0.0;				    // 当前次实际与理想的偏差
    pid.err_last=0.0;			    // 上一次的偏差
    pid.voltage= 0.0;			    // 控制电压值
    pid.integral= 0.0;			  	// 积分值
    pid.Kp= 0.2;				    // 比例系数
    pid.Ki= 0.15;				    // 积分系数
    pid.Kd= 0.2;				    // 微分系数
    printf("PID_init end \n");
}

float PID_realize( float v, float v_r)
{
    pid.Set_Voltage = v;			// 固定电压值传入
    pid.Actual_Voltage = v_r;	// 实际电压传入 = ADC_Value * 3.3f/ 4096
    pid.err = pid.Set_Voltage - pid.Actual_Voltage;	//计算偏差
    pid.integral += pid.err;						//积分求和
    pid.result = pid.Kp * pid.err + pid.Ki * pid.integral + pid.Kd * ( pid.err - pid.err_last);//位置式公式
    pid.err_last = pid.err;				//留住上一次误差
    return pid.result;
}