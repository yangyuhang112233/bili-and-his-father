/*   ·���滮Դ�ļ� ����*/
#include "Path_Plan_4.h"
#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "dma.h"
#include "io2iic.h"
#include "ov7620.h"
#include "ftm.h"
#include "cmt.h"
#include "adc.h"
#include "lptmr.h"
#include "img_processing.h"
#include "Drv_LCD.h"
#include "img_save.h"
#include "control.h"
#include "wdog.h"
#include "pit.h"
#include "ov7725.h"
#include "ov7725_Init.h"
#include "img_save.h"
#include "sd.h"

#include <stdint.h>

/* *************************************
*         ·�� 4
*****************************************/
/*  ·���滮  */
uint8_t TurnSide_Array_4[20]=// 1 �ұ�   0 ���  ���棺��2 �� 3 һ�ߣ��� 4 �� 5 
{
	//��һ��·����ʼ

	8,8,8,8,0,
	8,1,8,8,0,
	8,8,8,8,8,
	8,0,8,8,0,
};

/*  ���ٿ���   */
uint8_t Speed_Down_Array_4[20]=//�ڼ����Ʋ���Ҫ����ֱ�Ӹ���0 ����
//          ���ǣ� ��n�ζ�Ӧ�ŵ�n��Ԫ��
{
	//��һ���ƿ�ʼ ��һ�����п�ʼ
	1,1,0,1,0,
	1,0,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1
};

/*  ת�����   */
uint8_t No_Target_Turn_Array_4[20]=//Ŀ����ʧ��ʱ�� 1 ��ת  0��ת
//          ��n����Ϩ����ת��Ϊ ��n+1 �� Ԫ��
{
	1,//������
//	��һ���ƿ�ʼ
  1,1,1,0,0,
	0,1,1,1,0,
	1,1,1,0,0,
	1,1,1,1
	 
};

/*  ��ǰ��ǿ���   */
uint8_t Pre_Turn_Array_4[20]=//ȷ����Ҫ��ǰ�����  1 ��Ҫ ; 
                           //                      0 ����Ҫ
                           //  �����n���Ƶ�ʱ��Ϊ����� �� n ��Ԫ��
{
  1,1,1,1,0,
	1,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0
//	0,1,1,1,1,
//	1,0,
//	1,1,0,1,1,
//	1,1,
//	0,0,0,0,0,0
};

uint8_t Obs_Avoid_Array_4[20]=//����Ҫ����  ����� 1  ���� ���� 0
{
	0,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1
	
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0
};
