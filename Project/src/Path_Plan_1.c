/*   ·���滮Դ�ļ� ����*/
#include "Path_Plan_1.h"
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
#include "Path_Plan_2.h"
#include "Path_Plan_3.h"
#include "Path_Plan_4.h"

/* *************************************
*         ·�� 1
*****************************************/
/*  ·���滮  */
uint8_t TurnSide_Array_1[20]=// 1 �ұ�   0 ���  ���棺��2 �� 3 һ�ߣ��� 4 �� 5 
{
	//��һ��·����ʼ

	8,8,8,8,0,
	8,1,8,8,0,
	8,8,8,8,8,
	8,0,8,8,0,
};

/*  ���ٿ���   */
uint8_t Speed_Down_Array_1[20]=//�ڼ����Ʋ���Ҫ����ֱ�Ӹ���0 ����
//          ���ǣ� ��n�ζ�Ӧ�ŵ�n��Ԫ��
{
	//��һ���ƿ�ʼ ��һ�����п�ʼ
	1,1,0,1,0,
	0,0,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1
};

/*  ת�����   */
uint8_t No_Target_Turn_Array_1[20]=//Ŀ����ʧ��ʱ�� 1 ��ת  0��ת
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
uint8_t Pre_Turn_Array_1[20]=//ȷ����Ҫ��ǰ�����  1 ��Ҫ ; 
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

uint8_t Obs_Avoid_Array_1[20]=//����Ҫ����  ����� 1  ���� ���� 0
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





uint8_t path_i=1;
//ȫ�ֺ���
void PathChoose(void)//·��ѡ��
{
	LCD_printf(10,26,"PathChoose:");
	LCD_printf(10,39,"        ");
	LCD_printf(10,39,"%d",path_i);
	while(1)
	{
	while(GPIO_ReadBit(HW_GPIOD, 13)==1);
	while(GPIO_ReadBit(HW_GPIOD, 13)==0);
	while(GPIO_ReadBit(HW_GPIOD, 12)==1);
	while(GPIO_ReadBit(HW_GPIOD, 12)==0);
	if(GPIO_ReadBit(HW_GPIOB, 11))
	{
		path_i++;
		if(path_i>=5)
		{
			path_i=1;
		}
		LCD_printf(10,39,"        ");
		LCD_printf(10,39,"%d",path_i);
	}
	else
	{
		break;
	}
  }
	
	switch(path_i)
	{
		case 1:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_1[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_1[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_1[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_1[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_1[i];
			
		}
			
		}
			
			break;
		case 2:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_2[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_2[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_2[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_2[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_2[i];
			
		}
		}
			
			break;
		
		case 3:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_3[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_3[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_3[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_3[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_3[i];
			
		}
		}
			break;
		
		case 4:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_4[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_4[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_4[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_4[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_4[i];
			
		}
		}
			break;
		default: break;
	}
	
}



