#include "head.h"


uint8_t Run_mode=9;
//extern uint8_t img[OV7620_H*OV7620_W];

/* ������ͼ��������� */
const uint8_t IMAGE_CENTER = OV7620_W /2;      //ͼ��ľ�������λ��

uint16_t count_target = 0;   //�ܹ��׵����  ���з�ֵ�ж�



uint8_t target_l_flag; // �޶�ת�䷽��Ϊ��ת  
uint8_t target_r_flag;//�޶�ת�䷽��Ϊ��ת

 uint16_t desire_l = 170 ;           //ǰ����ͷƫ��Ŀ��������
 
 uint16_t desire_l_back = 170 ;      //������ͷƫ��Ŀ��������
 
//������ͷ
uint16_t target_h_back;//Ŀ����
uint16_t target_l_back;//Ŀ����
uint8_t target_flag_back; //Ŀ���ҵ���־λ

// uint32_t target_count_l;  //��ת����
// uint32_t target_count_r;  //��ת����

uint8_t pre_turn_flag=0;



/****************************************************************
* ��������: Void getimage()
* �α���: ���ͼ��
****************************************************************/
//void getimage()
//{     
//    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
//    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//   	
//     //7725����ͷ�ɼ�ͼ��  
//     ov7725_Get_Imge();
//     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));
//    
//    
//    
//    
//    
//    
//    
//    
//	  uint16_t ii,jj;
//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
//    
//}
/****************************************************************
* ��������: Void sending()
* �α���: ���ڷ���ͼ��ͼ��
* ����ֵ����
****************************************************************/
//uint32_t gray_sum=0;
//uint32_t point_sum=0;
//void sending(void)
//{
//	uint16_t gray_gate=0;
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//    uint16_t ii,jj;
//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
//	gray_sum=0;
//	point_sum=0;
//    for(ii=0;ii<OV7620_H;ii++)
//		for(jj=0;jj<OV7620_W;jj++)
//		{
//			if(jj<=110 && ii >= (60+jj*4/11))
//				CCD_Image[ii][jj]=0;
//			else  if(jj >= 210 && jj <= 320 && ii>=(60 + (320-jj)*4/11))
//				CCD_Image[ii][jj]=0;
//			else if(ii>=95)
//				CCD_Image[ii][jj]=0;
//      else
//			{
//				point_sum++;
//				gray_sum=gray_sum+CCD_Image[ii][jj];
//			}
//			
//			if(CCD_Image[ii][jj]==0xff)
//			CCD_Image[ii][jj]=0xfe;
//		}
//		
//		
//		gray_gate=gray_sum/point_sum;
//		
//		for(ii=0;ii<OV7620_H;ii++)
//		for(jj=0;jj<OV7620_W;jj++)
//		{
//		if(CCD_Image[ii][jj]>=gray_gate+50)
//			CCD_Image[ii][jj]=0xfe;
//		else
//			CCD_Image[ii][jj]=0x01;
//			
//    UART_WriteByte(HW_UART0,CCD_Image[ii][jj]);
//		}
//		
//		
//		
//		
//		
//    UART_WriteByte(HW_UART0,0xff);
//    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
//	  PORTE->ISFR = ~0; //�����־λ 
////    PORTC->ISFR = ~0; //�����������ͷ��־λ 
////	enable_irq(OV7620_VSYN_GPIO_IRQ);//�������ж�
////    enable_irq(OV7620_back_VSYN_GPIO_IRQ);//������������ͷ���ж�
//}

//void sending2(void)
//{
//    enable_irq(OV7620_back_VSYN_GPIO_IRQ);
//    uint16_t ii,jj;
//    while(ov7620_img_flag2 != OV7620_STATE_COMPLETE2);            //�ȴ�ͼ��ɼ����
//    for(ii=0;ii<OV7620_H2;ii++)
//		for(jj=0;jj<OV7620_W2;jj++)
//		{
//            if(CCD_Image2[ii][jj]==0xff)
//			CCD_Image2[ii][jj]=0xfe;
//			UART_WriteByte(HW_UART0,CCD_Image2[ii][jj]);
//		}
//    UART_WriteByte(HW_UART0,0xff);
//    ov7620_img_flag2 = OV7620_STATE_IDLE2;            //����״̬����ʼ�ɼ�ͼ��
//    PORTC->ISFR = ~0; //�����������ͷ��־λ 

//}

//ͨ�����ڷ���7620��ͼ��
void sending3(void)
{
//    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
//    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//    
//	

//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
//   
     uint16_t ii,jj;   

if(jioushu==0)  
{    
    for(ii=0;ii<OV7620_H;ii++)
			for(jj=0;jj<OV7620_W;jj++)
			{                
				if(CCD_Image[ii][jj]==0xff)
				CCD_Image[ii][jj]=0xfe;
				UART_WriteByte(HW_UART4,CCD_Image[ii][jj]);
			}
    UART_WriteByte(HW_UART4,0xff); 
}
else
{
    for(ii=0;ii<OV7620_H;ii++)
			for(jj=0;jj<OV7620_W;jj++)
			{                
							if(CCD_Image22[ii][jj]==0xff)
				CCD_Image22[ii][jj]=0xfe;
				UART_WriteByte(HW_UART4,CCD_Image22[ii][jj]);
			}
    UART_WriteByte(HW_UART4,0xff); 
}

}

   
//������������ͼƬ
//    uint16_t ii1,jj1;
//        if(jioushu==1)
//    {
//    for(ii1=0;ii1<OV7620_H;ii1++)
//			for(jj1=0;jj1<OV7620_W;jj1++)
//			{                
//							if(CCD_Image[ii1][jj1]==0xff)
//				CCD_Image[ii1][jj1]=0xfe;
//				UART_WriteByte(HW_UART0,CCD_Image[ii1][jj1]);
//			}
//    UART_WriteByte(HW_UART0,0xff);
//     }
//    else
//    {
//    for(ii1=0;ii1<OV7620_H;ii1++)
//			for(jj1=0;jj1<OV7620_W;jj1++)
//			{                
//							if(CCD_Image22[ii1][jj1]==0xff)
//				CCD_Image22[ii1][jj1]=0xfe;
//				UART_WriteByte(HW_UART0,CCD_Image22[ii1][jj1]);
//			}
//    UART_WriteByte(HW_UART0,0xff);
//    } 

//ͨ�����ڷ���7725��ͼ��
//void sending_7()
//{
//    uint8_t colour[2] = {0xfe, 0x00};
//    uint8_t temp=0;
//    for(uint16_t i=0;i<(OV7725_H*OV7725_W);i++)
//    {
//        if(i==(temp*OV7725_W +center[temp]))
//        {
//            temp++;
//            UART_WriteByte (HW_UART0 ,0);
//        }
//        else
//            UART_WriteByte (HW_UART0 ,colour [img[i]]);
//    }
//    UART_WriteByte(HW_UART0,0xff);
//}   



