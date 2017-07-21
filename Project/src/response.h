#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include "stdint.h"
#include "stdbool.h"
extern uint16_t deviation;//偏差
extern uint8_t lookcount;
void bizhang(void);//避障函数
void pointbizhang(void);//信标避障
 
void gothere(void);//前往信标位置
void lookfor(void);//看不到信标的时候寻找信标

void gothere1(void);//靠近信标时边缘切过信标

void piancha(void);//计算边缘经过信标的偏差








#endif