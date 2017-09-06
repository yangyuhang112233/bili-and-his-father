#ifndef _IMG_SAVE_H_
#define _IMG_SAVE_H_

#include "common.h"
#include "stdint.h"
#include "ff.h"
/****************************************************************************
    ͬ�ô�ѧ��˼����ʵ����
	K60ͼ��洢
	�޸�ʱ�䣺2015-6-25
	������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
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

/*��ӡ������Ϣ*/
void ERROR_TRACE(FRESULT rc);

/*�����ļ�ϵͳ*/
void Fatfs_Init(void);

/*�ļ�ϵͳ��ӡ�ַ���*/
void FATFS_printf(const char *format,...);

/*���ѹ�����ͼ����Ϣ*/
void Save_Imgrar(void);

/*��������ͼ���������*/
void Save_Img(void);

/*����BMPͼ�������Ϣ*/
void WriteHeader(FIL* file);
void WriteBMPInfo(FIL* file);
void WriteBMPPalette(FIL* file);

#endif
