#include "head.h"
 
//1ms�жϻص�����
void PIT1_HandlerU( void )
{
	if(delay_flag==DELAY_START)
	{
		tt++;
	}
}

 void getready()
 {    
    DelayInit();
    
    /* PTA14/C5���ó����룬��ֹ���� */
    //GPIO_QuickInit (HW_GPIOA ,14,kGPIO_Mode_OPP);
    //GPIO_QuickInit (HW_GPIOC ,5,kGPIO_Mode_OPP);
     
    /* ��������ָʾ�Ƴ�ʼ�� */
    GPIO_QuickInit(HW_GPIOD,15, kGPIO_Mode_OPP); 
    GPIO_QuickInit(HW_GPIOE ,26, kGPIO_Mode_OPP); 

    /* UART�˿ڳ�ʼ�� */
    UART_QuickInit(UART4_RX_PE25_TX_PE24, 115200);
		 
    /* IO��ģ��IIC�˿ڳ�ʼ�� */    /* ������Ķ˿���ȥio2iic.hͷ�ļ����޸� */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    
     /* ���뿪�س�ʼ�� */
    GPIO_QuickInit(HW_GPIOB, 0, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 1, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 2, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 3, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 4, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 5, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 6, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 7, kGPIO_Mode_IPU);
       
    /* ��ʼ���������룬�˿ںŷֱ�Ϊ��PA12,PA13;�ң�PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

    /* �������س�ʼ�� */
    GPIO_QuickInit(HW_GPIOA, 4 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOA, 5 , kGPIO_Mode_IPU);

    /* ϵͳ��ͨ�Žӿڳ�ʼ�� */
    GPIO_QuickInit(HW_GPIOC, 0 , kGPIO_Mode_IFT);
         
    /* �����ʼ�� */
    CMT_PWM_QuickInit (55,0);
    /* ���ö����ʹռ�ձȣ���Χ0-10000�ֱ��ʾ0-100% */
    anglex=anglemid;
    CMT_PWM_ChangDuty (anglex);
      
    /* FTM���ٳ�ʼ�� */
    FTM_PWM_QuickInit(FTM0_CH0_PC01, kPWM_EdgeAligned ,10000);     /* ����PC03Ϊ�������˿ڣ�Ƶ���趨Ϊ5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH1_PC02, kPWM_EdgeAligned ,10000);     /* ����PD04Ϊ�������˿ڣ�Ƶ���趨Ϊ5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH2_PC03, kPWM_EdgeAligned ,10000);     /* ����PC03Ϊ�������˿ڣ�Ƶ���趨Ϊ5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH3_PC04, kPWM_EdgeAligned ,10000);     /* ����PD04Ϊ�������˿ڣ�Ƶ���趨Ϊ5000Hz*/
    /* ����FTM��ʹռ�ձȣ���Χ0-10000�ֱ��ʾ0-100% */
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH0, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH1, 0);
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 0);
		
	//��ʼ��pitģ���0ͨ��������15ms���ж�
    PIT_QuickInit(HW_PIT_CH0, 15000);
    PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //ע��ͨ��0�Ļص�����Ϊ��QD_value����
    PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //����ģ��0ͨ���ж� 

    //��ʼ��pitģ���1ͨ��������1ms���ж�
    PIT_QuickInit(HW_PIT_CH1, 1000);
    PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //ע��ͨ��1�Ļص�����Ϊ��PIT1_HandlerU����		
    PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //����ģ��1ͨ���ж� 
	
	/*��ʼ��pitģ���2ͨ��������10ms�ж�*/
	PIT_QuickInit(HW_PIT_CH2, 10000);
    PIT_CallbackInstall(HW_PIT_CH2, Motor_PID_Output ); //ע��ͨ��0�Ļص�����Ϊ��QD_value����
    PIT_ITDMAConfig(HW_PIT_CH2, kPIT_IT_TOF, ENABLE); //����ģ��0ͨ���ж� 


//	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
//	NVIC_SetPriority(OV7620_HREF_GPIO_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,1));
//	NVIC_SetPriority(OV7620_VSYN_GPIO_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,2));
//	NVIC_SetPriority(OV7620_PCLK_eDMA_IRQ,NVIC_EncodePriority(NVIC_PriorityGroup_2,1,3));
//	
//	NVIC_SetPriority(PORTA_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,2,1));
//	NVIC_SetPriority(DMA2_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,2,2));
//	
//	NVIC_SetPriority(PIT0_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,3,1));
//	
//	NVIC_SetPriority(PIT2_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,3,2));
//	
//	NVIC_SetPriority(PIT1_IRQn,NVIC_EncodePriority(NVIC_PriorityGroup_2,4,1));
    //СҺ����ʼ��
    LCD_Init();

    //����ͷ��ʼ��
    OV7620_Init();
