#include "head.h"

/**************************************************************
* 简介：舵机PD
**************************************************************/
 
     //参数：
  
	static uint16_t dooracc;
    static uint16_t doorslow;
    static int16_t Kp;
    static int16_t Ki;
  
    static int16_t leftsum ;
    static int16_t rightsum ;
    
    
void Servo_Control()
{     
    uint16_t piancha1;
    
    //在程序第一次进入循环时设置初值
    if(anglenow==0)foreangle=anglex;
    
    
   //kd作用是让舵机在变化的时候变化的更快，更快达到直线状态来进行加速
    
   anglenow=anglex-Kd*(foreangle-anglex)/10;  
     
     
     
     if(anglenow<angleright)anglenow=angleright;
     if(anglenow>angleleft)anglenow=angleleft;     
     
    
    //舵机打角只在这里实现
     CMT_PWM_ChangDuty (anglenow);
             
}



/**************************************************************
* 函数名称:void Motor_Control1(uint8_t start, uint8_t end)
* 参变量：start，end同上
* 简介:电机PID
* 变量： 无
**************************************************************/
//第一个参数为左轮转速，第二个为右轮转速,pi控速
void Motor_Control(uint16_t leftspeed,uint16_t rightspeed)
{   
      //基本变量：
      int16_t lefterror;//速度偏差
      int16_t righterror;
    
      int32_t pwm_out1;//pwm输出	
      int32_t pwm_out2;  
    
      uint16_t avespeed; //当前速度
  
    
      //状态判断以及参数赋值：  
     avespeed=(qd_left_value+qd_right_value)/2;
    
   //  bool accflag;//加减速标志位。需要加速为1，需要减速为0  
      
    //判断状态切换。根据切换后的状态重置pi参数
    
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
        if(state!=forestate)
        {
           switch(state)
              {
                case 0://找不到信标，转一转来找到信标
                Kp= 600;Ki= 1;
               leftsum=1000;
                rightsum=1000;
                
                break;
 
                
                case 1://找到信标的状态，遇到前方有障碍物，进行避障
                Kp= 1000;Ki= 0;
              
                break;
                
                case 2://找到信标的状态，前方没有障碍物，前往信标位置
                if(speedx==speedjiasu) 
                {Kp= 800;Ki= 2;
                leftsum=2000;
                rightsum=2000;
                }
                
                if(speedx==speedxinjia)
                {Kp=500;Ki=1;  
                leftsum=1000;
                rightsum=1000;
                }
                
                if(speedx==speedxinjiansu)
                {Kp=1300;Ki=0;}
                
                
                                       
                break;
                
               case 3://靠近信标进行信标避障
                   
               if(qd_left_value+qd_left_value>22)
               { Kp= 1500;Ki= 1;}
               else
               {
                Kp= 600;Ki= 3;
                leftsum=1300;
                rightsum=1300;
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
                
     //pi具体实现 
     
               
                
      lefterror = leftspeed - qd_left_value ;
      righterror= rightspeed - qd_right_value ;	
		
	  leftsum+= lefterror ;//积分调节的积分量
      rightsum  += righterror ;
       
       
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
}
