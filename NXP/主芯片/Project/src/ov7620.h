#ifndef __CH_LIB_OV7620_H__
#define __CH_LIB_OV7620_H__

#include "head.h"

//����ͷ����ֱ���
#define OV7620_W 320
#define OV7620_H 100


extern DMA_InitTypeDef DMA_InitStruct1; 



extern uint8_t ov7620_img_flag;

extern uint8_t CCD_Image[OV7620_H][OV7620_W];//��һ��ͼ��
extern uint8_t CCD_Image22[OV7620_H][OV7620_W];//��һ��ͼ��

//��������OV7620CC��GPIO�ܽ�״̬���塣
//ʹ��8λ���ݶ˿�(PTE0~PTE7)�ɼ���������ͷOV7620��8λ�Ҷ�(Y����)��������
#define OV7620_DATA_PORT  PORTE  
#define OV7620_DATA_VALU  (PTE->PDIR)    
#define OV7620_PORT_INIT  (PTE->PDDR)

#define CAMERA_DMA_CH  HW_DMA_CH0   //DMA0ͨ��
//HW_DMA_CH0��DMA0_IRQn��ֵ���,���ߵ�ͬ
//  DMA0_IRQn                    = 0,                /**< DMA Channel 0 Transfer Complete */
//  DMA1_IRQn                    = 1,                /**< DMA Channel 1 Transfer Complete */
//  DMA2_IRQn                    = 2,                /**< DMA Channel 2 Transfer Complete */
//  DMA3_IRQn                    = 3,                /**< DMA Channel 3 Transfer Complete */

/* ״̬�����壬���ڼ�¼���ݲɼ�״̬ */
#define OV7620_STATE_IDLE          (0)          //����ɼ�
#define OV7620_STATE_START         (1)		    //���ڲɼ�
#define OV7620_STATE_COMPLETE      (2)	    	//�ɼ����
#define OV7620_STATE_PROCEED       (3)          //���ݴ���
#define OV7620_STATE_SENDING       (4)          //���ݴ���


//���ж�
#define OV7620_HREF_PORT  HW_GPIOD
#define OV7620_HREF_PIN   (14)
#define OV7620_HREF_GPIO_IRQ  PORTD_IRQn

//���ж�
#define OV7620_VSYNC_PORT HW_GPIOE
#define OV7620_VSYNC_PIN  (11)
#define OV7620_VSYN_GPIO_IRQ  PORTE_IRQn

//�����ж�
#define OV7620_PCLK_PORT  HW_GPIOE
#define OV7620_PCLK_PIN  (10)
#define OV7620_PCLK_eDMA_IRQ  DMA0_IRQn

//�ӿں�������
void OV7620_Init(void);
void ov7620_DMA(void);//��������
void VIsr(void);//���ж�
void HIsr(void);//���ж�
#endif
