#include "head.h"

/**************************************************************
* ��飺���PD
**************************************************************/
 
     //������
  
	static uint16_t dooracc;
    static uint16_t doorslow;
    static int16_t Kp;
    static int16_t Kil;
    static int16_t Kir;
    
    static int16_t leftsum ;
    static int16_t rightsum ;
    
    
void Servo_Control()
{     
    uint16_t piancha1;
    
    //�ڳ����һ�ν���ѭ��ʱ���ó�ֵ
    if(anglenow==0)foreangle=anglex;
    
    
   //kd�������ö���ڱ仯��ʱ��仯�ĸ��죬����ﵽֱ��״̬�����м���
    
   anglenow=anglex-Kd*(foreangle-anglex)/10;  
     
     
     
     if(anglenow<angleright)anglenow=angleright;
     if(anglenow>angleleft)anglenow=angleleft;     
     
    
    //������ֻ������ʵ��
     CMT_PWM_ChangDuty (anglenow);
             
}



/**************************************************************
* ��������:void Motor_Control1(uint8_t start, uint8_t end)
* �α�����start��endͬ��
* ���:���PID
* ������ ��
**************************************************************/
//��һ������Ϊ����ת�٣��ڶ���Ϊ����ת��,pi����
void Motor_Control(uint16_t leftspeed,uint16_t rightspeed)
{   
      //����������
      int16_t lefterror;//�ٶ�ƫ��
      int16_t righterror;
    
      int32_t pwm_out1;//pwm���	
      int32_t pwm_out2;  
    
      uint16_t avespeed; //��ǰ�ٶ�
  
    float k1=1;//���ּ����ϵ��
    
      //״̬�ж��Լ�������ֵ��  
     avespeed=(qd_left_value+qd_right_value)/2;
    
   //  bool accflag;//�Ӽ��ٱ�־λ����Ҫ����Ϊ1����Ҫ����Ϊ0  
      
    //�ж�״̬�л��������л����״̬����pi����
    
         dooracc=10000;
         doorslow=10000;
        
uint8_t cha=0;
if(avespeed>speedx)
{
 cha=avespeed-speedx;
}
else
{
cha=speedx-avespeed;
}    

//     if(cha>5)
//{        
//}   
       if(Kp==0)  
   {
       Kp= 400;
             
       Kir= 0;
       Kil= 0;
       
       leftsum=2000;
       rightsum=2000;
   }


        if(state!=forestate)
        {
           switch(state)
              {
                case 0://�Ҳ����ű꣬תһת���ҵ��ű�
               Kp= 600;
                
                Kir= 0;
                Kil= 0;
                
               leftsum=1000;
               rightsum=1000;
                 
               
                
               if(forestate==3)
          {
              k1=1;
              Kp= 600;
            
           
                if(leftspeed>rightspeed)
                {
               Kil= 2;
               Kir= 0;
                    
                leftsum=800;
                rightsum=0;
                }
              else
               {
                   Kil= 0;
                    Kir= 2;
              
                   
                   
                leftsum=0;
                rightsum=800;               
              } 
          }
       
                break;
 
                
                case 1://�ҵ��ű��״̬������ǰ�����ϰ�����б���
                Kp= 1000;
                
                
                Kir= 0;
                Kil= 0;
                k1=1;
                break;
                
                case 2://�ҵ��ű��״̬��ǰ��û���ϰ��ǰ���ű�λ��
                k1=1;    
                
                if(speedx==speedjiasu) 
                {Kp= 800;
                    
                    
                Kir= 2;
                Kil= 2;
                    
                leftsum=800;
                rightsum=800;
                }
                
                if(speedx==speedxinjia)
                {Kp=500;
                    
                Kir= 1;
                Kil= 1;
                    
                leftsum=800;
                rightsum=800;
                }
                
                if(speedx==speedxinjiansu)
                {Kp=1300;
               
                Kir= 0;
                Kil= 0;
                
                }
                
                
                                       
                break;
                
               case 3://�����ű�����ű����
                k1=1;   
               if(qd_left_value+qd_left_value>22)
               { Kp= 1500;
               
               
                Kir= 0;
                Kil= 0;
               
               }
               else
               {
                Kp= 600;
                   
                Kir= 3;
                Kil= 3;
                   
                leftsum=800;
                rightsum=800;
               }
                                      
               break;
              }      
        }            
  
//                Kp= 600;Ki= 2;
//                leftsum=2000;
//                rightsum=2000;
//       if(state==3)
//     {
//             if(qd_left_value+qd_left_value<22)
//             {
//               speedx=speedxinbijia;              
//              }
//     }
                
     //pi����ʵ�� 
     
               
                
      lefterror = leftspeed - qd_left_value ;
      righterror= rightspeed - qd_right_value ;	
		
	  leftsum+= lefterror ;//���ֵ��ڵĻ�����
      rightsum  +=righterror ;
       
       
	  if(leftsum >= 800)leftsum = 800;
	  if(leftsum <= -400)leftsum = -400;
	  if(rightsum  >= 800) rightsum  = 800;
	  if(rightsum  <= -400)rightsum  = -400;
            
      pwm_out1 =   Kp*lefterror + Kil*leftsum  ;
	  pwm_out2 =   Kp*righterror + Kir*rightsum   ;

	  	
	  
	     
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
	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1);
		}
		else
		{
		pwm_out1 = -pwm_out1 ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0 );
		}
		
		if(pwm_out2 > 0)
		{
//			pwm_out2 = -pwm_out2 ;	//
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
		}
		else
		{
		pwm_out2 = -pwm_out2 ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
		}
}
