#include "head.h"
#include "key.h"
            
uint8_t bamakaiguan=0;//拔码开关状态
uint16_t xinbiaoxiangsu;//信标像素个数
uint16_t xinbiao0[10];//过去的信标像素值
uint8_t xinbiaobiaozhi=0;//判定是否信标像素个数超过400
uint8_t xidengshu=0;//熄过得灯的个数
uint8_t laststate=0;
uint8_t pass_beacon_number;
uint8_t drive_back=0;
uint16_t car_back_delay=0;

 void speedset()
 {
     switch(count1)
     {

        case 1:
        speedjiasu=     15;           //远离信标 直线加速  
        speedxinjiansu= 10;           //靠近信标 进行减速   
        speedxinjia=    10;          //靠近信标 速度太慢 而加速 
        break;

        case 2:
        speedjiasu=     27;           //远离信标 直线加速  
        speedxinjiansu= 16;           //靠近信标 进行减速   
        speedxinjia=    25;          //靠近信标 速度太慢 而加速  
        break;

        default:
        break;
     }
}
 
void pass()
{
if(xinbiaobiaozhi==0)
   {
      if(xinbiaoxiangsu>350&&target_h<23)
      {
      xinbiaobiaozhi=1;      
      }
   }
else
   {
     if(xinbiaoxiangsu<180)
     {
        count1++;
        xidengshu++;
        xinbiaobiaozhi=0;
     }         
   }
      if(count1>=29)count1=0;
   
   pass_beacon_number=PASS_BEACONS;
	//停止运动
	if(pass_beacon_number!=0)
	{
		if(xidengshu>=pass_beacon_number)   
		{        
			stop_flag=1;
		}  
	}
	else 
	{
		return;
	}

}

void touchswitch()
{
    static bool a;
    static bool b;
    static uint16_t jishu1;
    
	car_back_delay=bamaa[1];
	
    a=0;
    b=0;
	if(GPIO_ReadBit(HW_GPIOA, 4)==0)    //碰撞开关检测 
    {
      a=1;
    }     
    if(GPIO_ReadBit(HW_GPIOA, 5)==0)    //碰撞开关检测
    {
      b=1;
    }
      if(a==1||b==1)
      {
      jishu1++;
      }
      else
          jishu1=0;
      
      //倒车
	  if(car_back_delay==1)
	  {
		  drive_back=DAOCHE_JUESAI;
	  }
	  else
	  {
		  drive_back=DAOCHE_YUSAI;
	  }
      if(jishu1>drive_back)
      {       
        CMT_PWM_ChangDuty (anglemid);     
        PID_speed_set(-400,-400);               
        DelayMs(500);         
      }   
}

  //储存前一个状态的变量
void prestate()
{   
    if(forestate!=state)
    {
    laststate=forestate;
    } 

    forestate=state;
    foreangle=anglex;
  

    for(uint8_t i=4;i>0;i--)
    {
    count11[i]=count11[i-1];
    }
    count11[0]=count1;

    
    for(uint8_t i=9;i>0;i--)
    {
    state0[i]=state0[i-1];
    }
    state0[0]=state;
    
    
    for(uint8_t i=9;i>0;i--)
    {
    xinbiao0[i]=xinbiao0[i-1];
    }
    xinbiao0[0]=xinbiaoxiangsu;
}


