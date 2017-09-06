#ifndef _CARTEST_H
#define _CARTEST_H

#include "head.h"
#include "rtp.h"

void low_speed_mode( void );
void hardware_test( uint32_t data );
void test_PWM( void );
void test_accelerate( void );
void test_PID( void );

#endif