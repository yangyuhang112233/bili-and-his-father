#include "head.h"
 
//1ms中断回调函数
void PIT1_HandlerU( void )
{
	if(delay_flag==DELAY_START)
	{
		tt++;
	}
}

 void getready()
 {    
    DelayInit();
    
    /* PTA14/C5设置成输入，防止死机 */
    //GPIO_QuickInit (HW_GPIOA ,14,kGPIO_Mode_OPP);
    //GPIO_QuickInit (HW_GPIOC ,5,kGPIO_Mode_OPP);
     
    /* 正常运行指示灯初始化 */
    GPIO_QuickInit(HW_GPIOD,15, kGPIO_Mode_OPP); 
    GPIO_QuickInit(HW_GPIOE ,26, kGPIO_Mode_OPP); 

    /* UART端口初始化 */
    UART_QuickInit(UART4_RX_PE25_TX_PE24, 115200);
		 
    /* IO口模拟IIC端口初始化 */    /* 如需更改端口请去io2iic.h头文件中修改 */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    
     /* 拨码开关初始化 */
    GPIO_QuickInit(HW_GPIOB, 0, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 1, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 2, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 3, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 4, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 5, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 6, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 7, kGPIO_Mode_IPU);
       
    /* 初始化正交解码，端口号分别为左：PA12,PA13;右：PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

    /* 触碰开关初始化 */
    GPIO_QuickInit(HW_GPIOA, 4 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOA, 5 , kGPIO_Mode_IPU);

    /* 系统板通信接口初始化 */
    GPIO_QuickInit(HW_GPIOC, 0 , kGPIO_Mode_IFT);
         
    /* 舵机初始化 */
    CMT_PWM_QuickInit (55,0);
    /* 设置舵机初使占空比，范围0-10000分别表示0-100% */
    anglex=anglemid;
    CMT_PWM_ChangDuty (anglex);
      
    /* FTM快速初始化 */
    FTM_PWM_QuickInit(FTM0_CH0_PC01, kPWM_EdgeAligned ,10000);     /* 设置PC03为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH1_PC02, kPWM_EdgeAligned ,10000);     /* 设置PD04为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH2_PC03, kPWM_EdgeAligned ,10000);     /* 设置PC03为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH3_PC04, kPWM_EdgeAligned ,10000);     /* 设置PD04为电机输出端口，频率设定为5000Hz*/
    /* 设置FTM初使占空比，范围0-10000分别表示0-100% */
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH0, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH1, 0);
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 0);
		
	//初始化pit模块的0通道，产生15ms的中断
    PIT_QuickInit(HW_PIT_CH0, 15000);
    PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //注册通道0的回调函数为：QD_value（）
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //开起模块0通道中断 

    //初始化pit模块的1通道，产生1ms的中断
    PIT_QuickInit(HW_PIT_CH1, 1000);
    PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //注册通道1的回调函数为：PIT1_HandlerU（）		
    PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //开起模块1通道中断 
	
	/*初始化pit模块的2通道，产生10ms中断*/
	PIT_QuickInit(HW_PIT_CH2, 10000);
    PIT_CallbackInstall(HW_PIT_CH2, Motor_PID_Output ); //注册通道0的回调函数为：QD_value（）
    PIT_ITDMAConfig(HW_PIT_CH2, kPIT_IT_TOF, ENABLE); //开起模块0通道中断 


//	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
//	NVIC_SetPriority(OV7620_HREF_GPIO_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,1));
//	NVIC_SetPriority(OV7620_VSYN_GPIO_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,2));
//	NVIC_SetPriority(OV7620_PCLK_eDMA_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,3));
//	
//	NVIC_SetPriority(PORTA_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,2,1));
//	NVIC_SetPriority(DMA2_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,2,2));
//	
//	NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,3,1));
//	
//	NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,3,2));
//	
//	NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,4,1));
    //小液晶初始化
    LCD_Init();

    //摄像头初始化
    OV7620_Init();
//    ov7725_Init();

/* 看门狗初始化   500ms  */
//   WDOG_QuickInit(500);
}
 
