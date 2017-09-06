#ifndef _PID_H_
#define _PID_H_


#include "stdint.h"
#include "stdbool.h"

#define PWM_RATE 1

/*电机控制函数*/
void Motor_down_Control(uint16_t speed_desire1,uint16_t speed_desire2);

void Motor_up_Control_8(uint16_t speed_desire_8);
void Motor_down_Control_8(uint16_t speed_desire_8);

void Motor_PWM_Output(int left, int right);
void Motor_PID_Output( void );
void PID_speed_set(int leftspeed, int rightspeed);
void Car_stop( void );


/*舵机控制函数*/
void Servo_Control();






#endif