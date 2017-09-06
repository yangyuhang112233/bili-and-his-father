#include "ov7620.h"
#include "common.h"
#include "dma.h"
#include "uart.h"
#include "gpio.h"
#include "string.h"
#include "ov7620_back.h"

/*ͼ��ɼ�״̬*/
uint8_t ov7620_img_flag;

uint8_t CCD_Image[OV7620_H][OV7620_W];//ͼ������
uint8_t CCD_Image22[OV7620_H][OV7620_W];//����ͼ�����ɼ����ݣ�������������

//OV7620��ǰ�еļ���ֵ
uint16_t currRow = 0;
//OV7620��Ҫ�еļ���ֵ�����Ϊ�ɼ���������OV7620_H
//����ʱ���Ҫ�ɼ�ȫ���������ݣ������ܲɼ��ٶ����Ʋ���ȫ�ɡ�
uint16_t wantRow = 0;

//�б�־
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
    //����ͷ����D0-D7
    for(uint8_t i=0;i<8;i++){
        GPIO_QuickInit(HW_GPIOE, i, kGPIO_Mode_IFT);//����ͷ���ݶ˿���������
    }
    OV7620_PORT_INIT &= 0xFFFFFF00;//����PTE0~7��Ϊ0������״̬   
    //0 Pin is configured as general-purpose input, for the GPIO function. 
    //1 Pin is configured as general-purpose output, for the GPIO function.
    
    /* ���ж�  ���ж� �����ж����� */
    GPIO_QuickInit(OV7620_PCLK_PORT, OV7620_PCLK_PIN, kGPIO_Mode_IPD);       //PCLK����Ϊ��������
    GPIO_QuickInit(OV7620_VSYNC_PORT,OV7620_VSYNC_PIN, kGPIO_Mode_IPD);     //VSYNC����Ϊ��������
	GPIO_QuickInit(OV7620_HREF_PORT,OV7620_HREF_PIN, kGPIO_Mode_IPD);     //HREF����Ϊ��������
    
    //��������DMA��������     �����ش���
    GPIO_ITDMAConfig(OV7620_PCLK_PORT, OV7620_PCLK_PIN, kGPIO_DMA_RisingEdge, true);
    //���������½����жϹ���   �����ش���
    GPIO_ITDMAConfig(OV7620_VSYNC_PORT, OV7620_VSYNC_PIN, kGPIO_IT_RisingEdge, true);   disable_irq(OV7620_VSYN_GPIO_IRQ);  //���ú������ر�
	//���������½����жϹ���   �����ش���
    GPIO_ITDMAConfig(OV7620_HREF_PORT, OV7620_HREF_PIN, kGPIO_IT_RisingEdge, true);     disable_irq(OV7620_HREF_GPIO_IRQ);
    
		
    ov7620_img_flag = OV7620_STATE_COMPLETE;
    disable_irq(OV7620_VSYN_GPIO_IRQ);
		
		
    //DMA����
    DMA_InitStruct1.chl = CAMERA_DMA_CH ;     //HW_DMA_CH0
    DMA_InitStruct1.chlTriggerSource = PORTE_DMAREQ;
    DMA_InitStruct1.minorLoopByteCnt = 1;                   //��ѭ��(major loop)��ѭ��(minor loop)
    DMA_InitStruct1.majorLoopCnt = (OV7620_W);          //��ѭ������
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal;
    DMA_InitStruct1.sAddr = (uint32_t)&OV7620_DATA_VALU;//����ƫ����
    DMA_InitStruct1.sLastAddrAdj = 0;
    DMA_InitStruct1.sAddrOffset = 0;
    DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.sMod = kDMA_ModuloDisable;
    
    DMA_InitStruct1.dAddr = (uint32_t)CCD_Image;
    
    DMA_InitStruct1.dLastAddrAdj = 0;
    DMA_InitStruct1.dAddrOffset = 1;
    DMA_InitStruct1.dDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.dMod = kDMA_ModuloDisable;
    
    /* initialize DMA moudle ��ʼ��DMAģ��*/
    DMA_Init(&DMA_InitStruct1);  
    
    DMA_ITConfig (CAMERA_DMA_CH ,kDMA_IT_Major ,true ); //����DMA�ж�
    DMA_CallbackInstall (CAMERA_DMA_CH ,ov7620_DMA);
    
    DMA_DisableRequest (CAMERA_DMA_CH );
	
		//����״̬
	  
		
}

