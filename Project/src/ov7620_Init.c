#include "ov7620_Init.h"
#include "lptmr.h"
#include "common.h"
#include "dma.h"
#include "ov7620.h"
#include "gpio.h"
#include "uart.h"
#include "ftm.h"
#include "Drv_LCD.h"

extern uint32_t Left_QD_value;           //�����������ֵ
extern uint32_t Right_QD_value;          //�ұ���������ֵ
extern uint32_t QDVALUE_GETFINSH;        //����������״̬
DMA_InitTypeDef DMA_InitStruct1;

/*ָ�������ַ*/
uint8_t CCDBufferPool[OV7620_H*(OV7620_W/8)]; 

/* ����ͷ����ָ��*/
uint8_t *CCDBuffer;

//��Ч����  ֻ�ɼ� 68 71 74 77�� ��
uint8_t  CCD_Valid_Line[CCD_IMAGE_H];

/*ͼ��ɼ�״̬*/
volatile OV7725_Status ov7725_img_flag;

/* ���Ŷ��� */
#define BOARD_OV7620_PCLK_PORT      HW_GPIOC
#define BOARD_OV7620_PCLK_PIN       (3)          //ʹ��PTA7������Ϊ�����ź�����         //7
#define BOARD_OV7620_VSYNC_PORT     HW_GPIOC
#define BOARD_OV7620_VSYNC_PIN      (11)         //ʹ��PTA16������Ϊ���ź�����        //16
#define BOARD_OV7620_HREF_PORT      HW_GPIOE
#define BOARD_OV7620_HREF_PIN       (8)         //ʹ��PTA17������Ϊ���ź�����          //17
#define BOARD_OV7620_DATA_OFFSET    (8) /* ����ͷ���ݲɼ�����PTA8-PTA15 ֻ��Ϊ 0 8 16 24 */

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
    if(index & (1 << BOARD_OV7620_VSYNC_PIN))
    {
        //���ж���Ҫ�ж��ǳ��������ǳ���ʼ
        if(ov7725_img_flag == IMG_START)                   //��Ҫ��ʼ�ɼ�ͼ��
        {             
            ov7725_img_flag = IMG_GATHER;                  //���ͼ��ɼ���
            //disable_irq (PORTA_IRQn);
            PORTC ->ISFR = 1<<BOARD_OV7620_PCLK_PIN;       //���PCLK��־λ

            DMA_EnableRequest (HW_DMA_CH2 );                  //ʹ��ͨ��CHn Ӳ������
            PORTC ->ISFR = 1 <<  BOARD_OV7620_PCLK_PIN;            //���PCLK��־λ
            DMA_SetDestAddress (HW_DMA_CH2,(uint32_t)CCDBufferPool );    //�ָ���ַ

        }
        else if(ov7725_img_flag == IMG_FINISH)
        {
            uint8_t i;
            //��ȡ������ֵ
            FTM_QD_GetData (HW_FTM1 ,&Left_QD_value ,&i);  //�����������ļ���ֵ
            FTM_QD_GetData (HW_FTM2 ,&Right_QD_value,&i);  //����ұ������ļ���ֵ

            FTM_QD_ClearCount (HW_FTM1 );                  //�����������ͨ��1��countֵ
            FTM_QD_ClearCount (HW_FTM2 );
            QDVALUE_GETFINSH =1;
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
    DMA_IRQ_CLEAN (CAMERA_DMA_CH ) ;  //����жϱ�־λ
}

/*************************************************
 * �������ƣ�void ov7725_Init()
 * ��飺 ov7725��ʼ��
 * �������ͣ���
 *************************************************/
//��ʼ��OV7620ģ��
void OV7620_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct1;
	uint32_t i = 0;
	//��Ч���� 
	for(i=0;i<sizeof(CCD_Valid_Line);i++)
	{
		CCD_Valid_Line[i] = i*2; //*2�����������Ҫ������ͼ��߶ȷֱ� 
	}
	//����״̬
	OV7620Dev.State = OV7620_STATE_IDLE;
	//����ͷ���� D0-D7
	for(i=0;i<8;i++)
	{
		GPIO_InitStruct1.pinx = i;
		GPIO_InitStruct1.GPIO_InitState = Bit_SET;
		GPIO_InitStruct1.GPIO_IRQMode = kGPIO_IT_DISABLE;
		GPIO_InitStruct1.mode = kGPIO_Mode_IFT;
		GPIO_InitStruct1.instance = OV7620_DATAPORT;
		GPIO_Init(&GPIO_InitStruct1);
	}
	
	//�����ж� PCLK
	GPIO_InitStruct1.pinx = OV7620_PCLK_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = kGPIO_DMA_RisingEdge;
	GPIO_InitStruct1.mode = kGPIO_Mode_IPD;
	GPIO_InitStruct1.instance = OV7620_PCLK_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	//���ж� HREF
	GPIO_InitStruct1.pinx = OV7620_HREF_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = kGPIO_IT_RisingEdge;
	GPIO_InitStruct1.mode = kGPIO_Mode_IPD;
	GPIO_InitStruct1.instance = OV7620_HREF_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	// ���ж� VSYNC
	GPIO_InitStruct1.pinx = OV7620_VSYNC_PIN;
	GPIO_InitStruct1.GPIO_InitState = Bit_SET;
	GPIO_InitStruct1.GPIO_IRQMode = kGPIO_IT_RisingEdge;
	GPIO_InitStruct1.mode = kGPIO_Mode_IPD;
	GPIO_InitStruct1.instance = OV7620_VSYNC_PORT;
	GPIO_Init(&GPIO_InitStruct1);
	
	NVIC_EnableIRQ(PORTB_IRQn);
  //����DMA
  DMA_InitStruct1.chl          = HW_DMA_CH1;         //DMA 1ͨ��
  DMA_InitStruct1.chlTriggerSource   =PORTC_DMAREQ;    //C�˿�(PCLK) ����ѽ����    
	DMA_InitStruct1.triggerSourceMode = kDMA_TriggerSource_Normal;
  DMA_InitStruct1.minorLoopByteCnt = 2;               //������� ��������ͷÿ������������
	DMA_InitStruct1.majorLoopCnt = 170;                   //ÿ�δ���3���ֽ�       

  DMA_InitStruct1.sAddr =(uint32_t)&PTD->PDIR;//����ͷ�˿ڽ�D0-D7
	DMA_InitStruct1.sLastAddrAdj = 0;                  //��ַ������
	DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;       //8BIT����
	DMA_InitStruct1.sAddrOffset = 0;

  DMA_InitStruct1.dAddr =(uint32_t)CCDBuffer;  //DMA �ڴ�
	DMA_InitStruct1.dLastAddrAdj = 0;
	DMA_InitStruct1.sDataWidth = kDMA_DataWidthBit_8;
	DMA_InitStruct1.dAddrOffset = 1;                   //ÿ�δ��� +1���ֽ�
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
        if(ov7725_img_flag == IMG_FAIL)             //����ͼ��ɼ����������²ɼ�
        {
            ov7725_img_flag = IMG_START;            //��ʼ�ɼ�ͼ��
            PORTA->ISFR = ~0;                       //д1���жϱ�־λ
            enable_irq(PORTA_IRQn);                 //����PTA���ж�
        }
    }
}




