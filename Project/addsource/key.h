#ifndef _KEY_H
#define _KEY_H

#include "stdint.h"
#include "gpio.h"

uint32_t switch_mode_selection( void );
uint32_t switch_mode_data(  void );

extern uint16_t bama[4];//��ȡ���뿪�ص��ĸ�����
extern uint16_t bamaa[4];

#endif