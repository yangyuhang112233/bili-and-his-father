#include "head.h"

bool barrier=0;//7725���ϱ�־λ
uint16_t countbz7620=0;//7620�ϰ������ظ���
uint8_t juli=0;

void findpoint()
{
    uint16_t ii,jj,count;
    uint16_t avespeed,xinbiao;

    uint32_t suml = 0;
    uint32_t sumh=0;
    count=0;

    target_flag = 0;

      for(ii=0;ii<OV7620_H-4;ii++)	
  {     
       for(jj=0;jj<OV7620_W-1;jj++)
     {
         if(CCD_Image[ii][jj]>=door7620)
         {
             sumh = sumh + ii ;
			 suml = suml + jj ;
			 count ++;
         }         
     }
  }   


     //�ж��Ƿ��ҵ��ű�
          if(count>2)
          {
              target_l=suml /count ;
              target_h=sumh /count ;
              target_flag = 1;            
          }


}
  
         
              
              
