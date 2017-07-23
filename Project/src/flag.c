#include "head.h"


bool barrier2=0;//7725避障标志位
uint16_t countbz7620=0;//7620障碍物像素个数
 uint8_t juli=0;


   //判断是否找到信标并找出信标的横纵坐标
void findpoint()
{
   //  getimage();//同时采集7620和7725的图像  可更改为采集图像的同时处理数据
   
     uint16_t ii,jj,count;
     uint16_t avespeed,xinbiao;

     uint32_t suml = 0;
     uint32_t sumh=0;
     count=0;
     
     target_flag = 0;

     //图像信息处理
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

	//判断是否找到信标
	if(count>2)
	{
		target_l=suml /count ;
		target_h=sumh /count ;
		target_flag = 1;            
	}

	xinbiaoxiangsu=count;

	//判断是否停止普通避障
	stopba=0;
        
                                                  
     //根据count1值确定是切过还是避障，确定避障行坐标阀值   根据信标横坐标和速度判断是否进行信标避障 
	uint8_t xinbiaobizhang_hh;
          
	static bool a=0;
	avespeed=(qd_left_value+qd_right_value)/2;
     
//          
//     if(avespeed<28)
//     {         
//     //避障行坐标 低速好用
//     xinbiaobizhang_h=25;//信标避障行坐标   
//     k11=1;
//     }
//     else
//     {
//      //快速好用
//      xinbiaobizhang_h=32;//信标避障行坐标   
//      k11=1.15;
//     }
	xinbiaobizhang_h=35;//信标避障行坐标   
	k11=5;
	julican();
          
      //调常数c 
          
    //进入信标避障后速度会变化，计算的避障行坐标也会变化。只能采用第一次计算的信标避障行坐标
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
//        //之前状态切换有问题是因为这里距离阀值在变化，同时使标志位变化，让经过灯的数量误判断
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
  
 
  //判断是否需要避障
 void findbarrier()
 {
   uint16_t ii,jj;
     
    barrier=0;
    barrier2=0;
     
    uint32_t sumh = 0;
    uint32_t suml = 0;
    uint16_t count = 0;   //总共白点个数
     
     
      if(target_h<stopbizhangh7620)
     {
     stopba=1;
     }
     
     
    
     uint16_t hbizhang;//避障行坐标
     //7620避障
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
    
   //自适应像素阀值 
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
    avezhi=zongzhi/count110;//计算均值
   // xiangsuzhi=avezhi+27;
     xiangsuzhi=avezhi+33;//下午2点半
    
     
     
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
    uint32_t zongzhi=0;//新更改
    uint8_t  avezhi;
     for(ii=3;ii<60;ii=ii+2)
     {       
				for(jj=110;jj<210;jj=jj+2)
			{
                zongzhi=zongzhi+CCD_Image22[ii][jj];
                count110++;
            }
     }
    avezhi=zongzhi/count110;//计算均值
     
     
    xiangsuzhi=avezhi+33;  //光线条件不同就更改过这个参数，注意一下就要改两个  下午时候很好、、
    
    
     
   //  xiangsuzhi=avezhi+23;//晚上
     
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
           countbz7620=count;//通过led来实时显示像素个数
          
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
     

//  //设置分部分阀值  在图像的前段设置阀值比较小 后端设置阀值比较大

//    //7725避障    
//    sumh = 0;
//    suml = 0;
//    count = 0;   //总共白点个数 
//     uint16_t position;
//     
//     uint8_t k=0;

//     //通过仔细观察图像发现，7725始终在两个角的位置有噪点，所以不看这部分图像
//       //没必要这么麻烦，直接两个矩形就可以
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


//             // 行坐标和列坐标赋值
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
//               count7725=count;//通过led来实时显示像素个数

//             //判断是否进行避障  避障条件： 1、像素超过阀值 2、行坐标高于设定值（障碍物距离小车进入一定距离） 3、列坐标在中央范围内
//              if(count >50&& barrier2_h>2&& barrier2_l<62&&barrier2_l>22)		
//              {                                             
//				 barrier2= 1;
//			  }	

//            //防止因为信标灯引起7725避障，在th>90时，通过像素点来判断无避障，在小于90时，通过bh来判断是信标灯还是障碍物。在小于56时直接屏蔽7725避障
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
              
              
              
              






  
