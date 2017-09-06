#ifndef _CONTROL2_H_
#define _CONTROL2_H_

#include "stdint.h"
#include "stdbool.h"
extern uint16_t tt;

void getready(void);//初始化函数
void PIT1_HandlerU( void );//1ms中断回调函数
void Printf(void);//变量显示
void bamaswitch(void);//设置拔码开关  
void stopmove(void);//停止运动
void startimage(void);
void endimage(void);
void firstimage(void);
void duqubama(void);

#endif