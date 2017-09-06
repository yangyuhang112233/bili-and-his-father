#ifndef _OV7725_INIT_H_
#define _OV7725_INIT_H_

#include <stdint.h>


// �ı�����ͷ�ɼ�ͼ��Ĵ�С
#define IMAGE_SIZE  0

//�ɼ���ͼ���80���أ�60��
#if (IMAGE_SIZE  ==  0)
#define OV7725_W    (80)
#define OV7725_H    (60)

//�ɼ���ͼ���160���أ�120��
#elif (IMAGE_SIZE == 1)
#define OV7725_W    (160)
#define OV7725_H    (120)

//�ɼ���ͼ���240���أ�180��
#elif (IMAGE_SIZE == 2)
#define OV7725_W    (240)
#define OV7725_H    (180)


#else
#error "Image Size Not Support!"
#endif

#define CAMERA_7_DMA_CH  HW_DMA_CH2
#define OV7725_PORT_INIT1111  (PTC->PDDR)
/*BITBAND�궨����*/
#define BITBAND(Reg,Bit) ((uint32_t volatile*)(0x22000000 + (32*((uint32_t)&(Reg) - (uint32_t)0x20000000)) + (4*((uint32_t)(Bit)))))

/* ״̬�����壬���ڼ�¼���ݲɼ�״̬ */
typedef enum
{
    IMG_NOTINIT = 0,
    IMG_FINISH,             //ͼ��ɼ����
    IMG_FAIL,               //ͼ��ɼ�ʧ��
    IMG_GATHER,             //ͼ��¼���
    IMG_START,              //��ʼ�ɼ�ͼ��
    IMG_STOP,               //��ֹͼ��ɼ�
}OV7725_Status;

extern uint8_t CCDBufferPool[OV7725_H*(OV7725_W/8)];

extern uint8_t img[OV7725_H*OV7725_W];



extern int8_t center[OV7725_H];

extern volatile OV7725_Status ov7725_img_flag;



//�û�����ӿ�����
void extract(void);
int SCCB_Init(void);
void OV_ISR(uint32_t index);
void ov7725_Init(void);
void ov7725_Get_Imge(void);
void img_extract(uint8_t *dst, uint8_t *src, uint32_t srclen);

#endif
