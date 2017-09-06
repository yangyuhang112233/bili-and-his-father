#ifndef _PID_H_
#define _PID_H_


#include "stdint.h"
#include "stdbool.h"

/*������ƺ���*/
void Motor_Control(uint16_t speed_desire1,uint16_t speed_desire2);
void Motor_down_Control(uint16_t speed_desire1,uint16_t speed_desire2);

void Motor_up_Control_8(uint16_t speed_desire_8);
void Motor_down_Control_8(uint16_t speed_desire_8);


/*������ƺ���*/
void Servo_Control();






#endif