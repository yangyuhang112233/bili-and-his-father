#include "Drv_LCD.h"
#include "common.h"
#include "gpio.h"
#include "spi.h"
#include "ov7620.h"
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "SimSun6x12.h"
   
extern volatile uint8_t left[2][120],right[2][120];

bool display_on_LCD = 1;

static font_t _gFontTbl[] = 
{
    {"SimSun", FONT_SimSun6x12_XSize, FONT_SimSun6x12_YSize, FONT_SimSun6x8 },
};

/**********LCD��ʼ������**********/
//��������
//���أ���
//��ע��LCD_SCK -- PTB21
//      LCD_SDA -- PTB22
//      LCD_A0  -- PTE9
//      LCD_RESET -- PTE8
//      LCD_CS0 -- PTB20
/*********************************/
void LCD_Init(void)
{
	/*��ʼ��GPIO*/
	GPIO_QuickInit(HW_GPIOB,20,kGPIO_Mode_OPP);
	GPIO_QuickInit(HW_GPIOE,8 ,kGPIO_Mode_OPP);
	GPIO_QuickInit(HW_GPIOE,9 ,kGPIO_Mode_OPP);
	
	/*��ʼ��SPI1*/
	SPI_QuickInit(SPI2_SCK_PB21_SOUT_PB22_SIN_PB23,kSPI_CPOL0_CPHA0,25000000);
	
	/*ʹ�ܷ���FIFO*/
	SPI_EnableTxFIFO(HW_SPI2,ENABLE);
	
	/*Ӳ����λLCD*/
	LCD_RESET_LOW;
	DelayMs(100);
	LCD_RESET_HIGH;
	DelayMs(100);
	
	/*LCD��ʼ������*/
	/*�˳�˯��ģʽ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x11,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	DelayMs(20);
	
	/*����Ĭ��Gammaֵ*/
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x26,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x04,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����֡��*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xB1,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x0E,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x10,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����VRH1[4:0] & VC[2:0] for VCI1 & GVDD*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xC0,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x08,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����BT[2:0] for AVDD & VCL & VGH & VGL*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xC1,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x05,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����VMH[6:0] & VML[6:0] for VOMH & VCOML*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xC5,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x38,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x40,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*������ɫ��ʽ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3A,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x05,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*���ô洢ͨ������*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x36,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xC8,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*�����е�ַ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2A,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x7F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����ҳ��ַ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2B,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x9F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*������ʾ��ת����*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xB4,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*ʹ��Gammaλ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xF2,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x01,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*������GammaУ������*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xE0,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x22,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x20,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x30,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x29,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x0C,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x4E,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xB7,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3C,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x19,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x22,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x1E,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x02,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x01,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*���ø�GammaУ������*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0xE1,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x00,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x1B,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x1F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x0F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x16,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x13,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x31,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x84,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x43,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x06,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x1D,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x21,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3D,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3E,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x3F,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����ʾ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x29,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*ȫ�ױ���ɫ*/
	LCD_Display_BackgroundColor(WHITE);
	
}
	
/**********LCD��ʾ��ɫ����**********/
//������color-16λRGB565��ɫ����
//���أ���
//��ע��
void LCD_Display_BackgroundColor(uint16_t color)
{
	uint8_t i,j;
	
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2C,HW_SPI_CS0,kSPI_PCS_KeepAsserted);
	LCD_A0_HIGH;
	for(i = 0;i < 128;i++)
		for(j = 0;j < 128;j++)
		{
			SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,color>>8,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
			SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,color,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
		}
}

/**********LCD���㺯��**********/
//������x-�����꣬y-�����꣬color-16λRGB565��ɫ����
//���أ���
//��ע��
void LCD_Draw_Point(uint8_t x,uint8_t y,uint16_t color)
{
	/*�����е�ַ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2A,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,x,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,x,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*����ҳ��ַ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2B,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,y,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,y,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
	/*д������*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x2C,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	LCD_A0_HIGH;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,color>>8,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,color,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	
}

/**********LCD���ߺ���**********/
//��������
//���أ���
//��ע��
void LCD_Sleep(void)
{
	/*�ر���ʾ������˯��ģʽ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x28,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x10,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
}

/**********LCD���Ѻ���**********/
//��������
//���أ���
//��ע��
void LCD_WakeUp(void)
{
	/*�˳�˯��ģʽ��������ʾ*/
	LCD_A0_LOW;
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x11,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
	SPI_ReadWriteByte(HW_SPI2,HW_CTAR0,0x29,HW_SPI_CS0,kSPI_PCS_ReturnInactive);
}

/*******LCD��ʾͼ����Ϣ*******/
//��������
//���أ���
//��ע��
//void LCD_DispImg()
//{
//    int8_t i,j;
//    uint16_t colour[2] = {WHITE,BLACK};
//    //��ʾԭʼͼ����Ϣ
//    for(i=0;i<OV7620_H;i++)
//        for(j=0;j<OV7620_W;j++)
//        {
//            if(j==center[i])
//                LCD_Draw_Point(center[i],OV7620_H-i,BLUE);                         
//            else
//                LCD_Draw_Point(j,OV7620_H-i,colour[*(img+i*OV7620_W+j)]);       
//        }
//    for(i=0;i<OV7620_H;i+=10)        
//        for(j=OV7620_W;j<OV7620_W+15;j++)
//            LCD_Draw_Point(j,i,RED);
//    /*��ʾ�������������*/     
//    Printf();
//}

/*******LCD�����ַ���ʾ����*******/
//��������
//���أ���
//��ע��
void _LCD_DispChar(char c, int x, int y, const char *pdata, int font_xsize, int font_ysize, int fcolor, int bcolor)
{
    uint8_t j,pos,t;
    uint8_t temp;
    uint8_t XNum;
    uint32_t base;
    XNum = (font_xsize/8) + 1;
    if(font_ysize%8 == 0)
    {
        XNum--;
    }
    if(c < ' ')
    {
        return;
    }
    c = c - ' ';
    base = (c*XNum*font_ysize);

    for(j=0;j<XNum;j++)
    {
        for(pos = 0; pos < font_ysize; pos++)
        {
            temp = (uint8_t)pdata[base+pos+j*font_ysize];
            if(j < XNum)
            {
                for(t = 0; t < 8; t++)
                {
                    if((temp>>t)&0x01)
                    {
                        LCD_Draw_Point(x+t, y+pos,fcolor);
                    }
                    else
                    {
                        LCD_Draw_Point(x+t, y+pos,bcolor);
                    }
                }
            }
            else
            {
                for(t = 0; t < font_xsize%8; t++)
                {
                    if((temp>>t)&0x01)
                    {
                        LCD_Draw_Point(x+t, y+pos,fcolor);
                    }
                    else
                    {
                        LCD_Draw_Point(x+t, y+pos,bcolor);
                    }
                }
            }
        }
    x += 8;
    }
}
void LCD_DispChar(char c, int x, int y)
{
    _LCD_DispChar(c, x, y, _gFontTbl[0].data, _gFontTbl[0].x_size, _gFontTbl[0].y_size, 0xFFFF, 0x0000);
}
/********LCD�ַ�����ӡ����*******/
//��������
//���أ���
//��ע��
int LCD_printf(int x, int y, const char *format,...)
{
    int chars;
    int i;
    __va_list ap;
    char printbuffer[64];
    va_start(ap, format);
    chars = vsprintf(printbuffer, format,ap);
    va_end(ap);
    for(i = 0; i < chars; i++)
    {
        LCD_DispChar(printbuffer[i],x + i*_gFontTbl[0].x_size ,y);
    }
    return chars ;
}


