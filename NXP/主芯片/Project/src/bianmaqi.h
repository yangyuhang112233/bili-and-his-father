#ifndef _BIANMAQI_H_
#define _BIANMAQI_H_

#include <stdint.h>
#include "common.h"

extern  int16_t qd_left_value;           //使用的左编码器计数值
extern	int16_t qd_right_value;          //使用的右编码器计数值
extern  int16_t avespeed;                //当前平均速度
void QD_value( void );

#endif
