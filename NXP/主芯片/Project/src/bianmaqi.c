#include "head.h"

int16_t qd_left_value;           //ʹ�õ������������ֵ
int16_t qd_right_value;          //ʹ�õ��ұ���������ֵ
int16_t avespeed; //��ǰ�ٶ�

uint8_t direction;   
uint8_t direction2;
uint32_t Left_QD_value;      //�����������ֵ
uint32_t Right_QD_value;     //�ұ���������ֵ      

void QD_value( void )
{
    FTM_QD_GetData(HW_FTM1, &Left_QD_value, &direction);
    FTM_QD_ClearCount(HW_FTM1);            //��ʱ20ms  ��¼����������
    FTM_QD_GetData(HW_FTM2, &Right_QD_value, &direction2);
    FTM_QD_ClearCount(HW_FTM2);            //��ʱ20ms  ��¼����������
        
	//�����ӷ�ת��ʱ�򣬱����������ݴ�65535���¼�����ת��ʱ���0���ϼ�
	if(Left_QD_value>60000)
		Left_QD_value=-65536+Left_QD_value;
	if(Right_QD_value>60000)
		Right_QD_value=-65536+Right_QD_value;
		
	qd_left_value=Left_QD_value;
	qd_right_value=-Right_QD_value;
    avespeed=(qd_left_value+qd_right_value)/2;
}
