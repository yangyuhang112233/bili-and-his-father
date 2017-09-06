#include "cmt.h"
#include "common.h"
#include "gpio.h"
#include <stdint.h>

static uint16_t FullDuty; 

void CMT_PWM_QuickInit(uint16_t fre,uint16_t duty)
{
    uint32_t clock;
    /* ��ȡϵͳ��ʱ��Ƶ�� */
    CLOCK_GetClockFrequency(kBusClock, &clock);
    /* CMTʱ��ʹ�� */
    SIM->SCGC4 |=SIM_SCGC4_CMT_MASK ;
    /* ���Ÿ��� */
    PORT_PinMuxConfig (HW_GPIOD ,7,kPinAlt2);
    /* ����ʱ�ӷ�Ƶ������IFʱ���ź� */
    CMT->PPS =CMT_PPS_PPSDIV(10);
    /* CMTʱ�� IFʱ���źŷ�Ƶ */
    CMT->MSC =CMT_MSC_CMTDIV (0);
    /* ����Ƶ�ʼ������ֵ */
    FullDuty =clock /(80*fre);
    
    CMT->CMD1 =(uint8_t)((duty >>8)&CMT_CMD1_MB_MASK);
    CMT->CMD2 =(uint8_t)(duty&CMT_CMD2_MB_MASK);
    CMT->CMD3 =(uint8_t )(((FullDuty -duty)>>8)&CMT_CMD3_SB_MASK);
    CMT->CMD4 =(uint8_t )((FullDuty -duty)&CMT_CMD4_SB_MASK);
    
    /* ����ģʽʹ�� */
    CMT->MSC &= ~CMT_MSC_FSK_MASK;
    CMT->MSC |=CMT_MSC_BASE_MASK; 
    /* �ز����Ʋ�ʹ�� */
    CMT->MSC |=CMT_MSC_MCGEN_MASK ;   
    /* ��ת��ƽ */
    CMT->OC |=CMT_OC_CMTPOL_MASK ;
    /*  ���ʹ�� */
    CMT->OC |=CMT_OC_IROPEN_MASK ;    
}

void CMT_PWM_ChangDuty(uint16_t duty)
{
    duty=duty*FullDuty/10000;
    CMT->CMD1 =(uint8_t)((duty >>8)&CMT_CMD1_MB_MASK);
    CMT->CMD2 =(uint8_t)(duty&CMT_CMD2_MB_MASK);
    CMT->CMD3 =(uint8_t )(((FullDuty -duty)>>8)&CMT_CMD3_SB_MASK);
    CMT->CMD4 =(uint8_t )((FullDuty -duty)&CMT_CMD4_SB_MASK);
}
