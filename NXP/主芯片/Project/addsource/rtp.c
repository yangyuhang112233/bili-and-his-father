#include "rtp.h"

uint16_t speed_level_selection=0;
uint16_t cam_back=0;
uint16_t route_selection_switch=0;

void camstop()	//摄像头倒车
{
	static uint16_t jishu2;
	if(target_flag==0)
	{
		jishu2++;
	}
	else
	{
		jishu2=0;
	}
	
	if(jishu2>200)
	{
		CMT_PWM_ChangDuty(anglemid);
		PID_speed_set(-400,-400);
		DelayMs(700);
		jishu2=0;
	}
}

void real_time_process(void)
{  
	firstimage();
	
	speed_level_selection=bamaa[0];
	cam_back=bamaa[2];
	route_selection_switch=bamaa[3];
	
	speedjiasu = speedjiasu_list[speed_level_selection];        //远离信标 直线加速  
	speedxinjiansu = speedxinjiansu_list[speed_level_selection];        //靠近信标 进行减速 
	speedxinbi1 = speedxinbi1_list[speed_level_selection];        //信标避障减速    
	speedxinjia = speedxinjia_list[speed_level_selection];        //靠近信标 速度太慢 而加速

	speeddazhuan = speeddazhuan_list[speed_level_selection];         //找不到信标大转弯速度    
	speedbizhang = speedbizhang_list[speed_level_selection];          //避障减速    

	speedzhuanwan = speedzhuanwan_list[speed_level_selection];        //寻找信标转弯速度
	speedzhuanwan2 = speedzhuanwan2_list[speed_level_selection];        //低速时寻找信标转弯速度    
	
    while(1)
    {           
		beacon_right_flag=PCin(0);
		
	   GPIO_ToggleBit(HW_GPIOD, 15); 
       startimage();
            
       //一：根据图像设定不同标志位           
	   findpoint();
	   findbarrier();
		barrier=0;
		
		
                   
		
        if(target_flag==0)
        {
           state=0;
        }
        else
        {
            if(xinbiaoqieguo==1)
            {
            state=3;
            }
            else 
            {
                if(barrier==1)
                {
                state=1;
                }
                else
               {
                state=2;
               }
            }     
        }

        
   //三：根据状态的不同执行相应的操作
        
        switch(state)
              {
                case 0://找不到信标，转一转来找到信标
					lookfor();
                break;

                case 1://找到信标的状态，遇到前方有障碍物，进行避障
					bizhang();             
                break;

                case 2://找到信标的状态，前方没有障碍物，前往信标位置
					gothere();   
                break;

                case 3: //信标切过                         
					gothere1();     
                break; 
				
                default:
					lookfor();
                break;     
              }
              
                   
      //四：舵机打角和电机速度改变           
       move();
             	
      //五：判断经过了一个灯   等待采集图像完成  储存前一个状态的变量
       pass();       

		if(stop_flag)
		{
			Car_stop();
		}
			  
		endimage();               
		prestate();     
		touchswitch();
		
		if(cam_back)
		{
			camstop();
		}
    }   
}