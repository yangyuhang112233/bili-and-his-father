/*   路径规划源文件 数组*/
#include "Path_Plan_4.h"
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

/* *************************************
*         路径 4
*****************************************/
/*  路径规划  */
uint8_t TurnSide_Array_4[20]=// 1 右边   0 左边  交叉：左2 右 3 一边：左 4 右 5 
{
	//第一个路径开始

	8,8,8,8,0,
	8,1,8,8,0,
	8,8,8,8,8,
	8,0,8,8,0,
};

/*  减速控制   */
uint8_t Speed_Down_Array_4[20]=//第几个灯不需要减速直接给定0 即可
//          助记： 第n段对应着第n个元素
{
	//第一个灯开始 第一段运行开始
	1,1,0,1,0,
	1,0,1,1,0,
	1,1,1,1,1,
	1,1,1,1,1
};

/*  转向控制   */
uint8_t No_Target_Turn_Array_4[20]=//目标消失的时候 1 右转  0左转
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
uint8_t Pre_Turn_Array_4[20]=//确定需要提前打角吗？  1 需要 ; 
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

uint8_t Obs_Avoid_Array_4[20]=//若需要避障  则给定 1  否则 给定 0
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
