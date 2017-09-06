#include "key.h"

uint16_t bama[4]={0,0,0,0};//��ȡ���뿪�ص��ĸ�����
uint16_t bamaa[4]={0};

uint32_t switch_mode_selection( void )
{
	uint32_t status;
//	return status;
	if(GPIO_ReadBit(HW_GPIOB, 0)==0)    //���뿪�ؿ���  
       {
		   bama[0]=1;
       }      
       	if(GPIO_ReadBit(HW_GPIOB, 1)==0)    //���뿪�ؿ���  
       {
		 bama[1]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 2)==0)    //���뿪�ؿ���  
       {
		bama[2]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 3)==0)    //���뿪�ؿ���  
       {
		 bama[3]=1;
       }   
       status=bama[0]+2* bama[1]+2*2*bama[2]+2*2*2*bama[3];
	   return status;
}

uint32_t switch_mode_data( void )
{
	uint32_t status;
	if(GPIO_ReadBit(HW_GPIOB, 4)==0)    //���뿪�ؿ���  
   {
	   bamaa[0]=1;
   }      
	if(GPIO_ReadBit(HW_GPIOB, 5)==0)    //���뿪�ؿ���  
   {
	 bamaa[1]=1;
   }
	if(GPIO_ReadBit(HW_GPIOB, 6)==0)    //���뿪�ؿ���  
   {
	bamaa[2]=1;
   }
	if(GPIO_ReadBit(HW_GPIOB, 7)==0)    //���뿪�ؿ���  
   {
	 bamaa[3]=1;
   }   
   status=bamaa[0]+2* bamaa[1]+2*2*bamaa[2]+2*2*2*bamaa[3];
   return status;
}
