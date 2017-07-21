#include "head.h"

            
uint8_t bamakaiguan=0;//拔码开关状态
 uint16_t xinbiaoxiangsu;//信标像素个数
uint16_t xinbiao0[10];//过去的信标像素值
uint8_t xinbiaobiaozhi=0;//判定是否信标像素个数超过400
uint8_t xidengshu=0;//熄过得灯的个数

 void speedset()
 {
     //这里可以设置任意参数，不只速度
     
     switch(count1)
     {
//         
//               case 1:
//    speedjiasu=     15;           //远离信标 直线加速  
//    speedxinjiansu= 10;           //靠近信标 进行减速   
//    speedxinjia=    10;          //靠近信标 速度太慢 而加速 
//             break;
//         
//       case 2:
//    speedjiasu=     27;           //远离信标 直线加速  
//    speedxinjiansu= 16;           //靠近信标 进行减速   
//    speedxinjia=    25;          //靠近信标 速度太慢 而加速  
//         break;
          
         
         
         
//         case 0:
//             //稳速情况
////             speedjiasu=     27;            //远离信标 直线加速
//// speedxinjiansu= 20;        //靠近信标 进行减速
//// speedxinjia=    23;          //靠近信标 速度太慢 而加速 
//         
//         
// speedjiasu=     33;            //远离信标 直线加速
// speedxinjiansu= 21;        //靠近信标 进行减速
// speedxinjia=    26;          //靠近信标 速度太慢 而加速
//         
//         
//// speedzhuanwan=  15;        //寻找信标转弯速度

//// speeddazhuan=   20;         //找不到信标大转弯速度
//// speedbizhang=   6;          //避障减速
//// speedxinbi=     7;            //信标避障减速
//// speedxinbijia=  23;          //信标避障时太慢，则加速
//       //可以设置pi参数变量，在这里改变
//         
//             break;
//         

////   
////             break;
////        case 3:
////    speedjiasu=     27;           //远离信标 直线加速  
////    speedxinjiansu= 16;           //靠近信标 进行减速   
////    speedxinjia=    25;          //靠近信标 速度太慢 而加速  
////       
////             break;
//         
//                case 2:   //稳速情况
//    speedjiasu=     18;           //远离信标 直线加速  
//    speedxinjiansu= 12;           //靠近信标 进行减速   
//    speedxinjia=    12;          //靠近信标 速度太慢 而加速  
//   
//             break;
//        case 3:
//    speedjiasu=     24;           //远离信标 直线加速  
//    speedxinjiansu= 16;           //靠近信标 进行减速   
//    speedxinjia=    22;          //靠近信标 速度太慢 而加速  
//       
//             break;
//        
//               case 4:
//    speedjiasu=     33;           //远离信标 直线加速  
//    speedxinjiansu= 22;           //靠近信标 进行减速   
//    speedxinjia=    27;          //靠近信标 速度太慢 而加速  
//       
//             break;
//               
//                 case 6://稳速情况
//    speedjiasu=     24;           //远离信标 直线加速  
//    speedxinjiansu= 17;           //靠近信标 进行减速   
//    speedxinjia=    22;          //靠近信标 速度太慢 而加速  
//         
//             break;
//        
//        
////         case 6:
////    speedjiasu=     28;           //远离信标 直线加速  
////    speedxinjiansu= 21;           //靠近信标 进行减速   
////    speedxinjia=    25;          //靠近信标 速度太慢 而加速  
////         
////             break;
//        
         default:
             break;
     }
     
 
 }
 
