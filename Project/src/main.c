#include "head.h"
#include "key.h"
#include "rtp.h"
#include "carTest.h"

uint32_t mode_selection;
uint32_t mode_data;


int main()
{
	jioushu=1;//用于7620和7725两幅图片的轮流采集和处理 
    getready();  
    mode_selection = switch_mode_selection();
	mode_data = switch_mode_data();
    
	while(1)
	{
		switch(mode_selection)
		{
			case 0:
				real_time_process();
			break;
			case 1:
				Printf();
			break;
			case 2:
				low_speed_mode();
			break;
			case 3:
				GPIO_ToggleBit(HW_GPIOD, 15); 
				startimage();
				sending3();
				endimage();  
			break;
			case 7:
				hardware_test(mode_data);	
			break;
			default:
				real_time_process();
			break;
		}
	}
}