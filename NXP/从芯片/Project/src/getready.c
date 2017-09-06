#include "head.h"

 uint16_t tt=0;//��ʼ��1ms�жϺ����ı���
 
//1ms�жϻص�����
void PIT1_HandlerU( void )
{
	tt++;
}

 void getready()
 {    
    DelayInit();
    
    /* PTA14/C5���ó����룬��ֹ���� */
    GPIO_QuickInit (HW_GPIOA ,14,kGPIO_Mode_OPP);
    GPIO_QuickInit (HW_GPIOC ,5,kGPIO_Mode_OPP);
     
    /* ��������ָʾ�Ƴ�ʼ�� */
    GPIO_QuickInit(HW_GPIOD,15, kGPIO_Mode_OPP); 
    GPIO_QuickInit(HW_GPIOE ,26, kGPIO_Mode_OPP); 

    /* UART�˿ڳ�ʼ�� */
    UART_QuickInit(UART4_RX_PE25_TX_PE24, 115200);
		 
    /* IO��ģ��IIC�˿ڳ�ʼ�� */    /* ������Ķ˿���ȥio2iic.hͷ�ļ����޸� */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    


    /* ��ʼ���������룬�˿ںŷֱ�Ϊ��PA12,PA13;�ң�PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

    /* ϵͳ��ͨ�Žӿڳ�ʼ�� */
    GPIO_QuickInit(HW_GPIOC, 0 ,kGPIO_Mode_OPP);
    

		
	//��ʼ��pitģ���0ͨ��������20ms���ж�
    PIT_QuickInit(HW_PIT_CH0, 20000);
    PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //ע��ͨ��0�Ļص�����Ϊ��QD_value����
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //����ģ��0ͨ���ж� 

    //��ʼ��pitģ���1ͨ��������1ms���ж�
    PIT_QuickInit(HW_PIT_CH1, 1000);
    PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //ע��ͨ��1�Ļص�����Ϊ��PIT1_HandlerU����		
    PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //����ģ��1ͨ���ж� 


    //����ͷ��ʼ��
    OV7620_Init();


/* ���Ź���ʼ��   500ms  */
//   WDOG_QuickInit(500);
}
 

    
void firstimage()
{

    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
    
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
    
    //7620����ͷ��ʼ�ɼ�ͼ��
    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
   	     
}

 void endimage()
{
    //7620 �ɼ�ͼ�����  
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);   //�ȴ�ͼ��ɼ����           
} 

