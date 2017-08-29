#include "head.h"

uint8_t stop_flag=0;

void move()
{        
    //舵机打角控制
    Servo_Control();
    
    //防止速度过低
 if(state!=1)
 {
    if(target_h<50)
    {
      if(avespeed<200)
      {
      speedx=250;
      }
    }
  }
	
uint16_t leftspeed=0;
uint16_t rightspeed=0;//左右轮设定速度

    
         if(anglenow>anglemid-51&&anglenow<anglemid+51) 
      {
        rightspeed=speedx;
        leftspeed=speedx;         
      }        
      else
      {        
        if(anglenow<anglemid-50)
        {
        rightspeed=speedx;
        leftspeed=1*speedx;       
        }
        else
        {
        rightspeed=1*speedx;
        leftspeed=speedx;       
        }        
      } 
      
        if(state==0)
        {
         if(anglex==angleleft)
           {
			   if((mode_selection==2)||((mode_selection==0)&&(mode_data==(SPEED_LEVEL-1))))
			   {
				   PID_speed_set(chasu_low[1],chasu_high[1]);
			   }
			   else
			   {
				   PID_speed_set(chasu_low[0],chasu_high[0]);
			   }
           }		   
           else 
           {
				if((mode_selection==2)||((mode_selection==0)&&(mode_data==(SPEED_LEVEL-1))))
				{
					PID_speed_set(chasu_high[1],chasu_low[1]);
				}
				else
				{
					PID_speed_set(chasu_high[0],chasu_low[0]);
				}
     
           }
        }
        else 
        {  
           PID_speed_set(leftspeed,rightspeed);   
        }

       
        if(state==1)
       {           
           DelayMs(10);
           if(avespeed<18) DelayMs(10);
       } 

       if(state==3)
       {
            for(int co1=0;co1<2;co1++)
            {              
             PID_speed_set(leftspeed,rightspeed);
             DelayMs(3);
            }     
       }  
}
  
  