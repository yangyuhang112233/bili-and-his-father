#include "img_save.h"
#include "ov7725_Init.h"
#include "common.h"
#include "gpio.h"
#include "ff.h"
#include "stdio.h"
#include "Drv_LCD.h"
#include "sd.h"
#include <stdarg.h>

volatile uint32_t file_name;
FRESULT rc;
FATFS fs_sd;
FATFS *fs=&fs_sd;;
FIL fil;
UINT WRBytes;

/****************************************************************
* 函数名称:void ERROR_TRACE(FRESULT rc)
* 说明：LCD打印错误信息
* 参变量：无   
* 返回值类型：
* 修改时间：2015-6-25
****************************************************************/
void ERROR_TRACE(FRESULT rc)
{   
    if(rc != 0)
    {
        GPIO_SetBit(HW_GPIOD,6);
        LCD_printf(10,116,"fatfs error:%d\r\n", rc);
    }
}
/****************************************************************
* 函数名称:void Fatfs_Init(void) 
* 说明：挂载文件系统
* 参变量：无   
* 返回值类型：0：挂载正常  1：挂载失败
* 修改时间：2015-6-25
****************************************************************/
void Fatfs_Init(void)
{
    uint32_t i=SD_QuickInit(25*1000*1000);
    if(i!=0)
    {
        LCD_printf(15,116,"SDCard no found!");
        //GPIO_SetBit(HW_GPIOD,6);
    }
    //初始化文件名称
    file_name=0;
     /* 挂载文件系统 rc=0挂载正常 */
    rc = f_mount(fs, "0:", 0);
    ERROR_TRACE(rc);
}
/****************************************************************
* 函数名称:void FATFS_printf(const char *format,...) 
* 说明：外部调用用以保存必要的数据
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-27
****************************************************************/
void FATFS_printf(const char *format,...)
{
    char filename[15];//数据路径名称
    sprintf(filename,"0:/%d.txt",file_name++);
    //按照给定格式写入数组
    int chars;
    __va_list ap;
    char printbuffer[128];
    va_start(ap, format);
    chars = vsprintf(printbuffer,format,ap);
    va_end(ap);
    //fatfs文件操作
    rc=f_open(&fil,filename,FA_WRITE | FA_CREATE_ALWAYS);
    ERROR_TRACE(rc);
    rc=f_write(&fil,(uint8_t*)printbuffer,chars,&WRBytes);
    ERROR_TRACE(rc);
    rc=f_close(&fil);
    ERROR_TRACE(rc);
}
/****************************************************************
* 函数名称:void Save_Img(void); 
* 说明：外部调用用以保存图像数据
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-25
****************************************************************/
void Save_Imgrar(void)
{
    uint16_t i=0;
    //设置缓冲区并写入数据
    uint8_t temp[160];
    uint8_t *q;
    for(;i<80;i++)
        temp[i]=CCDBufferPool[i];
    q=(uint8_t *)center;
    for(;i<160;i++)
        temp[i]=*(q++);
    //文件系统操作
    char filename[15];
    sprintf(filename,"0:/RAR%d.bmp",file_name++);
    rc=f_open(&fil,filename,FA_WRITE | FA_CREATE_ALWAYS);
    ERROR_TRACE(rc);
    rc=f_write(&fil,(uint8_t *)temp,160,&WRBytes);
    ERROR_TRACE(rc);
    rc=f_close(&fil);
}
/****************************************************************
* 函数名称:void Save_Img(void); 
* 说明：外部调用用以保存图像数据
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-25
****************************************************************/
void Save_Img(void)
{
    int i,j;
    uint8_t colour[2] = {0xfe, 0x00};
    char filename[15];//图像路径名称
    sprintf(filename,"0:/%d.bmp",file_name++);
    rc=f_open(&fil,filename,FA_WRITE | FA_CREATE_ALWAYS);
    ERROR_TRACE(rc);
    WriteHeader(&fil);
    WriteBMPInfo(&fil);
    WriteBMPPalette(&fil);
    for(i=0;i<OV7725_W;i++)
	{
		for(j=OV7725_H-1;j>=0;j--)
		{
            rc=f_write(&fil,&colour[*(img+j*OV7725_H+i)],100,&WRBytes);
            ERROR_TRACE(rc);
        }
    }
    ERROR_TRACE(rc);
    rc=f_close(&fil);
    ERROR_TRACE(rc);
}


/****************************************************************
* 函数名称:void WriteHeader(FIL* file)
* 说明：保存BMP图像的头信息
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-25
****************************************************************/
void WriteHeader(FIL* file)
{
	UINT WRBytes;
	uint8_t BMP_header[14];	
	BMPHEADER* bmph;

	bmph=(BMPHEADER*)BMP_header;
	bmph->bfType=0x4d42;//bmp文件
	bmph->bfSize=0x16f6;//文件大小,待定
	bmph->bfReserved1=0;//保留,必须设置为0
	bmph->bfReserved2=0;//保留,必须设置为0
	bmph->bfOffBits=0x436;//从文件头到位图数据所需偏移字节
	f_write(file,BMP_header,14,&WRBytes);
}
/****************************************************************
* 函数名称:void WriteBMPInfo(FIL* file)
* 说明：保存BMP文件的位图信息
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-25
****************************************************************/
void WriteBMPInfo(FIL* file)
{
 	UINT WRBytes;
	uint8_t BMP_info[40];	
	BMPINFOHEADER* bmpi;

	bmpi=(BMPINFOHEADER*)BMP_info;
	bmpi->biSize=40;//位图信息头大小
	bmpi->biWidth=80;//图像宽度
	bmpi->biHeight=60;//图像高度
	bmpi->biPlanes=1;
	bmpi->biBitCount=8;
	bmpi->biCompression=0;
	bmpi->biSizeImage=0x12c0;
	bmpi->biXPelsPerMeter=0x1274;
	bmpi->biYPelsPerMeter=0x1274;
	bmpi->biClrUsed=0;
	bmpi->biClrImportant=0;
	f_write(file,BMP_info,40,&WRBytes);
}
/****************************************************************
* 函数名称:void WriteBMPPalette(FIL* file)
* 说明：保存BMP文件的颜色板
* 参变量：无   
* 返回值类型：无
* 修改时间：2015-6-25
****************************************************************/
void WriteBMPPalette(FIL* file)
{
    UINT WRBytes;
    uint8_t BMP_quad[4];	
    BMPQUAD* bmpq;
	bmpq=(BMPQUAD*)BMP_quad;
    for(uint16_t i=0;i<256;i++)
    {
        bmpq->rgbBlue=i;
        bmpq->rgbGreen=i;
        bmpq->rgbRed=i;
        bmpq->alpha=0;
        rc=f_write(file,BMP_quad,4,&WRBytes);
        ERROR_TRACE(rc);
    }   
}





