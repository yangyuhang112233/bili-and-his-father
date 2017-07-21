#include "head.h"

    int32_t qd_left_value;           //ʹ�õ������������ֵ
	int32_t qd_right_value;          //ʹ�õ��ұ���������ֵ

/*�ٶȿ��������*/
	uint8_t direction;       // ����
	uint8_t direction2;

 uint32_t Left_QD_value;      //�����������ֵ
 uint32_t Right_QD_value;     //�ұ���������ֵ      
 



/**************************************************************
* ��������:int32_t QD_value( void )
* �α�������������ȡ����
* ������ ��
**************************************************************/
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
		
}



/**************************************************************
* ��������:void Car_PWM_ChangeDuty(int32_t speed_duty,SpeedControl_Type dir)
* ��飺 ���ڵ�����PWMռ�ձ�
* ������ SpeedControl_Type----left or right
**************************************************************/
void Car_PWM_ChangeDuty(int8_t mode)
{
                uint16_t speed= 1000*mode;
	    switch( mode )
			{
				case 1:                 //ǰ��   pwmΪ2000
				{
			    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,8000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 8000); 
                FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
			  case 2:                 //������ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 3:                 //������ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,5000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 4:                 //������ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);//3000
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 5000); //7100
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 5:                 //������ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 6:                 // ���˲�����ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 6000);
				} break ;
				case 7:                 //�������
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9300);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9300);
				} break ;
				case 8:                 //�������
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9000);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9000);
				} break ;
				case 9:                 //��ת
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9300);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9300);
				} break ;
		    case 10:                 //��ת����  ��Ŀ��
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,4000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 6000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				 case 11:                 //��ת����  ��Ŀ��
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 4000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 12:                 //ǰ��   pwmΪ2000
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 6000);
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				
				case 13:              
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,1000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 1000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
					case 14:              
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,7500);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 7500); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				default :
					break ;	
            }                
}
