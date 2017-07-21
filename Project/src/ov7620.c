#include "ov7620.h"
#include "common.h"
#include "dma.h"
#include "uart.h"
#include "gpio.h"
#include "string.h"
#include "ov7620_back.h"

/*图像采集状态*/
uint8_t ov7620_img_flag;

uint8_t CCD_Image[OV7620_H][OV7620_W];//图像数据
uint8_t CCD_Image22[OV7620_H][OV7620_W];//两幅图轮流采集数据，轮流处理数据

//OV7620当前行的计数值
uint16_t currRow = 0;
//OV7620需要行的计数值，最大为采集场的行数OV7620_H
//因有时侯不需要采集全部的行数据，或者受采集速度限制不能全采。
uint16_t wantRow = 0;

//行标志
//uint8_t wantRowFlag[OV7620_H];
uint8_t const OV7620_SelectedROWS[OV7620_H] =
			{
				2,4,6,8,10,12,14,16,18,20,
				22,24,26,28,30,32,34,36,38,40,
				42,44,46,48,50,52,54,56,58,60,
				62,64,66,68,70,72,74,76,78,80,
				82,84,86,88,90,92,94,96,98,100,
				102,104,106,108,110,111,112,113,114,115,116,117,118,119,120,121,
				122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,
				142,144,146,148,150,152,154,156,158,160,
				162,164,166,168
//				202,204,206,208,210,212,214,216,218,220,
//				222,224,226,228,230,232,234,236,238,239
				
			};
DMA_InitTypeDef DMA_InitStruct1;     
            


            
void OV7620_Init(void)
{
    //摄像头数据D0-D7
    for(uint8_t i=0;i<8;i++){
        GPIO_QuickInit(HW_GPIOE, i, kGPIO_Mode_IFT);//摄像头数据端口悬空输入
    }
    OV7620_PORT_INIT &= 0xFFFFFF00;//将低PTE0~7置为0，输入状态   
    //0 Pin is configured as general-purpose input, for the GPIO function. 
    //1 Pin is configured as general-purpose output, for the GPIO function.
    
    /* 场中断  行中断 像素中断设置 */
    GPIO_QuickInit(OV7620_PCLK_PORT, OV7620_PCLK_PIN, kGPIO_Mode_IPD);       //PCLK设置为下拉输入
    GPIO_QuickInit(OV7620_VSYNC_PORT,OV7620_VSYNC_PIN, kGPIO_Mode_IPD);     //VSYNC设置为下拉输入
	GPIO_QuickInit(OV7620_HREF_PORT,OV7620_HREF_PIN, kGPIO_Mode_IPD);     //HREF设置为下拉输入
    
    //配置引脚DMA触发功能     上升沿触发
    GPIO_ITDMAConfig(OV7620_PCLK_PORT, OV7620_PCLK_PIN, kGPIO_DMA_RisingEdge, true);
    //配置引脚下降沿中断功能   上升沿触发
    GPIO_ITDMAConfig(OV7620_VSYNC_PORT, OV7620_VSYNC_PIN, kGPIO_IT_RisingEdge, true);   disable_irq(OV7620_VSYN_GPIO_IRQ);  //配置后立即关闭
	//配置引脚下降沿中断功能   上升沿触发
    GPIO_ITDMAConfig(OV7620_HREF_PORT, OV7620_HREF_PIN, kGPIO_IT_RisingEdge, true);     disable_irq(OV7620_HREF_GPIO_IRQ);
    
		
    ov7620_img_flag = OV7620_STATE_COMPLETE;
    disable_irq(OV7620_VSYN_GPIO_IRQ);
		
		
    //DMA配置
    DMA_InitStruct1.chl = CAMERA_DMA_CH ;     //HW_DMA_CH0
    DMA_InitStruct1.chlTriggerSource = PORTE_DMAREQ;
    DMA_InitStruct1.minorLoopByteCnt = 1;                   //主循环(major loop)副循环(minor loop)
    DMA_InitStruct1.majorLoopCnt = (OV7620_W);          //主循环次数
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal;
    DMA_InitStruct1.sAddr = (uint32_t)&OV7620_DATA_VALU;//数据偏移量
    DMA_InitStruct1.sLastAddrAdj = 0;
    DMA_InitStruct1.sAddrOffset = 0;
    DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.sMod = kDMA_ModuloDisable;
    
    DMA_InitStruct1.dAddr = (uint32_t)CCD_Image;
    
    DMA_InitStruct1.dLastAddrAdj = 0;
    DMA_InitStruct1.dAddrOffset = 1;
    DMA_InitStruct1.dDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.dMod = kDMA_ModuloDisable;
    
    /* initialize DMA moudle 初始化DMA模块*/
    DMA_Init(&DMA_InitStruct1);  
    
    DMA_ITConfig (CAMERA_DMA_CH ,kDMA_IT_Major ,true ); //设置DMA中断
    DMA_CallbackInstall (CAMERA_DMA_CH ,ov7620_DMA);
    
    DMA_DisableRequest (CAMERA_DMA_CH );
	
		//空闲状态
	  
		
}

