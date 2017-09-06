#ifndef _KEY_H
#define _KEY_H

#include "stdint.h"
#include "gpio.h"

uint32_t switch_mode_selection( void );
uint32_t switch_mode_data(  void );

extern uint16_t bama[4];//读取拔码开关的四个输入
extern uint16_t bamaa[4];

#endif