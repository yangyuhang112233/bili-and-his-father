#ifndef _CANSHU_H_
#define _CANSHU_H_

#include "stdint.h"
#include "stdbool.h"

#define anglemid        813   //813  768
#define hide2_left      anglemid+48         //�ű���ϵ���ת���
#define hide2_right     anglemid-48         //�ű���ϵ���ת���
#define hide_left       anglemid+50         //������ת���
#define hide_right      anglemid-50         //������ת���
#define acc_left        anglemid+15         //���ٶζ���������
#define acc_right       anglemid-15         //���ٶȶζ���������
#define angleleft       anglemid+75         //�������
#define angleright      anglemid-75         //����Ҽ���

//�ٶ�
extern uint8_t speedzhuanwan2;
extern uint8_t speedzhuanwan;
extern uint8_t speedjiasu;
extern uint8_t speedxinjiansu;
extern uint8_t speedxinjia;
extern uint8_t speeddazhuan;
extern uint8_t speedbizhang;
extern int8_t speedxinbi1;
//���� ��־λ
extern uint8_t jioushu;
extern uint16_t foreangle;
extern uint8_t forestate;
extern uint16_t anglenow;//���ʵ�ʴ��
extern uint8_t count1;//�жϾ����˵ڼ����ű��
extern uint8_t turn[20];
extern uint8_t turn_route[20];
extern uint8_t count11[5];
extern uint8_t state0[10];
extern bool bama[4];
extern uint8_t state;//״̬��־λ
extern uint16_t speedx;//�ٶ�
extern uint16_t anglex;//�Ƕ�
extern uint8_t target_flag; //Ŀ���ҵ���־λ
extern uint16_t target_h;//Ŀ����
extern uint16_t target_l;//Ŀ����
extern uint32_t tt1;//��¼ʱ���
extern uint8_t barrier_h;//�ϰ���Ŀ����
extern uint8_t barrier_l;//�ϰ���Ŀ����
extern uint8_t  xideng;

//����
extern  uint16_t cammid;
extern float anglek;//���ϵ��
extern int16_t Kd;//������KD
extern uint16_t count7725;//7725�ɼ�����ֵ
extern bool xinbiaoqieguo;
extern uint16_t xinbiaoqieguo_h;
extern uint16_t acc_stop;
extern float pianchak;//ƫ�����ϵ��
extern uint16_t door7620;//7620����ͷ��ֵ
extern float k12;//���ٽ���ʱ�����������ϵ�� 
extern uint16_t stopbizhangh7725;
#endif