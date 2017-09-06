#include "ov7620_back.h"
#include "ov7620.h"
#include "common.h"
#include "dma.h"
#include "uart.h"
#include "gpio.h"
#include "string.h"

/*ͼ��ɼ�״̬*/
uint8_t ov7620_img_flag2;

uint8_t CCD_Image2[OV7620_H2][OV7620_W2];//ͼ������

//OV7620��ǰ�еļ���ֵ
uint16_t currRow2 = 0;
//OV7620��Ҫ�еļ���ֵ�����Ϊ�ɼ���������OV7620_H
//����ʱ���Ҫ�ɼ�ȫ���������ݣ������ܲɼ��ٶ����Ʋ���ȫ�ɡ�
uint16_t wantRow2 = 0;

//�б�־
//uint8_t wantRowFlag2[OV7620_H2];
uint8_t const OV7620_SelectedROWS2[OV7620_H2] =
			{
//				2,4,6,8,10,12,14,16,18,20,
//				22,24,26,28,30,32,34,36,38,40,
//				42,44,46,48,50,52,54,56,58,60,
//				62,64,66,68,70,72,74,76,78,80,
//				82,84,86,88,90,92,94,96,98,100,
//				102,104,106,108,110,112,114,116,118,120,
//				122,124,126,128,130,132,134,136,138,140,
//				142,144,146,148,150,152,154,156,158,160,
//				162,164,166,168,170,172,174,176,178,180,
//				182,184,186,188,190,192,194,196,198,200
//				
				2,4,6,8,10,12,14,16,18,20,
				22,24,26,28,30,32,34,36,38,40,
				42,44,46,48,50,52,54,56,58,60,
				62,64,66,68,70,72,74,76,78,80,
				82,84,86,87,88,90,92,94,95,96,97,98,99,100,101,
				102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,
				122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,
				142,143,144,145,146
//				202,204,206,208,210,212,214,216,218,220,
//				222,224,226,228,230,232,234,236,238,239
				
			};

DMA_InitTypeDef DMA_InitStruct2;                 
            
void OV7620_back_Init(void)
{
    //����ͷ����D0-D7
    for(uint8_t i=0;i<8;i++){
        GPIO_QuickInit(HW_GPIOC, i+BOARD_OV7620_DATA_OFFSET, kGPIO_Mode_IFT);//����ͷ���ݶ˿���������
    }
    OV7620_back_PORT_INIT &= 0xFFFF00FF;//����PTC8~15��Ϊ0������״̬
    //0 Pin is configured as general-purpose input, for the GPIO function. 
    //1 Pin is configured as general-purpose output, for the GPIO function.
    
    //��������ͷ
    GPIO_QuickInit(OV7620_back_PCLK_PORT, OV7620_back_PCLK_PIN, kGPIO_Mode_IPD);       //PCLK����Ϊ��������
    GPIO_QuickInit(OV7620_back_VSYNC_PORT,OV7620_back_VSYNC_PIN, kGPIO_Mode_IPD);     //VSYNC����Ϊ��������
	GPIO_QuickInit(OV7620_back_HREF_PORT,OV7620_back_HREF_PIN, kGPIO_Mode_IPD);     //HREF����Ϊ��������
        
    //��������ͷ�ж�����
    GPIO_ITDMAConfig(OV7620_back_PCLK_PORT, OV7620_back_PCLK_PIN, kGPIO_DMA_RisingEdge, true);
    GPIO_ITDMAConfig(OV7620_back_VSYNC_PORT, OV7620_back_VSYNC_PIN, kGPIO_IT_RisingEdge, true);     disable_irq(OV7620_back_VSYN_GPIO_IRQ);
    GPIO_ITDMAConfig(OV7620_back_HREF_PORT, OV7620_back_HREF_PIN, kGPIO_IT_RisingEdge, true);       disable_irq(OV7620_back_HREF_GPIO_IRQ);
    
//    //��������ͷ
//    enable_irq(OV7620_back_VSYN_GPIO_IRQ);
//	disable_irq(OV7620_back_VSYN_GPIO_IRQ);
//	enable_irq(OV7620_back_HREF_GPIO_IRQ);
//	disable_irq(OV7620_back_HREF_GPIO_IRQ);
    
//    memset(&wantRowFlag2,0,sizeof(wantRowFlag2));
    
    //DMA����
    DMA_InitStruct2.chl = CAMERA_back_DMA_CH ;     //HW_DMA_CH1
    DMA_InitStruct2.chlTriggerSource = PORTD_DMAREQ;
    DMA_InitStruct2.minorLoopByteCnt = 1;
    DMA_InitStruct2.majorLoopCnt = (OV7620_W2);          //��ѭ������
    DMA_InitStruct2.triggerSourceMode = kDMA_TriggerSource_Normal;
    DMA_InitStruct2.sAddr = (uint32_t)&OV7620_back_DATA_VALU+ BOARD_OV7620_DATA_OFFSET/8;//����ƫ����
    DMA_InitStruct2.sLastAddrAdj = 0;
    DMA_InitStruct2.sAddrOffset = 0;
    DMA_InitStruct2.sDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct2.sMod = kDMA_ModuloDisable;
    
    DMA_InitStruct2.dAddr = (uint32_t)CCD_Image2;
    DMA_InitStruct2.dLastAddrAdj = 0;
    DMA_InitStruct2.dAddrOffset = 1;
    DMA_InitStruct2.dDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct2.dMod = kDMA_ModuloDisable;
    
    /* initialize DMA moudle ��ʼ��DMAģ��*/
    DMA_Init(&DMA_InitStruct2);  
    
    DMA_ITConfig (CAMERA_back_DMA_CH ,kDMA_IT_Major ,true ); //����DMA�ж�
    DMA_CallbackInstall (CAMERA_back_DMA_CH ,ov7620_DMA_back);
    
    DMA_DisableRequest (CAMERA_back_DMA_CH );
		
//	enable_irq(OV7620_back_VSYN_GPIO_IRQ);
//    disable_irq(OV7620_back_VSYN_GPIO_IRQ);
//    disable_irq(OV7620_back_HREF_GPIO_IRQ);
//    disable_irq(OV7620_back_PCLK_eDMA_IRQ);
//    PORTA->ISFR = ~0;
//    PORTC->ISFR = ~0;
//    PORTD->ISFR = ~0;
	
		//����״̬
	ov7620_img_flag2 = OV7620_STATE_IDLE2;
}

