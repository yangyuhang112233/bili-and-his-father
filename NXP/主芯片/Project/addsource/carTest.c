#include "carTest.h"

void low_speed_mode()
{
	firstimage();
	while(1)
	{   
		beacon_right_flag=PCin(0);
		GPIO_ToggleBit(HW_GPIOD, 15);  //小灯闪烁表示进入循环
		startimage();  //开始采集图像的配置   

		//一：根据图像设定不同标志位        
		findpoint();//判断是否找到信标，并更新信标位置和标志位,判断是否屏蔽普捅避障，是否开启信标避障     
		findbarrier();//判断前方是否需要普通避障 
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
			break;     
		}
		
		move();
		
		pass();
		
		if(stop_flag)
		{
			Car_stop();
		}
		else
		{
			PID_speed_set(200,200);
		}
		endimage();
		prestate();
		touchswitch();
		camstop();
	}   
}

void hardware_test( uint32_t data )
{
	switch (data)
	{
		case 0:
			test_PWM();
		break;
		case 1:
			test_accelerate();
		break;
		case 2:
			test_PID();
		default:
			Car_stop();
		break;
	}
}

void test_PWM()
{
	while(1)
	{
		Motor_PWM_Output(6000,6000);
	}
}

void test_accelerate()
{
	PID_speed_set(600,600);
	delay_ms(1000);
	while(1)
	{
		Car_stop();
	}
}

void test_PID()
{
	while(1)
	{
		PID_speed_set(100,100);
		delay_ms(500);
		GPIO_ToggleBit(HW_GPIOD, 15); 
		PID_speed_set(0,0);
		delay_ms(500);
		GPIO_ToggleBit(HW_GPIOD, 15); 
	}
}
