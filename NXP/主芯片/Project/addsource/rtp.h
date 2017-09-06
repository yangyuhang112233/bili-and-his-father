#ifndef _RTP_H
#define _RTP_H

#include "head.h"
#include "gpio.h"
#include "key.h"

extern uint16_t route_selection_switch;

void real_time_process( void );
void camstop( void );

#endif