#ifndef _QITA_H_
#define _QITA_H_


#include "stdint.h"
#include "stdbool.h"



void pass(void);//判断是否经过一个信标灯
void prestate(void);
void daoche(void);//判断是否需要倒车

extern int can;
extern uint8_t xidengshu;
extern uint8_t xinbiaobiaozhi;
 void speedset(void);//设置前往不同的灯的速度
 extern uint8_t bamakaiguan;
extern uint16_t xinbiaoxiangsu;
extern uint16_t xinbiao0[10];
extern uint8_t laststate;
void jiajiansujuli();//动态设置加减速距离

void julican();


#endif