/*************************************************
 * �������ƣ�void ov7620_DMA_back(void )
 * ��飺 DMA�жϷ�����
 * �������ͣ���
 *************************************************/
void ov7620_DMA_back(void)
{  
	DMA0->CINT = DMA_CINT_CINT(CAMERA_back_DMA_CH);/**< Clear Interrupt Request Register, offset: 0x1F */
//	wantRowFlag2[wantRow2] = 1;//���вɼ���ɱ�־��
	wantRow2 ++;//���һ������DMA��ȡ
    DMA_DisableRequest (CAMERA_back_DMA_CH);
    DMA_IRQ_CLEAN (CAMERA_back_DMA_CH) ;  //����жϱ�־λ/**< Interrupt Request Register, offset: 0x24 */
}

//PORTC�ⲿ�ж���ڣ���������ͷ���ж�VSYN��PTE16
//void PORTC_IRQHandler(void)
//{
////	uint8_t i = 31;
////	for(i=31;i>0;i--)  //�ж��ĸ����ŵ��жϷ�����i��ʾ�ĸ����ŷ������ж�
////	{
////	  if((PORTC->ISFR>>i)==1)
////			break;
////	}
////	switch(i)
////	{ //�жϴ���

////	  case OV7620_back_VSYNC_PIN://���ж�
////				VIsr_back();
////			break;
////    // ...		
////	  default : break;
////	}
////    PORTC->ISFR|=PORT_ISFR_ISF_MASK;   //�����־λ PORT_ISFR_ISF_MASK 0xFFFFFFFFu
//	 DelayUs (1);
//    if((PORTC->ISFR>>16)==1)
//	{
////		GPIO_ToggleBit (HW_GPIOA,17);//���볡�ж�ʱ�����жϴ���û��Ӧ�����Է�ת������ƽ
//        PORTC->ISFR = ~0;//����жϱ�־λ
//        if(ov7620_img_flag2!=OV7620_STATE_IDLE2)//����״̬�Ž���ɼ�
//        {
//            return;
//        }
//        currRow2 = 0;
//        wantRow2 = 0;
//        disable_irq(OV7620_back_VSYN_GPIO_IRQ);           //�رճ��ж�
//        enable_irq(OV7620_back_HREF_GPIO_IRQ);            //�����ж�
////        DMA_EnableRequest (CAMERA_back_DMA_CH);							 //ʹ��DMA�ж�
//        DMA_SetDestAddress(CAMERA_back_DMA_CH,(uint32_t)CCD_Image2);
//        ov7620_img_flag2 = OV7620_STATE_START2;//���ڲɼ�
//	}
//}


