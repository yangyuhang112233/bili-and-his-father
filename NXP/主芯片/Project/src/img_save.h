#ifndef _IMG_SAVE_H_
#define _IMG_SAVE_H_

#include "common.h"
#include "stdint.h"
#include "ff.h"
/****************************************************************************
    同济大学飞思卡尔实验室
	K60图像存储
	修改时间：2015-6-25
	本程序只供学习使用，未经作者许可，不得用于其它任何用途
****************************************************************************/	
#pragma pack(1)
typedef struct tagBITMAPFILEHEADER 
{ 
	WORD bfType;   
	DWORD bfSize; 
	WORD bfReserved1; 
	WORD bfReserved2; 
	DWORD bfOffBits;
} BMPHEADER;

typedef struct tagBITMAPINFOHEADER
{
	DWORD biSize; 
	LONG biWidth; 
	LONG biHeight; 
	WORD biPlanes; 
	WORD biBitCount; 
	DWORD biCompression; 
	DWORD biSizeImage; 
	LONG biXPelsPerMeter; 
	LONG biYPelsPerMeter; 
	DWORD biClrUsed; 
	DWORD biClrImportant;
} BMPINFOHEADER;

typedef struct tagBITMAPRGBQUAD
{ 
	BYTE rgbBlue;
    BYTE rgbGreen;
    BYTE rgbRed;
    BYTE alpha;
} BMPQUAD;

/*打印错误信息*/
void ERROR_TRACE(FRESULT rc);

/*挂载文件系统*/
void Fatfs_Init(void);

/*文件系统打印字符串*/
void FATFS_printf(const char *format,...);

/*输出压缩后的图像信息*/
void Save_Imgrar(void);

/*正常保存图像及相关数据*/
void Save_Img(void);

/*保存BMP图像相关信息*/
void WriteHeader(FIL* file);
void WriteBMPInfo(FIL* file);
void WriteBMPPalette(FIL* file);

#endif
