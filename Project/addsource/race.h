#ifndef _RACE_H
#define _RACE_H

#include "stdint.h"

/*���ٵĲ��������ֺ������ٶ�*/
#define CHASU_LOW 220
#define CHASU_HIGH 320

/*����ͷ����*/
#define BIZHANG_DELTA 20
#define BIZHANG_LIMIT 145
#define DOOR7620 228

/*�еƵ�ƫ��*/
#define PIANCHA_LEFT 1.15
#define PIANCHA_RIGHT 1.3

/*�������ٵ�ͣ�� 0��ʾ��ͣ*/
#define PASS_BEACONS 0

/*�����������ȣ���ֵԽ�󵹳�Խ������*/
#define DAOCHE_YUSAI 5
#define DAOCHE_JUESAI 10

/*�ٶ�level*/
#define SPEED_LEVEL 2

/*·���滮*/
#define TURN_LEFT_ROUTE 0
#define TURN_RIGHT_ROUTE 1

extern uint16_t speedjiasu_list[SPEED_LEVEL];	 //Զ���ű� ֱ�߼��� 
extern uint16_t speedxinjiansu_list[SPEED_LEVEL];        //�����ű� ���м��� 
extern uint16_t speedxinbi1_list[SPEED_LEVEL];        //�ű���ϼ���    
extern uint16_t speedxinjia_list[SPEED_LEVEL];        //�����ű� �ٶ�̫�� ������
    
extern uint16_t speeddazhuan_list[SPEED_LEVEL];         //�Ҳ����ű��ת���ٶ�    
extern uint16_t speedbizhang_list[SPEED_LEVEL];          //���ϼ���    

extern uint16_t speedzhuanwan_list[SPEED_LEVEL];        //Ѱ���ű�ת���ٶ�
extern uint16_t speedzhuanwan2_list[SPEED_LEVEL];        //����ʱѰ���ű�ת���ٶ�

extern uint16_t chasu_low[2];
extern uint16_t chasu_high[2];

extern uint16_t turn[30];
extern uint16_t turn_route[30];

#endif