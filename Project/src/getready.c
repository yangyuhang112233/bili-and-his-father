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
    
    /* PTA4���ó����룬��ֹ���� */
    GPIO_QuickInit (HW_GPIOA ,4,kGPIO_Mode_OPP);
    
    /* ��������ָʾ�Ƴ�ʼ�� */
    GPIO_QuickInit(HW_GPIOA ,15, kGPIO_Mode_OPP); 

    /* UART�˿ڳ�ʼ�� */
    UART_QuickInit(UART0_RX_PB16_TX_PB17, 115200);
		 
    /* IO��ģ��IIC�˿ڳ�ʼ�� */    /* ������Ķ˿���ȥio2iic.hͷ�ļ����޸� */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    
     /* ���뿪�س�ʼ�� */
    GPIO_QuickInit(HW_GPIOB, 8 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 9 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 10, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 11, kGPIO_Mode_IPU);
     
    /* ��ʼ���������룬�˿ںŷֱ�Ϊ��PA12,PA13;�ң�PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

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
		
		 //��ʼ��pitģ���0ͨ��������20ms���ж�
      PIT_QuickInit(HW_PIT_CH0, 20000);
      PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //ע��ͨ��0�Ļص�����Ϊ��QD_value����
      PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //����ģ��0ͨ���ж� 
        
        //��ʼ��pitģ���1ͨ��������1ms���ж�
	  PIT_QuickInit(HW_PIT_CH1, 1000);
      PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //ע��ͨ��1�Ļص�����Ϊ��PIT1_HandlerU����		
	  PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //����ģ��1ͨ���ж� 
		
  
		//turn_side=TurnSide_Array[0];
    //СҺ����ʼ��
    LCD_Init();
    
    //����ͷ��ʼ��
    OV7620_Init();
    ov7725_Init();

    /* ���Ź���ʼ��   500ms  */
//   	WDOG_QuickInit(500);
 
 
 }
 
//�����õ��ж���ʱ����
// void wait(uint16_t time)
// {
//     uint16_t tt1,tt2;
//    tt2=tt;
//     if(tt2>65535-time)tt2=time-(65535-tt2);//��ֹtt��65535������Ϊ0
//     else
//         tt2=tt2+time;
//     while(tt1>tt2)
//     {
//     tt1=tt;
//     }
// 
// }
  
 
  /**************************************************************
* ��������:void Printf()
* ��飺������ʾ
**************************************************************/
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
    
        LCD_printf(60,20,"bar2:    "); 
    LCD_printf(60,20,"bar2:%d",barrier); 
    
    LCD_printf(10,35,"bh:   ");
    LCD_printf(10,35,"bh:%d",barrier);
    
    LCD_printf(60,35,"bl:   ");
    LCD_printf(60,35,"bl:%d",barrier);
    
    
    //�����ڼ�����
    LCD_printf(10,50,"co1:    "); 
    LCD_printf(10,50,"co1:%d",count1); 
    
    LCD_printf(60,50,"7c:  "); 
    LCD_printf(60,50,"7c:%d",countbz7620); 
    
//        LCD_printf(60,50,"7c:  "); 
//    LCD_printf(60,50,"7c:%d",count7725); 
    
    LCD_printf(10,65,"state:   ");
    LCD_printf(10,65,"state:%d",state);
    
    //�ϰ�����ű��֮���ƽ������
    LCD_printf(60,65,"juli:   ");
    LCD_printf(60,65,"juli:%d",juli);
    
  
    LCD_printf(10,75,"fazhi:   ");
    LCD_printf(10,75,"fazhi:%d",xiangsuzhi);
    
    
    LCD_printf(10,95,"speed:    "); 
    LCD_printf(10,95,"speed:%d",speedx);

    LCD_printf(60,95,"xx:    "); 
    LCD_printf(60,95,"xx:%d",xinbiaoxiangsu);
//    LCD_printf(10,75,"st:   ");
//    LCD_printf(10,75,"st:%d",stopba);
//    
//    LCD_printf(10,95,"xbb:    "); 
//    LCD_printf(10,95,"xbb:%d",xinbiaobizhang);
    

    
}
void duqubama()
{
		if(GPIO_ReadBit(HW_GPIOB, 8)==0)    //���뿪�ؿ���  
       {
		   bama[0]=1;
       }      
       	if(GPIO_ReadBit(HW_GPIOB, 9)==0)    //���뿪�ؿ���  
       {
		 bama[1]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 10)==0)    //���뿪�ؿ���  
       {
		bama[2]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 11)==0)    //���뿪�ؿ���  
       {
		 bama[3]=1;
       }   
       bamakaiguan=bama[0]+2* bama[1]+2*2*bama[2]+2*2*2*bama[3];
}
void bamaswitch()
{
    
             //���뿪��״̬���

    switch(bamakaiguan)
{
         
case 1:  //��led��ʾ��
Printf();
        break;
case  2://���õ�����
                     
speedzhuanwan=15;        //Ѱ���ű�ת���ٶ�
speedjiasu=15;            //Զ���ű� ֱ�߼���
speedxinjiansu=15;        //�����ű� ���м���
speedxinjia=15;          //�����ű� �ٶ�̫�� ������
speeddazhuan=15;         //�Ҳ����ű��ת���ٶ�
speedbizhang=15;          //���ϼ���
speedxinbi1=15;            //�ű���ϼ���
speedxinbi2=15;            //�ű���ϼ���

//speedxinbijia=15;          //�ű����ʱ̫���������                

      break; 
         
case 4:
sending3();
        
      break;   
        
case 8:   //��7725ͼ��
    
       //7725����ͷ�ɼ�ͼ��  
     ov7725_Get_Imge();
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));

    uint8_t colour[2] = {0xfe, 0x00};
    uint8_t temp=0;
    for(uint16_t i=0;i<(OV7725_H*OV7725_W);i++)
    {
        if(i==(temp*OV7725_W +center[temp]))
        {
            temp++;
            UART_WriteByte (HW_UART0 ,0);
        }
        else
            UART_WriteByte (HW_UART0 ,colour [img[i]]);
    }
    UART_WriteByte(HW_UART0,0xff);
 break;
      
    case  3:
                 xideng=1;    
                

      break;
        case  5:
                 xideng=5;    
               
      break;
        
       case  7:
           
       xideng=5;    
 speedzhuanwan=15;        //Ѱ���ű�ת���ٶ�
