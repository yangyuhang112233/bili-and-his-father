#ifndef __CH_LIB_OV7620_BACK_H__
#define __CH_LIB_OV7620_BACK_H__

#include "gpio.h"

//����ͷ����ֱ���
#define OV7620_W2 320
#define OV7620_H2 100

extern uint8_t ov7620_img_flag2;
extern uint8_t CCD_Image2[OV7620_H2][OV7620_W2];


//ʹ��8λ���ݶ˿�(PTC8~PTC15)�ɼ���������ͷOV7620_back��8λ�Ҷ�(Y����)��������
#define OV7620_back_DATA_PORT  PORTC  
#define OV7620_back_DATA_VALU  (PTC->PDIR)    
#define OV7620_back_PORT_INIT  (PTC->PDDR)

#define CAMERA_back_DMA_CH  HW_DMA_CH1   //DMA1ͨ��

/* ״̬�����壬���ڼ�¼���ݲɼ�״̬ */
#define OV7620_STATE_IDLE2          (0)          //����ɼ�
#define OV7620_STATE_START2         (1)		    //���ڲɼ�
#define OV7620_STATE_COMPLETE2      (2)	    	//�ɼ����
#define OV7620_STATE_PROCEED2       (3)          //���ݴ���
#define OV7620_STATE_SENDING2       (4)          //���ݴ���


#define OV7620_back_HREF_PORT  HW_GPIOA
#define OV7620_back_HREF_PIN   (17)
#define OV7620_back_HREF_GPIO_IRQ  PORTA_IRQn

#define OV7620_back_VSYNC_PORT HW_GPIOC
#define OV7620_back_VSYNC_PIN  (16)
#define OV7620_back_VSYN_GPIO_IRQ  PORTC_IRQn

#define OV7620_back_PCLK_PORT  HW_GPIOD
#define OV7620_back_PCLK_PIN  (6)
#define OV7620_back_PCLK_eDMA_IRQ  DMA1_IRQn

#define BOARD_OV7620_DATA_OFFSET    (8) /* ����ͷ���ݲɼ�����PTA8-PTA15 ֻ��Ϊ 0 8 16 24 */

//�ӿں�������
void OV7620_back_Init(void);
void ov7620_DMA_back(void);
void VIsr_back(void);
void HIsr_back(void);
#endif
