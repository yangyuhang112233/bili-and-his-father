#include "head.h"

uint16_t dooracc=10000;
uint16_t doorslow=10000;
int16_t Kp=400;
int16_t Ki=1;
int16_t leftsum =800;
int16_t rightsum =800;

 /*pid参数设置*/
static float pwm_Kp = 60, pwm_Ki = 0.4, pwm_Kd=0;   //前向电机加速和减速pid参数
static int32_t error_sum_left = 0;
static int32_t error_sum_right = 0;
static int32_t pwm_left=0;
static int32_t pwm_right=0;

void Servo_Control()
{     
    
    //在程序第一次进入循环时设置初值
    if(anglenow==0)foreangle=anglex;
        
    anglenow=anglex-Kd*(foreangle-anglex)/10;  

      
    if(anglenow<angleright)anglenow=angleright;
    if(anglenow>angleleft)anglenow=angleleft;     

    //舵机打角只在这里实现
    CMT_PWM_ChangDuty (anglenow);            
}

void Motor_PWM_Output( int left_value, int right_value )
{
	if(left_value > 10000)
	{
		left_value = 10000*PWM_RATE;
	}
	if(left_value < -10000)
	{
		left_value = -10000*PWM_RATE;
	}
	if(right_value>10000)
	{
		right_value=10000*PWM_RATE;
	}
	if(right_value<-10000)
	{
		right_value=-10000*PWM_RATE;
	}
	if (left_value > 0)
	{
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH3 ,0 );
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH2 ,left_value);
	}
	else
	{
		left_value = -left_value ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH3 ,left_value );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH2 ,0 );
	}
	if ( right_value > 0)
	{
		FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH1, 0 ); 
		FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH0, right_value);
	}
	else
	{
		right_value = -right_value ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH1, right_value ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH0, 0 );
	}
}

void Motor_PID_Output()
{
	int32_t speed_error_left=0;
	int32_t speed_error_right=0;
	int32_t speed_error_left_old=0;
	int32_t speed_error_right_old=0;
	int32_t errD_l,errD_r;

	speed_error_left = left_speed_disire - qd_left_value;
	speed_error_right = right_speed_desire - qd_right_value;	
	errD_l=speed_error_left-speed_error_left_old;
	errD_r=speed_error_right-speed_error_right_old;

	error_sum_left += speed_error_left;
	error_sum_right += speed_error_right;

	pwm_left = pwm_Kp*speed_error_left + pwm_Ki*error_sum_left +pwm_Kd*errD_l;
	pwm_right = pwm_Kp*speed_error_right + pwm_Ki*error_sum_right +pwm_Kd*errD_r;
	
	if(error_sum_left>ERR_SUM_LIMIT)
	{
		error_sum_left=ERR_SUM_LIMIT;
	}
	if(error_sum_left<-ERR_SUM_LIMIT)
	{
		error_sum_left=-ERR_SUM_LIMIT;
	}
	if(error_sum_right>ERR_SUM_LIMIT)
	{
		error_sum_right=ERR_SUM_LIMIT;
	}
	if(error_sum_right<-ERR_SUM_LIMIT)
	{
		error_sum_right=-ERR_SUM_LIMIT;
	}

	Motor_PWM_Output(pwm_left,pwm_right);
	speed_error_left_old=speed_error_left;
	speed_error_right_old=speed_error_right;
}

void PID_speed_set(int leftspeed, int rightspeed)
{
	left_speed_disire=leftspeed;
	right_speed_desire=rightspeed;
}

void Car_stop()
{
	PID_speed_set(0,0);
}
