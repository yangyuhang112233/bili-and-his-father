#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <stdint.h>
#include "common.h"

extern int32_t qd_left_value;           //使用的左编码器计数值
extern	int32_t qd_right_value;          //使用的右编码器计数值

/*电机占空比控制函数*/
void Car_PWM_ChangeDuty(int8_t mode);
	
/*编码器读取函数*/
void QD_value( void );

#endif
