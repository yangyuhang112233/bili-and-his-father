#include "delay.h"

uint16_t tt=0;//��ʼ��1ms�жϺ����ı���

uint16_t delay_flag=DELAY_END;

void delay_ms( uint16_t ms )
{
	if (delay_flag==DELAY_END)
	{
		delay_flag=DELAY_START;
		tt=0;
	}
	while(tt<ms)
	{
	}
	delay_flag=DELAY_END;
}
