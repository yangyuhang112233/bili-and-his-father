#ifndef __DRV_LCD_H
#define __DRV_LCD_H

#include <stdint.h>
#include "common.h"

typedef struct
{
    char* mame;
    uint8_t  x_size;
    uint8_t  y_size;
    const char* data;
}font_t;

#define LCD_A0_HIGH GPIO_WriteBit(HW_GPIOE,9,1)
#define LCD_A0_LOW  GPIO_WriteBit(HW_GPIOE,9,0)
#define LCD_RESET_HIGH GPIO_WriteBit(HW_GPIOE,8,1)
#define LCD_RESET_LOW  GPIO_WriteBit(HW_GPIOE,8,0)

#define WHITE            0xFFFF
#define BLACK            0x0000
#define RED              0xF800
#define GREEN            0x07E0
#define BLUE             0x001F 
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

extern bool display_on_LCD;

/*LCD��ʼ������*/
void LCD_Init(void);

/*LCD��ʾ��ɫ����*/
void LCD_Display_BackgroundColor(uint16_t color);

/*LCD���㺯��*/
void LCD_Draw_Point(uint8_t x,uint8_t y,uint16_t color);

/*LCD��ʾCCD���ݺ���*/
void LCD_Draw_CCD(void);

/*LCD���ߺ���*/
void LCD_Sleep(void);

/*LCD���Ѻ���*/
void LCD_WakeUp(void);

/*LCD��ʾͼ����Ϣ����*/
void LCD_DispImg(void);

/*LCD��ӡ�ַ�������*/
int LCD_printf(int x, int y, const char *format,...);

#endif