//count1为0，则正前往第一个灯；为1，则处于 进入第一个灯的信标避障 和  进入第二个灯的信标避障之间。
void pass()
{
         //进入信标避障时加1  
       
    //因为速度比较快，靠近有的灯有的时候抖得厉害，没有进入信标就熄灭了灯进入下一个找灯了
   //调试方法，看经过了几个避障状态，记录下来，最后停车后通过led显示
//     if(forestate!=3&&state==3)
//      {   
//          count1++;        
//      }
//         if(forestate==2&&state==0)
//      {   
//          count1++;        
//      }
    
      //聪明的做法是在这里直接处理像素值和行坐标这些原始量，更加灵活
if(xinbiaobiaozhi==0)
   {
      if(xinbiaoxiangsu>350&&target_h<23)
      {
      xinbiaobiaozhi=1;
      
      }
   }
else
   {
     if(xinbiaoxiangsu<180)
     {
      count1++;
       xidengshu++;
      xinbiaobiaozhi=0;
     }         
   }
  

  
      if(count1==10)count1=0;
   
   
         //停止运动
      if(xidengshu==20)   
      {        
       stopmove();
      }  
   
   
   
   
   
}
      //在信标避障的临界点会有毛刺，信标的行坐标会有微小跳动，则信标状态会有跳动，造成计算了两次信标避障，算成了两个灯
      //对于毛刺问题，可以根据前后4个状态的优势状态（数量比较多的状态）来判定状态 
//        if(xinbiao0[0]<400&&xinbiaoxiangsu>400)
//      {   
//          count1++;        
//      }
      
      
      
      
      
      
      



      
//      if(state0[0]==3&&state0[1]==3&&state0[2]==3&&state0[3]!=3&&state0[4]!=3)
//      {
//      count1++;    
//      }
     
      //通过像素值变化来判断是否经过灯
//      if(xinbiao-xinbiao0[0]>50||xinbiao0[0]-xinbiao<50)
//      {
//      count1++; 
//      }
      
      

      
      
      //可以作为一个模板，首先状态改变，然后根据前状态和先状态的值来判断经过了灯
      //脱离信标避障时加1
//      if(forestate==3&&state!=3)
//      {
//     
//      
//      }
                       

  //储存前一个状态的变量
void prestate()
{   
    jishuwei++;
    if(jishuwei>200)
    {
    jishuwei=0;
    }
    
    
 forestate=state;
 foreangle=anglex;

    
    //还可以在设置一个数组，储存的数字是过去经过的变化的状态
     //存储过去的状态 0为刚刚的状态 
    
   for(uint8_t i=4;i>0;i--)
    {
    count11[i]=count11[i-1];
    }
    count11[0]=count1;

    
    for(uint8_t i=9;i>0;i--)
    {
    state0[i]=state0[i-1];
    }
    state0[0]=state;
    
    
       for(uint8_t i=9;i>0;i--)
    {
    xinbiao0[i]=xinbiao0[i-1];
    }
    xinbiao0[0]=xinbiaoxiangsu;
}


//   //根据7620图像判断小车是否不动，如果不动就倒车   使用超声波判断是否撞车！！！
//void daoche()
//{
//    
//   static uint8_t CCD_Image33[100][100];//图像数据,用于判断小车是否停住
//   uint32_t countzong=0;
//   static uint8_t i=0;//用于判断经过了几次循环
//    
//    i++;
//    
//    if(i==20)
//{
//         for(uint16_t ii=0;ii<80;ii++)	
//      {     
//          for(uint16_t jj=0;jj<80;jj++)
//        {
//         CCD_Image33[ii][jj]= CCD_Image[ii+100][jj];  //可以通过隔行取点的方法   
//        }
//      }         
//}
//     //每隔40个循环，计算40个循环前的图像与现在图像的差异大小
//    if(i==40)
//{
//       i=0;
//       countzong=0;
//    
//       //计算两幅图像的差异 
//          for(uint16_t ii=0;ii<80;ii++)	
//      {     
//          for(uint16_t jj=0;jj<80;jj++)
//        {
//         countzong=countzong+CCD_Image33[ii][jj]-CCD_Image[ii+100][jj];      
//        }
//      }  
//      
//      //图像差异过小，则倒车
////    if(countzong<100000)
////    {
////        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
////        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,9000);
////    	  FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
////        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 9000 );
////        DelayMs(2000);
////    }
//         
//}
//    LCD_printf(10,5,"co:   ");
//    LCD_printf(10,5,"co:%d",countzong);

//}
