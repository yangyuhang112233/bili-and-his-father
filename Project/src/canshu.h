#ifndef _CANSHU_H_
#define _CANSHU_H_


#include "stdint.h"
#include "stdbool.h"


//���ñ�������ʽ

////�̶����ٶ��ٶȣ������ú���
//#define  speedzhuanwan   15  //Ѱ���ű�ת���ٶ�
//#define  speedjiasu      30  //Զ���ű� ֱ�߼���
//#define  speedxinjiansu  10  //�����ű� ���м���
//#define  speedxinjia     25  //�����ű� �ٶ�̫�� ������
//#define  speeddazhuan    15  //�Ҳ����ű��ת���ٶ�
//#define  speedbizhang    10   //���ϼ���
//#define  speedxinbi      10   //�ű���ϼ���
//#define  speedxinbijia      15   //�ű����ʱ̫���������
//20 34 26 15 10 10  �ϵ��
//27 40 18 22 7 9
extern    uint8_t speedxinjia2;          //�����ű� �ٶ�̫�� ������
extern    uint8_t speedxinjiansu2;        //�����ű� ���м���
 extern   uint8_t speedjiasu2;            //Զ���ű� ֱ�߼���
extern uint8_t  kaiqi;
extern uint8_t speedzhuanwan2;
extern uint8_t  xideng;
extern uint8_t speedzhuanwan;
extern uint8_t speedjiasu;
extern uint8_t speedxinjiansu;
extern uint8_t speedxinjia;
extern uint8_t speeddazhuan;
extern uint8_t speedbizhang;
extern int8_t speedxinbi1;
//extern uint8_t speedxinbijia;
extern int8_t speedxinbi2;
extern uint8_t jioushu;
extern uint16_t foreangle;
extern  uint16_t cammid;
extern int16_t Kd;

extern uint8_t target_flag; //Ŀ���ҵ���־λ
extern uint16_t target_h;//Ŀ����
extern uint16_t target_l;//Ŀ����
extern uint32_t tt1;//��¼ʱ���
extern uint8_t forestate;
extern uint16_t stopbizhangh7620;//�ű�������С�����ֵʱ��������ͨ���
extern uint16_t stopbizhangh7725;
extern bool stopba;//ֹͣ��ͨ���ϵı�־λ
extern uint8_t h7620;  
extern bool barrier;//�ϰ����ҵ���־λ
extern uint8_t barrier_h;//Ŀ����
extern uint8_t barrier_l;//Ŀ����
extern uint16_t anglenow;//���ʵ�ʴ��
extern uint8_t count1;//�жϾ����˵ڼ����ű��
extern bool seepoint;//�ж��Ƿ��ڱ��Ϻ��Ҳ����ű�
extern bool xinbiaobizhang;//�ű���ϱ�־λ
extern float k11;
extern float k12;
extern uint8_t turn[20];
extern uint16_t xiangsuzh;
extern uint16_t acc_stop2;//���ٽ���ʱ��������
extern uint16_t acc_stop1;
extern uint16_t speedx;//�ٶ�
extern uint16_t anglex;//�Ƕ�
extern int c;
extern uint8_t barrier2_h;//�ϰ���Ŀ����
extern uint8_t barrier2_l;//�ϰ���Ŀ����

extern uint16_t anglemid;//�����ֵ
extern uint16_t angleleft;//�������
extern uint16_t angleright;//����Ҽ���
extern float anglek;//���ϵ��
extern uint16_t count7725;//7725�ɼ�����ֵ

extern uint8_t state;//״̬��־λ

extern float pianchak;//ƫ�����ϵ��

extern uint8_t xiangsuzhi;
extern uint16_t door7620;//7620����ͷ��ֵ
extern uint16_t jishuwei;
extern uint8_t count11[5];

extern uint16_t xinbiaobizhang_h;//�ű����������
extern uint16_t door_7620;//7725���Ϸ�ֵ
extern bool xinbiaoqieguo;
extern uint16_t hide_left;//������ת���
extern uint16_t hide_right;//������ת���
extern uint16_t xinbiaoqieguo_h;
extern uint16_t hide2_left;//�ű���ϵ���ת���
extern uint16_t hide2_right;//�ű���ϵ���ת���

extern uint16_t acc_left;//���ٶζ���������
extern uint16_t acc_right;//���ٶȶζ���������

extern uint16_t acc_stop;//���ٽ���ʱ��������

extern uint16_t delay1;//7725������ʱ
extern uint16_t delay2;//7620������ʱ
extern uint8_t state0[10];
extern bool bama[4];

#endif