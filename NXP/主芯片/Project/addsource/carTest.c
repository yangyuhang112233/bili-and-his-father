#include "carTest.h"

void low_speed_mode()
{
	firstimage();
	while(1)
	{   
		beacon_right_flag=PCin(0);
		GPIO_ToggleBit(HW_GPIOD, 15);  //С����˸��ʾ����ѭ��
		startimage();  //��ʼ�ɼ�ͼ�������   

		//һ������ͼ���趨��ͬ��־λ        
		findpoint();//�ж��Ƿ��ҵ��ű꣬�������ű�λ�úͱ�־λ,�ж��Ƿ�������ͱ���ϣ��Ƿ����ű����     
		findbarrier();//�ж�ǰ���Ƿ���Ҫ��ͨ���� 
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


		//��������״̬�Ĳ�ִͬ����Ӧ�Ĳ���

		switch(state)
		{
			case 0://�Ҳ����ű꣬תһת���ҵ��ű�
			lookfor();
			break;

			case 1://�ҵ��ű��״̬������ǰ�����ϰ�����б���
			bizhang();             
			break;

			case 2://�ҵ��ű��״̬��ǰ��û���ϰ��ǰ���ű�λ��
			gothere();   
			break;

			case 3: //�ű��й�                         
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
