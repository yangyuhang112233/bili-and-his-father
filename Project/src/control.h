#ifndef _CONTROL_H_
#define _CONTROL_H_

#include <stdint.h>
#include "common.h"

extern int32_t qd_left_value;           //ʹ�õ������������ֵ
extern	int32_t qd_right_value;          //ʹ�õ��ұ���������ֵ

/*���ռ�ձȿ��ƺ���*/
void Car_PWM_ChangeDuty(int8_t mode);
	
/*��������ȡ����*/
void QD_value( void );

#endif