////��������ͷ���ж�
//void VIsr_back(void)
//{
//    GPIO_ToggleBit (HW_GPIOA,17);//���볡�ж�ʱ�����жϴ���û��Ӧ�����Է�ת������ƽ
//    PORTC->ISFR = ~0;//����жϱ�־λ
//    if(ov7620_img_flag2!=OV7620_STATE_IDLE2)//����״̬�Ž���ɼ�
//    {
//        return;
//    }
//    currRow2 = 0;
//    wantRow2 = 0;
//    disable_irq(OV7620_back_VSYN_GPIO_IRQ);           //�رճ��ж�
//    enable_irq(OV7620_back_HREF_GPIO_IRQ);            //�����ж�
//    DMA_EnableRequest (CAMERA_back_DMA_CH);							 //ʹ��DMA�ж�
//    DMA_SetDestAddress(CAMERA_back_DMA_CH,(uint32_t)CCD_Image2);
//    ov7620_img_flag2 = OV7620_STATE_START2;//���ڲɼ�
//}

//void PORTA_IRQHandler(void)
//{
//	uint8_t i = 31;
//	for(i=31;i>0;i--)  //�ж��ĸ����ŵ��жϷ�����i��ʾ�ĸ����ŷ������ж�
//	{
//	  if((PORTA->ISFR>>i)==1)
//			break;
//	}
//	switch(i)
//	{ //�жϴ���
//	  case OV7620_HREF_PIN: //���ж�
//			HIsr();break;
//      case OV7620_back_HREF_PIN://��������ͷ���ж�
//            HIsr_back();break;
//		default : break;
//	}
//    PORTA->ISFR|=PORT_ISFR_ISF_MASK;   //�����־λ
//}

//void PORTA_IRQHandler(void)
//{
////    uint8_t i = 31;
////	for(i=31;i>0;i--)  //�ж��ĸ����ŵ��жϷ�����i��ʾ�ĸ����ŷ������ж�
////	{
////	  if((PORTA->ISFR>>i)==1)
////			break;
////	}
////	switch(i)
////	{ //�жϴ���
////	  case OV7620_HREF_PIN: //���ж�
////			HIsr();break;
////      case OV7620_back_HREF_PIN://��������ͷ���ж�
////            HIsr_back();break;
////		default : break;
////	}
////    PORTA->ISFR|=PORT_ISFR_ISF_MASK;   //�����־λ
//    if((PORTA->ISFR>>17)==1)
//    {
//		PORTA->ISFR = ~0;
//        currRow2 ++;
//        if(currRow2 == OV7620_SelectedROWS2[wantRow2])				//�����ǰ������Ӧ�òɼ�
//        {
//            //����DMA����
//            DMA_EnableRequest(CAMERA_back_DMA_CH);
//        }
//        if(wantRow2>=OV7620_H2)//һ����ɣ��ر����ж�
//        {
//            disable_irq(OV7620_back_HREF_GPIO_IRQ);   

//            DMA_DisableRequest(CAMERA_back_DMA_CH);//�ر�DMA
//            ov7620_img_flag2 = OV7620_STATE_COMPLETE2;//һ���ɼ����	
//        }
//    }
//}

//void HIsr_back(void) //�������жλص�����
//{
//	PORTA->ISFR = ~0;
//	currRow2 ++;
//	if(currRow2 == OV7620_SelectedROWS2[wantRow2])				//�����ǰ������Ӧ�òɼ�
//  {
//		//����DMA����
//		DMA_EnableRequest(CAMERA_back_DMA_CH);
//	}
//	if(wantRow2>=OV7620_H2)//һ����ɣ��ر����ж�
//    {
//        disable_irq(OV7620_back_HREF_GPIO_IRQ);   

//        DMA_DisableRequest(CAMERA_back_DMA_CH);//�ر�DMA
//		ov7620_img_flag2 = OV7620_STATE_COMPLETE2;//һ���ɼ����	
//	}
//}
