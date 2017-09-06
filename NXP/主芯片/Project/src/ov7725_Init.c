#include "ov7725_Init.h"
#include "lptmr.h"
#include "common.h"
#include "dma.h"
#include "ov7725.h"
#include "gpio.h"
#include "uart.h"
#include "ftm.h"
#include "Drv_LCD.h"

extern uint32_t Left_QD_value;           //�����������ֵ
extern uint32_t Right_QD_value;          //�ұ���������ֵ
extern uint32_t QDVALUE_GETFINSH;        //����������״̬

/*ָ�������ַ*/
uint8_t CCDBufferPool[OV7725_H*(OV7725_W/8)]; 

uint8_t img[OV7725_H*OV7725_W]={1};

int8_t center[OV7725_H];

/* ����ͷ����ָ��*/
uint8_t *CCDBuffer;

/*ͼ��ɼ�״̬*/
volatile OV7725_Status ov7725_img_flag;

/* ���Ŷ��� */
#define BOARD_OV7725_PCLK_PORT      HW_GPIOC
#define BOARD_OV7725_PCLK_PIN       (16)          //ʹ��PTA7������Ϊ�����ź�����         //7
#define BOARD_OV7725_VSYNC_PORT     HW_GPIOA
#define BOARD_OV7725_VSYNC_PIN      (17)         //ʹ��PTA16������Ϊ���ź�����        //16
#define BOARD_OV7725_HREF_PORT      HW_GPIOA
#define BOARD_OV7725_HREF_PIN       (16)         //ʹ��PTA17������Ϊ���ź�����          //17
#define BOARD_OV7725_DATA_OFFSET    (8) /* ����ͷ���ݲɼ�����PTA8-PTA15 ֻ��Ϊ 0 8 16 24 */

void ov7725_Port_Init(void);

/*************************************************
* ��������:SCCB_Init()
 * ��飺 ͨ��SCCBд7725�Ĵ���
 * �������ͣ�0������1ʧ��
 *************************************************/
int SCCB_Init()
{
    int r;
    r = ov7725_probe(); 
    if(r)
        return 1;
    r = ov7725_set_image_size(IMAGE_SIZE);
    if(r)
    {
        printf("OV7725 set image error\r\n");
        return 1;
    }
    return 0;
}

/*************************************************
 * �������ƣ�void OV_ISR()
 * ��飺 ���жϷ�����
 * �������ͣ���
 *************************************************/