speedjiasu=15;            //Զ���ű� ֱ�߼���
speedxinjiansu=15;        //�����ű� ���м���
speedxinjia=15;          //�����ű� �ٶ�̫�� ������
speeddazhuan=15;         //�Ҳ����ű��ת���ٶ�
speedbizhang=15;          //���ϼ���
speedxinbi1=15;            //�ű���ϼ���
speedxinbi2=15;            //�ű���ϼ���
//speedxinbijia=15;          //�ű����ʱ̫���������  
      break;
        
default:break;    
}
         
         
         
}

void firstimage()
{
         //���ó�ͣס���������ٿ�ʼ��
//         while(target_flag==0)
//        {
//          findpoint();
//        }
    
   
     //�ɼ���һ��ͼ��
    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
   	
     //7725����ͷ�ɼ�ͼ��  
     ov7725_Get_Imge();
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));
       
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
   	    
   
     //7725����ͷ��ʼ�ɼ�ͼ��
    ov7725_img_flag = IMG_START;                    //��ʼ�ɼ�ͼ��
    PORTA->ISFR = ~0;                               //д1���жϱ�־λ
    enable_irq(PORTA_IRQn);                         //����PTA���ж�
    
    
}

 void endimage()
{
    
      //7725 �ɼ�ͼ�����       
    while(ov7725_img_flag != IMG_FINISH)            //�ȴ�ͼ��ɼ����
    {
        if(ov7725_img_flag == IMG_FAIL)           //����ͼ��ɼ����������²ɼ�
        {
            ov7725_img_flag = IMG_START;            //��ʼ�ɼ�ͼ��
            PORTA->ISFR = ~0;                       //д1���жϱ�־λ
            enable_irq(PORTA_IRQn);                 //����PTA���ж�
        }
    }  
       
       if(jioushu==1)
    {
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));
    }
    else
    {
     img_extract(img22, CCDBufferPool ,OV7725_H*(OV7725_W/8));
    }
    
    
    //7620 �ɼ�ͼ�����  
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);   //�ȴ�ͼ��ɼ����           
} 


//ɲ������
void stopmove()
{
     uint16_t leftspeed=0;
     uint16_t rightspeed=0;
             
    static int16_t Kp=1200;
    static int16_t Ki=0;
    
    static int16_t leftsum ;
    static int16_t rightsum ;
              
                 
      int16_t lefterror;//�ٶ�ƫ��
      int16_t righterror;  
      int32_t pwm_out1;//pwm���	
      int32_t pwm_out2;  
      uint16_t avespeed; //��ǰ�ٶ�
       
    
          while(1)       
     {         
      //����������
              
   
  
    
      //״̬�ж��Լ�������ֵ��  
     avespeed=(qd_left_value+qd_right_value)/2;
    

          
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
		if(pwm_out1>=7000)
		{
			pwm_out1=7000;
		}
		if(pwm_out2>=7000)
		{
			pwm_out2=7000;
		}
        
		if(pwm_out1<-7000)
		{
			pwm_out1=-7000;
		}
		if(pwm_out2<-7000)
		{
			pwm_out2=-7000;
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



  //���Ժ���
  void test()
  {
      uint16_t ch;
      uint8_t ch1;
   if(UART_ReadByte(HW_UART0, &ch) == 0)
    {
               
           UART_WriteByte(HW_UART0,ch);//���ڽ������ݵļĴ�����16λ��
        
           ch1=(uint8_t)ch;

           UART_WriteByte(HW_UART0,ch);//����������ܵ����ַ�
        
               
               
                 switch(ch1)
              {
                  
                case '1':
                    
                 while(1)
                {
//                ov7725_Get_Imge();                    //��ȡͼ��
//                img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));   //��ͼ�񱣴�������img��  0��ʾ��ɫ 1��ʾ��ɫ                 
//                sending_7();
              
                }
                break;
             
                case '2':
                 while(1)
                {
                   
                sending3();
                             
                }     
        
                break;
               
//                  
//                case '3':
//                    CMT_PWM_ChangDuty (600);
//                break;
//                  
//                case '4':   
//                    CMT_PWM_ChangDuty (590);
//                break;
//                   
//                case '5':
//                      CMT_PWM_ChangDuty (580);
//                break;
//                  case '6':
//                    CMT_PWM_ChangDuty (570);
//                break;
//                  
//                case '7':   
//                    CMT_PWM_ChangDuty (560);
//                break;
//                   
//                case '8':
//                      CMT_PWM_ChangDuty (535);
//                break;
                default:
                    break;
             }
     }
  
  
  }