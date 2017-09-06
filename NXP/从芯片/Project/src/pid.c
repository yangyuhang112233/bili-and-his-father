#include "head.h"

uint16_t dooracc=10000;
uint16_t doorslow=10000;
int16_t Kp=400;
int16_t Ki=1;
int16_t leftsum =800;
int16_t rightsum =800;

void Servo_Control()
{     
    
    //�ڳ����һ�ν���ѭ��ʱ���ó�ֵ
    if(anglenow==0)foreangle=anglex;
        
    anglenow=anglex-Kd*(foreangle-anglex)/10;  

      
    if(anglenow<angleright)anglenow=angleright;
    if(anglenow>angleleft)anglenow=angleleft;     

    //������ֻ������ʵ��
    CMT_PWM_ChangDuty (anglenow);            
}

void Motor_Control(uint16_t leftspeed,uint16_t rightspeed)
{   
//����������
int16_t lefterror;//�ٶ�ƫ��
int16_t righterror;
int32_t pwm_out1;//pwm���	
int32_t pwm_out2;  
    

     if(state!=forestate)
     {
          switch(state)
        {
            case 0://�Ҳ����ű꣬תһת���ҵ��ű�
            Kp= 800;
            Ki= 0;
            break;

            case 1://�ҵ��ű��״̬������ǰ�����ϰ�����б���
            Kp= 800;              
            break;

            case 2://�ҵ��ű��״̬��ǰ��û���ϰ��ǰ���ű�λ��
            if(speedx==speedjiasu) 
            {
            Kp= 800;                          
//            Ki= 2;
//            leftsum=800;
//            rightsum=800;
            }

            if(speedx==speedxinjia)
            {
            Kp=800;
            Ki= 1;
            leftsum=800;
            rightsum=800;
            }

            if(speedx==speedxinjiansu)
            {
            Kp=1000;               
            Ki= 0;               
            }                                    
            break;

            case 3://�����ű�����ű����
            if(avespeed>11)
            {
            Kp= 2500;
            Ki= 0;
            }
            else
            {
            Kp= 800;
            Ki= 3;
            leftsum=800;
            rightsum=800;
            }                          
            break;

            default:
            break;
        }      
    }           
                                            
        lefterror = leftspeed - qd_left_value ;
        righterror= rightspeed - qd_right_value ;	

        leftsum+= lefterror ;//���ֵ��ڵĻ�����
        rightsum  +=righterror ;
       
        if(leftsum >= 800)leftsum = 800;
        if(leftsum <= -400)leftsum = -400;
        if(rightsum  >= 800) rightsum  = 800;
        if(rightsum  <= -400)rightsum  = -400;
            
        pwm_out1 =   Kp*lefterror + Ki*leftsum  ;
        pwm_out2 =   Kp*righterror + Ki*rightsum   ;
	     
        //��ֵֹ�����޶�
		if(pwm_out1>=dooracc)
		{
			pwm_out1=dooracc;
		}
		if(pwm_out2>=dooracc)
		{
			pwm_out2=dooracc;
		}
        
		if(pwm_out1<-doorslow)
		{
			pwm_out1=-doorslow;
		}
		if(pwm_out2<-doorslow)
		{
			pwm_out2=-doorslow;
		}
	     
	    if(pwm_out1 > 0)
		{
	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
		}
		else
		{
		pwm_out1 = -pwm_out1 ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1 );
		}
		
		if(pwm_out2 > 0)
		{
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
		}
		else
		{
		pwm_out2 = -pwm_out2 ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
		}
        
//        if(pwm_out1 > 0)
//		{
//	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1);
//		}
//		else
//		{
//		pwm_out1 = -pwm_out1 ;	
//		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
//		}
//		
//		if(pwm_out2 > 0)
//		{
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
//		}
//		else
//		{
//		pwm_out2 = -pwm_out2 ;	
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
//		}
}
