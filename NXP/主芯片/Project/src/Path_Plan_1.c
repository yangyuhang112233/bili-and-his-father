/*   路径规划源文件 数组*/
#include "Path_Plan_1.h"
#include "gpio.h"
#include "common.h"
#include "uart.h"
#include "dma.h"
#include "io2iic.h"
#include "ov7620.h"
#include "ftm.h"
#include "cmt.h"
#include "adc.h"
#include "lptmr.h"
#include "img_processing.h"
#include "Drv_LCD.h"
#include "img_save.h"
#include "control.h"
#include "wdog.h"
#include "pit.h"
#include "ov7725.h"
#include "ov7725_Init.h"
#include "img_save.h"
#include "sd.h"
#include <stdint.h>
#include "Path_Plan_2.h"
#include "Path_Plan_3.h"
#include "Path_Plan_4.h"

/* *************************************
*         路径 1
*****************************************/
/*  路径规划  */
uint8_t TurnSide_Array_1[20]=// 1 右边   0 左边  交叉：左2 右 3 一边：左 4 右 5 
{
	//第一个路径开始

	8,8,8,8,0,
	8,1,8,8,0,
	8,8,8,8,8,
	8,0,8,8,0,
};

/*  减速控制   */
uint8_t Speed_Down_Array_1[20]=//第几个灯不需要减速直接给定0 即可
//          助记： 第n段对应着第n个元素
{
	//第一个灯开始 第一段运行开始
	1,1,0,1,0,
	0,0,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1
};

/*  转向控制   */
uint8_t No_Target_Turn_Array_1[20]=//目标消失的时候 1 右转  0左转
//          第n个灯熄灭后的转向为 第n+1 个 元素
{
	1,//无作用
//	第一个灯开始
  1,1,1,0,0,
	0,1,1,1,0,
	1,1,1,0,0,
	1,1,1,1
	 
};

/*  提前打角控制   */
uint8_t Pre_Turn_Array_1[20]=//确定需要提前打角吗？  1 需要 ; 
                           //                      0 不需要
                           //  进入第n个灯的时候为数组的 第 n 个元素
{
  1,1,1,1,0,
	1,0,1,1,0,
	0,0,0,0,0,
	0,0,0,0,0
//	0,1,1,1,1,
//	1,0,
//	1,1,0,1,1,
//	1,1,
//	0,0,0,0,0,0
};

uint8_t Obs_Avoid_Array_1[20]=//若需要避障  则给定 1  否则 给定 0
{
	0,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1,
	1,1,1,1,1
	
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0,
//	0,0,0,0,0
};





uint8_t path_i=1;
//全局函数
void PathChoose(void)//路径选择
{
	LCD_printf(10,26,"PathChoose:");
	LCD_printf(10,39,"        ");
	LCD_printf(10,39,"%d",path_i);
	while(1)
	{
	while(GPIO_ReadBit(HW_GPIOD, 13)==1);
	while(GPIO_ReadBit(HW_GPIOD, 13)==0);
	while(GPIO_ReadBit(HW_GPIOD, 12)==1);
	while(GPIO_ReadBit(HW_GPIOD, 12)==0);
	if(GPIO_ReadBit(HW_GPIOB, 11))
	{
		path_i++;
		if(path_i>=5)
		{
			path_i=1;
		}
		LCD_printf(10,39,"        ");
		LCD_printf(10,39,"%d",path_i);
	}
	else
	{
		break;
	}
  }
	
	switch(path_i)
	{
		case 1:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_1[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_1[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_1[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_1[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_1[i];
			
		}
			
		}
			
			break;
		case 2:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_2[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_2[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_2[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_2[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_2[i];
			
		}
		}
			
			break;
		
		case 3:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_3[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_3[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_3[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_3[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_3[i];
			
		}
		}
			break;
		
		case 4:
		{
			for(uint8_t i=0;i<20;i++)
		{
			TurnSide_Array[i]=TurnSide_Array_4[i];
			
			Speed_Down_Array[i]=Speed_Down_Array_4[i];
			
			No_Target_Turn_Array[i]=No_Target_Turn_Array_4[i];
			
			Pre_Turn_Array[i]=Pre_Turn_Array_4[i];
			
			Obs_Avoid_Array[i]=Obs_Avoid_Array_4[i];
			
		}
		}
			break;
		default: break;
	}
	
}



