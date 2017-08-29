#include "head.h"


uint8_t Run_mode=9;
//extern uint8_t img[OV7620_H*OV7620_W];

/* 定义与图像相关数据 */
const uint8_t IMAGE_CENTER = OV7620_W /2;      //图像的绝对中线位置

uint16_t count_target = 0;   //总共白点个数  进行阀值判断



uint8_t target_l_flag; // 限定转弯方向为左转  
uint8_t target_r_flag;//限定转弯方向为右转

 uint16_t desire_l = 170 ;           //前摄像头偏移目标列坐标
 
 uint16_t desire_l_back = 170 ;      //后摄像头偏移目标列坐标
 
//后摄像头
uint16_t target_h_back;//目标行
uint16_t target_l_back;//目标列
uint8_t target_flag_back; //目标找到标志位

// uint32_t target_count_l;  //左转计数
// uint32_t target_count_r;  //右转计数

uint8_t pre_turn_flag=0;



/****************************************************************
* 函数名称: Void getimage()
* 参变量: 获得图像
****************************************************************/
//void getimage()
//{     
//    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
//    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//   	
//     //7725摄像头采集图像  
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
//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
//    
//}
/****************************************************************
* 函数名称: Void sending()
* 参变量: 串口发送图推图像
* 返回值类型
****************************************************************/
//uint32_t gray_sum=0;
//uint32_t point_sum=0;
//void sending(void)
//{
//	uint16_t gray_gate=0;
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//    uint16_t ii,jj;
//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
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
//    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
//	  PORTE->ISFR = ~0; //清除标志位 
////    PORTC->ISFR = ~0; //清除后置摄像头标志位 
////	enable_irq(OV7620_VSYN_GPIO_IRQ);//开启场中断
////    enable_irq(OV7620_back_VSYN_GPIO_IRQ);//开启后置摄像头场中断
//}

//void sending2(void)
//{
//    enable_irq(OV7620_back_VSYN_GPIO_IRQ);
//    uint16_t ii,jj;
//    while(ov7620_img_flag2 != OV7620_STATE_COMPLETE2);            //等待图像采集完毕
//    for(ii=0;ii<OV7620_H2;ii++)
//		for(jj=0;jj<OV7620_W2;jj++)
//		{
//            if(CCD_Image2[ii][jj]==0xff)
//			CCD_Image2[ii][jj]=0xfe;
//			UART_WriteByte(HW_UART0,CCD_Image2[ii][jj]);
//		}
//    UART_WriteByte(HW_UART0,0xff);
//    ov7620_img_flag2 = OV7620_STATE_IDLE2;            //空闲状态，开始采集图像
//    PORTC->ISFR = ~0; //清除后置摄像头标志位 

//}

//通过串口发送7620的图像
void sending3(void)
{
//    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
//    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
//    enable_irq(OV7620_VSYN_GPIO_IRQ);
//    
//	

//    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
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

   
//轮流发送两幅图片
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

//通过串口发送7725的图像
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