void OV_ISR(uint32_t index)
{
    if(index & (1 << BOARD_OV7725_VSYNC_PIN))
    {
        //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
        if(ov7725_img_flag == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
        {             
            ov7725_img_flag = IMG_GATHER;                  //���ͼ��ɼ���
            //disable_irq (PORTA_IRQn);
            PORTC ->ISFR = 1<<BOARD_OV7725_PCLK_PIN;       //���PCLK��־λ

            DMA_EnableRequest (HW_DMA_CH2 );                  //ʹ��ͨ��CHn Ӳ������
            PORTC ->ISFR = 1 <<  BOARD_OV7725_PCLK_PIN;            //���PCLK��־λ
            DMA_SetDestAddress (HW_DMA_CH2,(uint32_t)CCDBufferPool );    //�ָ���ַ
					

		        disable_irq (PORTA_IRQn);                      //�ر�PTA���ж�
					

        }
        else if(ov7725_img_flag == IMG_FINISH)
        {
//            uint8_t i;
//            //��ȡ������ֵ
//            FTM_QD_GetData (HW_FTM1 ,&Left_QD_value ,&i);  //�����������ļ���ֵ
//            FTM_QD_GetData (HW_FTM2 ,&Right_QD_value,&i);  //����ұ������ļ���ֵ

//            FTM_QD_ClearCount (HW_FTM1 );                  //�����������ͨ��1��countֵ
//            FTM_QD_ClearCount (HW_FTM2 );
//            QDVALUE_GETFINSH =1;
        }
        else                                        //ͼ��ɼ�����
        {
            disable_irq (PORTA_IRQn);                      //�ر�PTA���ж�
            ov7725_img_flag = IMG_FAIL;                    //���ͼ��ɼ�ʧ��
        }
    }
}

/*************************************************
 * �������ƣ�void ov7725_DMA(void )
 * ��飺 DMA�жϷ�����
 * �������ͣ���
 *************************************************/
void ov7725_DMA(void )
{
    ov7725_img_flag = IMG_FINISH ;
    DMA_DisableRequest (HW_DMA_CH2 );
    DMA_IRQ_CLEAN (CAMERA_7_DMA_CH ) ;  //����жϱ�־λ
}

/*************************************************
 * �������ƣ�void ov7725_Init()
 * ��飺 ov7725��ʼ��
 * �������ͣ���
 *************************************************/
void ov7725_Init()
{
    CCDBuffer =(uint8_t*)&CCDBufferPool;    
	//�������ͷ
    if(SCCB_Init())
    {
        printf("no device found!\r\n");
    }       
    ov7725_Port_Init();
    DelayMs (10);
}

/*************************************************
 * �������ƣ�void ov7725_Port_Init()
 * ��飺 ov7725�ܽų�ʼ�����ڲ����ã�
 * �������ͣ���
 *************************************************/
void ov7725_Port_Init()
{
     /* ��ʼ������ͷ���ݲɼ��˿� */
    for(uint8_t i=0;i<8;i++)
    {
        GPIO_QuickInit(HW_GPIOC, BOARD_OV7725_DATA_OFFSET+i, kGPIO_Mode_IFT);
    }
		OV7725_PORT_INIT1111 &= 0xFFFF00FF;//����PTE0~7��Ϊ0������״̬   
    //0 Pin is configured as general-purpose input, for the GPIO function. 
    //1 Pin is configured as general-purpose output, for the GPIO function.
    /* ���ж�  ���ж� �����ж����� */
    GPIO_QuickInit(BOARD_OV7725_PCLK_PORT, BOARD_OV7725_PCLK_PIN, kGPIO_Mode_IPU);       //PCLK����Ϊ��������
    GPIO_QuickInit(BOARD_OV7725_VSYNC_PORT, BOARD_OV7725_VSYNC_PIN, kGPIO_Mode_IPD);     //VSYNC����Ϊ��������
    
    /* install callback ��װ�ص�����*/
    GPIO_CallbackInstall(BOARD_OV7725_VSYNC_PORT, OV_ISR);
    
    //���������½����жϹ���   �����ش���
    GPIO_ITDMAConfig(BOARD_OV7725_VSYNC_PORT, BOARD_OV7725_VSYNC_PIN, kGPIO_IT_RisingEdge, true);
    //��������DMA��������     �½��ش���
    GPIO_ITDMAConfig(BOARD_OV7725_PCLK_PORT, BOARD_OV7725_PCLK_PIN, kGPIO_DMA_FallingEdge, true);
		
		
		//��ʼ��״̬
		ov7725_img_flag = IMG_FINISH;
	  disable_irq (PORTA_IRQn);                      //�ر�PTA���ж�
		
		
    
         //����DMA�ṹ
    DMA_InitTypeDef DMA_InitStruct1 = {0};
        
    //DMA����
    DMA_InitStruct1.chl = CAMERA_7_DMA_CH ;     //HW_DMA_CH2
    DMA_InitStruct1.chlTriggerSource = PORTC_DMAREQ;
    DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal;
    DMA_InitStruct1.minorLoopByteCnt = 1;
    DMA_InitStruct1.majorLoopCnt = (OV7725_H *(OV7725_W/8));          //��ѭ������
    
    DMA_InitStruct1.sAddr = (uint32_t)&PTC->PDIR + BOARD_OV7725_DATA_OFFSET/8;
    DMA_InitStruct1.sLastAddrAdj = 0;
    DMA_InitStruct1.sAddrOffset = 0;
    DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.sMod = kDMA_ModuloDisable;
    
    DMA_InitStruct1.dAddr = (uint32_t)CCDBuffer;
    DMA_InitStruct1.dLastAddrAdj = 0;
    DMA_InitStruct1.dAddrOffset = 1;
    DMA_InitStruct1.dDataWidth = kDMA_DataWidthBit_8;
    DMA_InitStruct1.dMod = kDMA_ModuloDisable;
    
    /* initialize DMA moudle ��ʼ��DMAģ��*/
    DMA_Init(&DMA_InitStruct1);  
    
    DMA_ITConfig (HW_DMA_CH2 ,kDMA_IT_Major ,true ); //����DMA�ж�
    DMA_CallbackInstall (HW_DMA_CH2 ,ov7725_DMA);
    
    DMA_DisableRequest (HW_DMA_CH2 );
		
		
		
}
/*************************************************
 * �������ƣ�void ov7725_Get_Imge(void)
 * ��飺 ͼ��ɼ��������ɼ��������ݴ洢�ڳ�ʼ���е������ϣ�
 * �������ͣ���
 *************************************************/
void ov7725_Get_Imge(void)
{
    ov7725_img_flag = IMG_START;                    //��ʼ�ɼ�ͼ��
    PORTA->ISFR = ~0;                               //д1���жϱ�־λ
    enable_irq(PORTA_IRQn);                         //����PTA���ж�
    while(ov7725_img_flag != IMG_FINISH)            //�ȴ�ͼ��ɼ����
    {
        if(ov7725_img_flag == IMG_FAIL)           //����ͼ��ɼ����������²ɼ�
        {
            ov7725_img_flag = IMG_START;            //��ʼ�ɼ�ͼ��
            PORTA->ISFR = ~0;                       //д1���жϱ�־λ
            enable_irq(PORTA_IRQn);                 //����PTA���ж�
        }
    }
}


void img_extract(uint8_t *dst, uint8_t *src, uint32_t srclen)
{
    uint8_t colour[2] = {0, 1}; //0 �� 1 �ֱ��Ӧ����ɫ
    //ע������ͷ 0 ��ʾ ��ɫ��1��ʾ ��ɫ
    uint8_t tmpsrc;
    while(srclen --)
    {
        tmpsrc = *src++;
        *dst++ = colour[ (tmpsrc >> 0 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 1 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 2 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 3 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 4 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 5 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 6 ) & 0x01 ];
        *dst++ = colour[ (tmpsrc >> 7 ) & 0x01 ];
    }
}


