#include "head.h"


bool barrier2=0;//7725���ϱ�־λ
uint16_t countbz7620=0;//7620�ϰ������ظ���
 uint8_t juli=0;


   //�ж��Ƿ��ҵ��ű겢�ҳ��ű�ĺ�������
void findpoint()
{
   //  getimage();//ͬʱ�ɼ�7620��7725��ͼ��  �ɸ���Ϊ�ɼ�ͼ���ͬʱ��������
   
     uint16_t ii,jj,count;
     uint16_t avespeed,xinbiao;

     uint32_t suml = 0;
     uint32_t sumh=0;
     count=0;
     
     target_flag = 0;

     //ͼ����Ϣ����
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

	xinbiaoxiangsu=count;

	//�ж��Ƿ�ֹͣ��ͨ����
	stopba=0;
        
                                                  
     //����count1ֵȷ�����й����Ǳ��ϣ�ȷ�����������귧ֵ   �����ű��������ٶ��ж��Ƿ�����ű���� 
	uint8_t xinbiaobizhang_hh;
          
	static bool a=0;
	avespeed=(qd_left_value+qd_right_value)/2;
     
//          
//     if(avespeed<28)
//     {         
//     //���������� ���ٺ���
//     xinbiaobizhang_h=25;//�ű����������   
//     k11=1;
//     }
//     else
//     {
//      //���ٺ���
//      xinbiaobizhang_h=32;//�ű����������   
//      k11=1.15;
//     }
	xinbiaobizhang_h=35;//�ű����������   
	k11=5;
	julican();
          
      //������c 
          
    //�����ű���Ϻ��ٶȻ�仯������ı���������Ҳ��仯��ֻ�ܲ��õ�һ�μ�����ű����������
	if(a==0)
	{
		xinbiaobizhang=0;
		xinbiaoqieguo=0;

		if(turn[count1]==1||turn[count1]==2)
		{
			xinbiaobizhang_hh=can+xinbiaobizhang_h+avespeed/k11;         
			if(target_h<xinbiaobizhang_hh)
			{
				xinbiaobizhang=1;a=1;
			}   
		}  
		else
		{         
			if(target_h<xinbiaoqieguo_h)
			{
				xinbiaoqieguo=1;a=1;
			}
		}

	}
	if(xinbiaoxiangsu<180)
	{
		a=0; 
	}		
//        //֮ǰ״̬�л�����������Ϊ������뷧ֵ�ڱ仯��ͬʱʹ��־λ�仯���þ����Ƶ��������ж�
//         if(target_flag==1)
//        {
//         avespeed=(qd_left_value+qd_right_value)/2;
//         xinbiao=xinbiaobizhang_h+0.9*avespeed;
//     
//         if(target_h<xinbiao)
//         {
//           xinbiaobizhang=1;
//         }
//        }
}
  
 
  //�ж��Ƿ���Ҫ����
 void findbarrier()
 {
   uint16_t ii,jj;
     
    barrier=0;
    barrier2=0;
     
    uint32_t sumh = 0;
    uint32_t suml = 0;
    uint16_t count = 0;   //�ܹ��׵����
     
     
      if(target_h<stopbizhangh7620)
     {
     stopba=1;
     }
     
     
    
     uint16_t hbizhang;//����������
     //7620����
     uint8_t kl=0;
     
      if(qd_right_value+qd_left_value>35)  
     {
     kl=10;
     }        
     else if(qd_right_value+qd_left_value>20)
     {
     kl=5;
     }
     else
     {
     kl=0;
     }
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
   // xiangsuzhi=avezhi+27;
     xiangsuzhi=avezhi+33;//����2���
    
     
     
                    for(ii=43;ii<60;ii++)
     {       
				for(jj=130;jj<190;jj++)
			{
                  if(CCD_Image[ii][jj]>xiangsuzhi&&CCD_Image[ii][jj]<145) 
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
			   
				     if(CCD_Image[ii][jj]>xiangsuzhi&&CCD_Image[ii][jj]<145) 
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
    uint32_t zongzhi=0;//�¸���
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
     
     
    xiangsuzhi=avezhi+33;  //����������ͬ�͸��Ĺ����������ע��һ�¾�Ҫ������  ����ʱ��ܺá���
    
    
     
   //  xiangsuzhi=avezhi+23;//����
     
               for(ii=43;ii<60;ii++)
     {       
				for(jj=130;jj<190;jj++)
			{
                  if(CCD_Image22[ii][jj]>xiangsuzhi&&CCD_Image22[ii][jj]<145) 
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
			   
				     if(CCD_Image22[ii][jj]>xiangsuzhi&&CCD_Image22[ii][jj]<145) 
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
      
         // hbizhang=h7620+(qd_left_value+qd_right_value+10)/2;
      

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
     

//  //���÷ֲ��ַ�ֵ  ��ͼ���ǰ�����÷�ֵ�Ƚ�С ������÷�ֵ�Ƚϴ�

//    //7725����    
//    sumh = 0;
//    suml = 0;
//    count = 0;   //�ܹ��׵���� 
//     uint16_t position;
//     
//     uint8_t k=0;

//     //ͨ����ϸ�۲�ͼ���֣�7725ʼ���������ǵ�λ������㣬���Բ����ⲿ��ͼ��
//       //û��Ҫ��ô�鷳��ֱ���������ξͿ���
//         for(ii=1;ii<26;ii++)
//     {
//				for(jj=27-ii;jj<54+ii;jj++)
//			{
//			       position=80*ii+jj;
//				     if(img[position]==0) 
//						 {       
//                                   sumh = sumh + ii ;
//							       suml = suml + jj ;					
//							         count ++;
//						 }	
//		  }
//      }
// //     if(count>10)barrier2=0;
// //     else{
//  //       count=0;


//              for(ii=26;ii<60;ii++)
//     {
//				for(jj=4;jj<76;jj++)
//			{
//                     position=80*ii+jj;
//				     if(img[position]==0) 
//						 {       
//                                   sumh = sumh + ii ;
//							       suml = suml + jj ;					
//							         count ++;
//                          }
//            }
//     }
//  //    }
//      


//             // ������������긳ֵ
//              barrier2_h = sumh /count ;
//              barrier2_l = suml /count ;
//     
//     
////             juli=(target_l-barrier_l)*(target_l-barrier_l)+(target_h-barrier_h)*(target_h-barrier_h);            
////              if(juli<julifazhi)
////             {
////             barrier= 0;  
////             }
//             
//               count7725=count;//ͨ��led��ʵʱ��ʾ���ظ���

//             //�ж��Ƿ���б���  ���������� 1�����س�����ֵ 2������������趨ֵ���ϰ������С������һ�����룩 3�������������뷶Χ��
//              if(count >50&& barrier2_h>2&& barrier2_l<62&&barrier2_l>22)		
//              {                                             
//				 barrier2= 1;
//			  }	

//            //��ֹ��Ϊ�ű������7725���ϣ���th>90ʱ��ͨ�����ص����ж��ޱ��ϣ���С��90ʱ��ͨ��bh���ж����ű�ƻ����ϰ����С��56ʱֱ������7725����
//     if(barrier2==1)
//{
//      if(target_h<78)
//     {
//         if( barrier2_h<6)
//         {
//         barrier2=0;
//         }       
//     }
//}

//      if(target_h<stopbizhangh7725)
//     {
//         
//         barrier2=0;       
//     }
     

}            
              
              
              
              






  