void Printf()
{
   //信标显示
    LCD_printf(10,5,"target:   ");
    LCD_printf(10,5,"target:%d",target_flag);
    
    LCD_printf(60,5,"th:   ");
    LCD_printf(60,5,"th:%d",target_h);
    
    LCD_printf(10,20,"tl:   ");
    LCD_printf(10,20,"tl:%d",target_l);

    //障碍物显示
//    LCD_printf(60,20,"bar2:    "); 
//    LCD_printf(60,20,"bar2:%d",barrier); 
//    
//    LCD_printf(10,35,"bh:   ");
//    LCD_printf(10,35,"bh:%d",barrier_h);
//    
//    LCD_printf(60,35,"bl:   ");
//    LCD_printf(60,35,"bl:%d",barrier_l);
    
       
    //经过第几个灯
    LCD_printf(10,50,"co1:    "); 
    LCD_printf(10,50,"co1:%d",count1); 
    
    LCD_printf(60,50,"7c:  "); 
    LCD_printf(60,50,"7c:%d",countbz7620); 
    
//  LCD_printf(60,50,"7c:  "); 
//  LCD_printf(60,50,"7c:%d",count7725); 
    
    LCD_printf(10,65,"state:   ");
    LCD_printf(10,65,"state:%d",state);
    
    //障碍物和信标灯之间的平方距离
    LCD_printf(60,65,"juli:   ");
    LCD_printf(60,65,"juli:%d",juli);
    
    
    LCD_printf(10,95,"speed:    "); 
    LCD_printf(10,95,"speed:%d",speedx);

    LCD_printf(60,95,"xx:    "); 
    LCD_printf(60,95,"xx:%d",xinbiaoxiangsu);

}

void firstimage()
{
   while(1)
{
    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
    
        int count=0;
         for(int ii=0;ii<OV7620_H-2;ii++)	
    {     
       for(int jj=0;jj<OV7620_W-1;jj++)
       {
         if(CCD_Image[ii][jj]>=door7620)
         {   
			 count ++;
         }      
       }
  }          
	beacon_right_flag=PCin(0);
   if((count>2)||(beacon_right_flag==1))
   {
	   break;
   }       
}
}  


void startimage()
{
    if(jioushu==0)jioushu=1;
    else 
    {
    jioushu=0;
    }

     if(jioushu==1)
    {
       DMA_InitStruct1.dAddr = (uint32_t)CCD_Image;      
    }
    
    else
    {
    DMA_InitStruct1.dAddr = (uint32_t)CCD_Image22;  
    }
    
    //7620摄像头开始采集图像
    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
}

 void endimage()
{
    //7620 采集图像结束  
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);   //等待图像采集完毕           
} 


//刹车函数
void stopmove()
{
    uint16_t leftspeed=0;
    uint16_t rightspeed=0;
         
    int16_t Kp=1200;
    int16_t Ki=0;
    int16_t leftsum ;
    int16_t rightsum ;
                    
    int16_t lefterror;//速度偏差
    int16_t righterror;  
    int32_t pwm_out1;//pwm输出	
    int32_t pwm_out2;    
       
      while(1)       
     {               
     //pi具体实现  

      lefterror = leftspeed - qd_left_value ;
      righterror= rightspeed - qd_right_value ;	
		
	  leftsum+= lefterror ;//积分调节的积分量
      rightsum  += righterror ;
       
	  if(leftsum >= 800)leftsum = 800;
	  if(leftsum <= -400)leftsum = -400;
	  if(rightsum  >= 800) rightsum  = 800;
	  if(rightsum  <= -400)rightsum  = -400;
            
      pwm_out1 =   Kp*lefterror + Ki*leftsum  ;
	  pwm_out2 =   Kp*righterror + Ki*rightsum   ;

	  	     
        //防止值超过限度
		if(pwm_out1>=10000)
		{
			pwm_out1=10000;
		}
		if(pwm_out2>=10000)
		{
			pwm_out2=10000;
		}
        
		if(pwm_out1<-10000)
		{
			pwm_out1=-10000;
		}
		if(pwm_out2<-10000)
		{
			pwm_out2=-10000;
		}
	     
	    if(pwm_out1 > 0)
		{
	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
		}
		else
		{
		pwm_out1 = -pwm_out1 ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1 );
		}
		
		if(pwm_out2 > 0)
		{
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
		}
		else
		{
		pwm_out2 = -pwm_out2 ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
		}
        
        if(qd_left_value+qd_right_value<1)
        {
         while(1)
         {
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0); 
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
         }
        }    
      }
}

