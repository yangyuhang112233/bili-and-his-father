#ifndef _QITA_H_
#define _QITA_H_


#include "stdint.h"
#include "stdbool.h"



void pass(void);//�ж��Ƿ񾭹�һ���ű��
void prestate(void);
void daoche(void);//�ж��Ƿ���Ҫ����

extern int can;
extern uint8_t xidengshu;
extern uint8_t xinbiaobiaozhi;
 void speedset(void);//����ǰ����ͬ�ĵƵ��ٶ�
 extern uint8_t bamakaiguan;
extern uint16_t xinbiaoxiangsu;
extern uint16_t xinbiao0[10];
extern uint8_t laststate;
void jiajiansujuli();//��̬���üӼ��پ���

void julican();


#endif