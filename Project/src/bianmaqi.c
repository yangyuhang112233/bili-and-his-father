#include "head.h"

int16_t qd_left_value;           //使用的左编码器计数值
int16_t qd_right_value;          //使用的右编码器计数值
int16_t avespeed; //当前速度

uint8_t direction;   
uint8_t direction2;
uint32_t Left_QD_value;      //左编码器计数值
uint32_t Right_QD_value;     //右编码器计数值      

void QD_value( void )
{
    FTM_QD_GetData(HW_FTM1, &Left_QD_value, &direction);
    FTM_QD_ClearCount(HW_FTM1);            //延时20ms  记录编码器数据
    FTM_QD_GetData(HW_FTM2, &Right_QD_value, &direction2);
    FTM_QD_ClearCount(HW_FTM2);            //延时20ms  记录编码器数据
        
	//当轮子反转的时候，编码器的数据从65535往下减。正转的时候从0往上加
	if(Left_QD_value>60000)
		Left_QD_value=-65536+Left_QD_value;
	if(Right_QD_value>60000)
		Right_QD_value=-65536+Right_QD_value;
		
	qd_left_value=Left_QD_value;
	qd_right_value=-Right_QD_value;
    avespeed=(qd_left_value+qd_right_value)/2;
}
