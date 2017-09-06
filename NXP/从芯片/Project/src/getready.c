#include "head.h"

 uint16_t tt=0;//初始化1ms中断函数的变量
 
//1ms中断回调函数
void PIT1_HandlerU( void )
{
	tt++;
}

 void getready()
 {    
    DelayInit();
    
    /* PTA14/C5设置成输入，防止死机 */
    GPIO_QuickInit (HW_GPIOA ,14,kGPIO_Mode_OPP);
    GPIO_QuickInit (HW_GPIOC ,5,kGPIO_Mode_OPP);
     
    /* 正常运行指示灯初始化 */
    GPIO_QuickInit(HW_GPIOD,15, kGPIO_Mode_OPP); 
    GPIO_QuickInit(HW_GPIOE ,26, kGPIO_Mode_OPP); 

    /* UART端口初始化 */
    UART_QuickInit(UART4_RX_PE25_TX_PE24, 115200);
		 
    /* IO口模拟IIC端口初始化 */    /* 如需更改端口请去io2iic.h头文件中修改 */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    


    /* 初始化正交解码，端口号分别为左：PA12,PA13;右：PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

    /* 系统板通信接口初始化 */
    GPIO_QuickInit(HW_GPIOC, 0 ,kGPIO_Mode_OPP);
    

		
	//初始化pit模块的0通道，产生20ms的中断
    PIT_QuickInit(HW_PIT_CH0, 20000);
    PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //注册通道0的回调函数为：QD_value（）
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //开起模块0通道中断 

    //初始化pit模块的1通道，产生1ms的中断
    PIT_QuickInit(HW_PIT_CH1, 1000);
    PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //注册通道1的回调函数为：PIT1_HandlerU（）		
    PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //开起模块1通道中断 


    //摄像头初始化
    OV7620_Init();


/* 看门狗初始化   500ms  */
//   WDOG_QuickInit(500);
}
 

    
void firstimage()
{

    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
    
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

