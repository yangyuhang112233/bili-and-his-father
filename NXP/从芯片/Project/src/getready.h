#ifndef _CONTROL2_H_
#define _CONTROL2_H_

#include "stdint.h"
#include "stdbool.h"
extern uint16_t tt;

void getready(void);//��ʼ������
void PIT1_HandlerU( void );//1ms�жϻص�����
void Printf(void);//������ʾ
void bamaswitch(void);//���ð��뿪��  
void stopmove(void);//ֹͣ�˶�
void startimage(void);
void endimage(void);
void firstimage(void);
void duqubama(void);

#endif