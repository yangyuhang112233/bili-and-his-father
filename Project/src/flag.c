#include "head.h"

bool barrier=0;//7725���ϱ�־λ
uint16_t countbz7620=0;//7620�ϰ������ظ���
uint8_t juli=0;
uint8_t xiangsuzhi;

void findpoint()
{
    uint16_t ii,jj,count;
    uint16_t avespeed,xinbiao;

    uint32_t suml = 0;
    uint32_t sumh=0;
    count=0;

    target_flag = 0;

if(jioushu==0)
{
      for(ii=0;ii<OV7620_H-2;ii++)	
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
}
else
{
      for(ii=0;ii<OV7620_H-2;ii++)	
  {     
       for(jj=0;jj<OV7620_W-1;jj++)
     {
         if(CCD_Image22[ii][jj]>=door7620)
         {
             sumh = sumh + ii ;
			 suml = suml + jj ;
			 count ++;
         }        
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

     xinbiaoxiangsu=count;//����led��ʾ      
                                                  
     uint8_t xinbiaoqieguo_hh;   
     static bool a=0;
          
    //�������к����ٶȣ������ű���Ϻ��ٶȻ�仯������ı���������Ҳ��仯��ֻ�ܲ��õ�һ�μ�����ű����������
    xinbiaoqieguo_hh=xinbiaoqieguo_h;      
      if(a==0)
    {
      xinbiaoqieguo=0;        
      if(target_h<xinbiaoqieguo_hh)
      {
       xinbiaoqieguo=1;a=1;
      }       
    }
     if(xinbiaoxiangsu<180)a=0;
         
}
  

 
  //�ж��Ƿ���Ҫ����
void findbarrier()
{
uint16_t ii,jj;

barrier=0;

uint32_t sumh = 0;
uint32_t suml = 0;
uint16_t count = 0;   //�ܹ��׵����

uint16_t hbizhang;//����������
    

     
if(jioushu==0)
{    
    
   //����Ӧ���ط�ֵ 
    uint16_t count110=0;
    
    uint32_t zongzhi=0;
    uint8_t  avezhi;
     for(ii=0;ii<60;ii=ii+2)
     {       
        for(jj=110;jj<210;jj=jj+2)
        {
        zongzhi=zongzhi+CCD_Image[ii][jj];
        count110++;
        }
     }
        avezhi=zongzhi/count110;//�����ֵ
      
        xiangsuzhi=avezhi+BIZHANG_DELTA;//����2���

    
     for(ii=43;ii<60;ii++)
     {       
		for(jj=130;jj<190;jj++)
	    {
          if(CCD_Image[ii][jj]>xiangsuzhi&&CCD_Image[ii][jj]<BIZHANG_LIMIT) 
         {       
           sumh = sumh + ii ;
           suml = suml + jj ;					
           count ++;
         }	
        }
     }
     for(ii=0;ii<43;ii++)
     {       
        for(jj=70;jj<250;jj++)
        {
            if(CCD_Image[ii][jj]>xiangsuzhi&&CCD_Image[ii][jj]<BIZHANG_LIMIT) 
            {       
            sumh = sumh + ii ;
            suml = suml + jj ;					
            count ++;
            }	
        }
      }
}
else
{
    
    uint16_t count110=0;
    uint32_t zongzhi=0;
    uint8_t  avezhi;
    for(ii=3;ii<60;ii=ii+2)
    {       
        for(jj=110;jj<210;jj=jj+2)
        {
        zongzhi=zongzhi+CCD_Image22[ii][jj];
        count110++;
        }
    }
    avezhi=zongzhi/count110;//�����ֵ
         
    xiangsuzhi=avezhi+BIZHANG_DELTA;  //����������ͬ�͸��Ĺ����������ע��һ�¾�Ҫ������  ����ʱ��ܺ�
    
     
    for(ii=43;ii<60;ii++)
    {       
        for(jj=130;jj<190;jj++)
        {
            if(CCD_Image22[ii][jj]>xiangsuzhi&&CCD_Image22[ii][jj]<BIZHANG_LIMIT) 
            {       
            sumh = sumh + ii ;
            suml = suml + jj ;					
            count ++;
            }	
        }
    }
     
    for(ii=0;ii<43;ii++)
    {       
        for(jj=70;jj<250;jj++)
        {
            if(CCD_Image22[ii][jj]>xiangsuzhi&&CCD_Image22[ii][jj]<BIZHANG_LIMIT) 
            {       
            sumh = sumh + ii ;
            suml = suml + jj ;					
            count ++;
            }	
        }
    }  
}
           countbz7620=count;//ͨ��led��ʵʱ��ʾ���ظ���         
           barrier_h = sumh /count ;
           barrier_l = suml /count ;
     

       if(count >door_7620&& barrier_l<250&&barrier_l>70)		
{                                            
		barrier= 1;  
        if(target_flag==1)
        {   
            if(target_h>barrier_h)juli=target_h-barrier_h;
            else
            {
            juli=barrier_h-target_h;
            }
                       
            if(juli<28)
            {
            barrier= 0;  
            }           
        }              
}

      if(target_h<stopbizhangh7620)
     {     
         barrier=0;       
     }
     
}            
              
              
              
