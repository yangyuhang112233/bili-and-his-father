#include "head.h"

uint16_t dooracc=10000;
uint16_t doorslow=10000;
int16_t Kp=400;
int16_t Ki=1;
int16_t leftsum =800;
int16_t rightsum =800;

void Servo_Control()
{     
    
    //在程序第一次进入循环时设置初值
    if(anglenow==0)foreangle=anglex;
        
    anglenow=anglex-Kd*(foreangle-anglex)/10;  

      
    if(anglenow<angleright)anglenow=angleright;
    if(anglenow>angleleft)anglenow=angleleft;     

    //舵机打角只在这里实现
    CMT_PWM_ChangDuty (anglenow);            
}

void Motor_Control(uint16_t leftspeed,uint16_t rightspeed)
{   
//基本变量：
int16_t lefterror;//速度偏差
int16_t righterror;
int32_t pwm_out1;//pwm输出	
int32_t pwm_out2;  
    

     if(state!=forestate)
     {
          switch(state)
        {
            case 0://找不到信标，转一转来找到信标
            Kp= 800;
            Ki= 0;
            break;

            case 1://找到信标的状态，遇到前方有障碍物，进行避障
            Kp= 800;              
            break;

            case 2://找到信标的状态，前方没有障碍物，前往信标位置
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

            case 3://靠近信标进行信标避障
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

        leftsum+= lefterror ;//积分调节的积分量
        rightsum  +=righterror ;
       
        if(leftsum >= 800)leftsum = 800;
        if(leftsum <= -400)leftsum = -400;
        if(rightsum  >= 800) rightsum  = 800;
        if(rightsum  <= -400)rightsum  = -400;
            
        pwm_out1 =   Kp*lefterror + Ki*leftsum  ;
        pwm_out2 =   Kp*righterror + Ki*rightsum   ;
	     
        //防止值超过限度
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