/*************************************************
 * �������ƣ�void ov7725_DMA(void )
 * ��飺 DMA�жϷ�����
 * �������ͣ���
 *************************************************/
void ov7620_DMA(void)
{  
	DMA0->CINT = DMA_CINT_CINT(CAMERA_DMA_CH);/**< Clear Interrupt Request Register, offset: 0x1F */
//	wantRowFlag[wantRow] = 1;//���вɼ���ɱ�־��
	wantRow ++;//���һ������DMA��ȡ
    DMA_DisableRequest (CAMERA_DMA_CH);
    DMA_IRQ_CLEAN (CAMERA_DMA_CH) ;  //����жϱ�־λ/**< Interrupt Request Register, offset: 0x24 */
}

/***********************************************************************************************
 ���ܣ�PORTE�ⲿ�ж���ڣ����ж�VSYN��PTE11
 �βΣ�0       
 ���أ�0
 ��⣺0
************************************************************************************************/
void PORTE_IRQHandler(void)
{

    if((PORTE->ISFR>>11)==1)
    {
			
		PORTE->ISFR = ~0;//����жϱ�־λ
		if(ov7620_img_flag!=OV7620_STATE_IDLE)//����״̬�Ž���ɼ�
		{
			return;
		}
		currRow = 0;
		wantRow = 0;
		disable_irq(OV7620_VSYN_GPIO_IRQ);           //�رճ��ж�
		enable_irq(OV7620_HREF_GPIO_IRQ);            //�����ж�
//		DMA_EnableRequest (CAMERA_DMA_CH);							 //ʹ��DMA�ж�
    
        if(jioushu==1)
        {
		DMA_SetDestAddress(CAMERA_DMA_CH,(uint32_t)CCD_Image);
        }
        else
        {
        DMA_SetDestAddress(CAMERA_DMA_CH,(uint32_t)CCD_Image22);
        } 
		ov7620_img_flag = OV7620_STATE_START;//���ڲɼ�
    }
}


void PORTD_IRQHandler(void)
{
//	uint8_t i = 31;
//	for(i=31;i>0;i--)  //�ж��ĸ����ŵ��жϷ�����i��ʾ�ĸ����ŷ������ж�
//	{
//	  if((PORTA->ISFR>>i)==1)
//			break;
//	}
//	switch(i)
//	{ //�жϴ���
//	  case OV7620_HREF_PIN: //���ж�
//          
//			HIsr();
////            DMA_EnableRequest (CAMERA_DMA_CH);							 //ʹ��DMA�ж�
//            break;
//	}
//    PORTA->ISFR|=PORT_ISFR_ISF_MASK;   //�����־λ
	if((PORTD->ISFR>>14)==1)
	{
		PORTD->ISFR = ~0;
		currRow ++;
		if(currRow == OV7620_SelectedROWS[wantRow])				//�����ǰ������Ӧ�òɼ�
			{
			//����DMA����
			DMA_EnableRequest(CAMERA_DMA_CH);
		}
		if(wantRow>=OV7620_H)//һ����ɣ��ر����ж�
			{
					disable_irq(OV7620_HREF_GPIO_IRQ);   

			ov7620_img_flag = OV7620_STATE_COMPLETE;//һ���ɼ����	
		}
	}
}

//��ͬ���ص��жϺ���
//void HIsr(void) //�������жλص�����
//{
//	PORTA->ISFR = ~0;
//	currRow ++;
//	if(currRow == OV7620_SelectedROWS[wantRow])				//�����ǰ������Ӧ�òɼ�
//    {
//		//����DMA����
//		DMA_EnableRequest(CAMERA_DMA_CH);
//	}
//	if(wantRow>=OV7620_H)//һ����ɣ��ر����ж�
//    {
//        disable_irq(OV7620_HREF_GPIO_IRQ);   

//		ov7620_img_flag = OV7620_STATE_COMPLETE;//һ���ɼ����	
//	}
//}