//    ov7725_Init();

/* ���Ź���ʼ��   500ms  */
//   WDOG_QuickInit(500);
}
 
void Printf()
{
   //�ű���ʾ
    LCD_printf(10,5,"target:   ");
    LCD_printf(10,5,"target:%d",target_flag);
    
    LCD_printf(60,5,"th:   ");
    LCD_printf(60,5,"th:%d",target_h);
    
    LCD_printf(10,20,"tl:   ");
    LCD_printf(10,20,"tl:%d",target_l);

    //�ϰ�����ʾ
//    LCD_printf(60,20,"bar2:    "); 
//    LCD_printf(60,20,"bar2:%d",barrier); 
//    
//    LCD_printf(10,35,"bh:   ");
//    LCD_printf(10,35,"bh:%d",barrier_h);
//    
//    LCD_printf(60,35,"bl:   ");
//    LCD_printf(60,35,"bl:%d",barrier_l);
    
       
    //�����ڼ�����
    LCD_printf(10,50,"co1:    "); 
    LCD_printf(10,50,"co1:%d",count1); 
    
    LCD_printf(60,50,"7c:  "); 
    LCD_printf(60,50,"7c:%d",countbz7620); 
    
//  LCD_printf(60,50,"7c:  "); 
//  LCD_printf(60,50,"7c:%d",count7725); 
    
    LCD_printf(10,65,"state:   ");
    LCD_printf(10,65,"state:%d",state);
    
    //�ϰ�����ű��֮���ƽ������
    LCD_printf(60,65,"juli:   ");
    LCD_printf(60,65,"juli:%d",juli);
    
    
    LCD_printf(10,95,"speed:    "); 
    LCD_printf(10,95,"speed:%d",speedx);

    LCD_printf(60,95,"xx:    "); 
    LCD_printf(60,95,"xx:%d",xinbiaoxiangsu);

}

void firstimage()
{
   while(1)
{
    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
    
        int count=0;
         for(int ii=0;ii<OV7620_H-2;ii++)	
    {     
       for(int jj=0;jj<OV7620_W-1;jj++)
       {
         if(CCD_Image[ii][jj]>=door7620)
         {   
			 count ++;
         }      
       }
  }          
	beacon_right_flag=PCin(0);
   if((count>2)||(beacon_right_flag==1))
   {
	   break;
   }       
}
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


//ɲ������
void stopmove()
{
    uint16_t leftspeed=0;
    uint16_t rightspeed=0;
         
    int16_t Kp=1200;
    int16_t Ki=0;
    int16_t leftsum ;
    int16_t rightsum ;
                    
    int16_t lefterror;//�ٶ�ƫ��
    int16_t righterror;  
    int32_t pwm_out1;//pwm���	
    int32_t pwm_out2;    
       
      while(1)       
     {               
     //pi����ʵ��  

      lefterror = leftspeed - qd_left_value ;
      righterror= rightspeed - qd_right_value ;	
		
	  leftsum+= lefterror ;//���ֵ��ڵĻ�����
      rightsum  += righterror ;
       
	  if(leftsum >= 800)leftsum = 800;
	  if(leftsum <= -400)leftsum = -400;
	  if(rightsum  >= 800) rightsum  = 800;
	  if(rightsum  <= -400)rightsum  = -400;
            
      pwm_out1 =   Kp*lefterror + Ki*leftsum  ;
	  pwm_out2 =   Kp*righterror + Ki*rightsum   ;

	  	     
        //��ֵֹ�����޶�
		if(pwm_out1>=10000)
		{
			pwm_out1=10000;
		}
		if(pwm_out2>=10000)
		{
			pwm_out2=10000;
		}
        
		if(pwm_out1<-10000)
		{
			pwm_out1=-10000;
		}
		if(pwm_out2<-10000)
		{
			pwm_out2=-10000;
		}
	     
	    if(pwm_out1 > 0)
		{
	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
		}
		else
		{
		pwm_out1 = -pwm_out1 ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1 );
		}
		
		if(pwm_out2 > 0)
		{
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
		}
		else
		{
		pwm_out2 = -pwm_out2 ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
		}
        
        if(qd_left_value+qd_right_value<1)
        {
         while(1)
         {
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0); 
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
         }
        }    
      }
}

