#include "key.h"

uint16_t bama[4]={0,0,0,0};//读取拔码开关的四个输入
uint16_t bamaa[4]={0};

uint32_t switch_mode_selection( void )
{
	uint32_t status;
//	return status;
	if(GPIO_ReadBit(HW_GPIOB, 0)==0)    //拨码开关控制  
       {
		   bama[0]=1;
       }      
       	if(GPIO_ReadBit(HW_GPIOB, 1)==0)    //拨码开关控制  
       {
		 bama[1]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 2)==0)    //拨码开关控制  
       {
		bama[2]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 3)==0)    //拨码开关控制  
       {
		 bama[3]=1;
       }   
       status=bama[0]+2* bama[1]+2*2*bama[2]+2*2*2*bama[3];
	   return status;
}

uint32_t switch_mode_data( void )
{
	uint32_t status;
	if(GPIO_ReadBit(HW_GPIOB, 4)==0)    //拨码开关控制  
   {
	   bamaa[0]=1;
   }      
	if(GPIO_ReadBit(HW_GPIOB, 5)==0)    //拨码开关控制  
   {
	 bamaa[1]=1;
   }
	if(GPIO_ReadBit(HW_GPIOB, 6)==0)    //拨码开关控制  
   {
	bamaa[2]=1;
   }
	if(GPIO_ReadBit(HW_GPIOB, 7)==0)    //拨码开关控制  
   {
	 bamaa[3]=1;
   }   
   status=bamaa[0]+2* bamaa[1]+2*2*bamaa[2]+2*2*2*bamaa[3];
   return status;
}