/*************************************************
 * 函数名称：void ov7725_DMA(void )
 * 简介： DMA中断服务函数
 * 返回类型：无
 *************************************************/
void ov7620_DMA(void)
{  
	DMA0->CINT = DMA_CINT_CINT(CAMERA_DMA_CH);/**< Clear Interrupt Request Register, offset: 0x1F */
//	wantRowFlag[wantRow] = 1;//该行采集完成标志，
	wantRow ++;//完成一行数据DMA读取
    DMA_DisableRequest (CAMERA_DMA_CH);
    DMA_IRQ_CLEAN (CAMERA_DMA_CH) ;  //清除中断标志位/**< Interrupt Request Register, offset: 0x24 */
}

/***********************************************************************************************
 功能：PORTE外部中断入口，场中断VSYN，PTE11
 形参：0       
 返回：0
 详解：0
************************************************************************************************/
void PORTE_IRQHandler(void)
{

    if((PORTE->ISFR>>11)==1)
    {
			
		PORTE->ISFR = ~0;//清除中断标志位
		if(ov7620_img_flag!=OV7620_STATE_IDLE)//空闲状态才进入采集
		{
			return;
		}
		currRow = 0;
		wantRow = 0;
		disable_irq(OV7620_VSYN_GPIO_IRQ);           //关闭场中断
		enable_irq(OV7620_HREF_GPIO_IRQ);            //打开行中断
//		DMA_EnableRequest (CAMERA_DMA_CH);							 //使能DMA中断
    
        if(jioushu==1)
        {
		DMA_SetDestAddress(CAMERA_DMA_CH,(uint32_t)CCD_Image);
        }
        else
        {
        DMA_SetDestAddress(CAMERA_DMA_CH,(uint32_t)CCD_Image22);
        } 
		ov7620_img_flag = OV7620_STATE_START;//正在采集
    }
}


void PORTD_IRQHandler(void)
{
//	uint8_t i = 31;
//	for(i=31;i>0;i--)  //判断哪个引脚的中断发生，i表示哪个引脚发生的中断
//	{
//	  if((PORTA->ISFR>>i)==1)
//			break;
//	}
//	switch(i)
//	{ //中断处理
//	  case OV7620_HREF_PIN: //行中断
//          
//			HIsr();
////            DMA_EnableRequest (CAMERA_DMA_CH);							 //使能DMA中断
//            break;
//	}
//    PORTA->ISFR|=PORT_ISFR_ISF_MASK;   //清除标志位
	if((PORTD->ISFR>>14)==1)
	{
		PORTD->ISFR = ~0;
		currRow ++;
		if(currRow == OV7620_SelectedROWS[wantRow])				//如果当前行数据应该采集
			{
			//启动DMA传输
			DMA_EnableRequest(CAMERA_DMA_CH);
		}
		if(wantRow>=OV7620_H)//一场完成，关闭行中断
			{
					disable_irq(OV7620_HREF_GPIO_IRQ);   

			ov7620_img_flag = OV7620_STATE_COMPLETE;//一场采集完成	
		}
	}
}

//行同步回调中断函数
//void HIsr(void) //调用行中段回调函数
//{
//	PORTA->ISFR = ~0;
//	currRow ++;
//	if(currRow == OV7620_SelectedROWS[wantRow])				//如果当前行数据应该采集
//    {
//		//启动DMA传输
//		DMA_EnableRequest(CAMERA_DMA_CH);
//	}
//	if(wantRow>=OV7620_H)//一场完成，关闭行中断
//    {
//        disable_irq(OV7620_HREF_GPIO_IRQ);   

//		ov7620_img_flag = OV7620_STATE_COMPLETE;//一场采集完成	
//	}
//}
