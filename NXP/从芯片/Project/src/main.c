#include "head.h"


int main(void)
{  

    jioushu=1;//����7620��7725����ͼƬ�������ɼ��ʹ��� 
    getready();  
    //firstimage();
    
    
    while(1)
    {   
//        UART_WriteByte (HW_UART4,tt-tt1);
//        tt1=tt;        
       
     //  startimage();
            
    ov7620_img_flag = OV7620_STATE_IDLE;            //����״̬����ʼ�ɼ�ͼ��
    PORTE->ISFR = ~0; //�����������ͷ��־λ 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //�ȴ�ͼ��ɼ����
        
          findpoint();      
        if(target_flag==1)
        {
        GPIO_WriteBit(HW_GPIOD, 15,1);   
        GPIO_WriteBit(HW_GPIOC, 0,1);   
        }
        else
        {
        GPIO_WriteBit(HW_GPIOD, 15,0);    
        GPIO_WriteBit(HW_GPIOC, 0,0);   
        }
        
        
//     uint16_t ii,jj;   
//           for(ii=0;ii<OV7620_H;ii++)
//			for(jj=0;jj<OV7620_W;jj++)
//			{                
//				if(CCD_Image[ii][jj]==0xff)
//				CCD_Image[ii][jj]=0xfe;
//				UART_WriteByte(HW_UART4,CCD_Image[ii][jj]);
//			}
//    UART_WriteByte(HW_UART4,0xff);  
//      

    }   
}

