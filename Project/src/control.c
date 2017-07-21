#include "head.h"

    int32_t qd_left_value;           //使用的左编码器计数值
	int32_t qd_right_value;          //使用的右编码器计数值

/*速度控制相关量*/
	uint8_t direction;       // 方向
	uint8_t direction2;

 uint32_t Left_QD_value;      //左编码器计数值
 uint32_t Right_QD_value;     //右编码器计数值      
 



/**************************************************************
* 函数名称:int32_t QD_value( void )
* 参变量：编码器读取函数
* 变量： 无
**************************************************************/
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
		
}



/**************************************************************
* 函数名称:void Car_PWM_ChangeDuty(int32_t speed_duty,SpeedControl_Type dir)
* 简介： 用于电机输出PWM占空比
* 参数： SpeedControl_Type----left or right
**************************************************************/
void Car_PWM_ChangeDuty(int8_t mode)
{
                uint16_t speed= 1000*mode;
	    switch( mode )
			{
				case 1:                 //前进   pwm为2000
				{
			    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,8000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 8000); 
                FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
			  case 2:                 //避障右转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 3:                 //差速右转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,5000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 4:                 //差速左转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);//3000
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 5000); //7100
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 5:                 //避障左转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,3000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 3000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 6:                 // 后退差速左转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 6000);
				} break ;
				case 7:                 //反向减速
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9300);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9300);
				} break ;
				case 8:                 //正向减速
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9000);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9000);
				} break ;
				case 9:                 //反转
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,9300);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 9300);
				} break ;
		    case 10:                 //左转差速  朝目标
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,4000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 6000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				 case 11:                 //右转差速  朝目标
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 4000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				case 12:                 //前进   pwm为2000
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,6000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 6000);
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				
				case 13:              
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,1000);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 1000); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
					case 14:              
				{
					FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,7500);
    			FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0);
    			FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 7500); 
          FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0);
				} break ;
				default :
					break ;	
            }                
}
