#include "head.h"

 //两个参数分别为舵机打角和速度，运动状态全部在这里改变，此函数中根据舵机打角自动设置差速
  //最佳情况是只传入打角，自动根据打角设置极限速度
  //不传入参数，根据全局变量使用函数，改变运动状态时调用此函数
   
 void move()//打角，速度作为全局变量引用
{        
      //舵机打角控制
      Servo_Control();
     
    static bool ab=0;
    
       //防止速度过低
       if(target_h<50)
     {
            if(qd_left_value+qd_right_value<24)
          {
          speedx=15;
          }
      }
	    uint16_t leftspeed,rightspeed;//左右轮设定速度
    uint16_t anglec;//根据角度选择差速
	        rightspeed=speedx;
      leftspeed=speedx; 
//      //根据舵机打角设置左右两个轮子的转速，并调用pid实现左右轮转速
//    
//    //float proportion[5]={1.41,1.36,1.28,1.24,1.19};//差速比
//     float proportion[5]={1.4,1.15,1,1,1};//差速比例
//     float bili=0;//差速比例
//     
//    //差速可能导致在滑的场地打滑
//     

//     
//  
//    
//    //本来没有差速，效果也还好
//             if(anglenow>anglemid-51&&anglenow<anglemid+51) 
//      {
//        rightspeed=speedx;
//        leftspeed=speedx;         
//      }        
//      else
//      {        
//       anglec=anglenow/10;
//                 
//        if(anglec<46)  //右转
//        {
//         anglec=anglec-41; 
//         rightspeed=speedx;
//          bili=proportion[anglec];           
//         leftspeed=bili*speedx;       
//        }
//        if(anglec>55)           //左转
//         {
//          anglec=60-anglec; 
//           bili=proportion[anglec];   
//          rightspeed=bili*speedx; 
//          leftspeed=speedx;          
//         }
//       } 
//       if(state==4)
//       {
//            if(anglec<46)  //右转
//          {
//          
//         rightspeed=speedx;
//                  
//         leftspeed=1.7*speedx;       
//        }
//        if(anglec>55)           //左转
//         {
//          rightspeed=1.7*speedx; 
//          leftspeed=speedx;          
//         }           
//       }
//      
       
       //注意一个问题：在state==0时可能进入一次判断后就不进入判断，电机输出占空比会固定不变，所以要加一个判断
//        if(state==0)
//        {
//            if(ab==0)
//            {
//                if(forestate==3||forestate==4)
//              {
//                 if(leftspeed>rightspeed)
//                {
//                  Motor_Control(30,3);
//                }
//                 else
//                { 
//                  Motor_Control(3,30);      
//                }     
//               }
//            else
//            {
//                 if(leftspeed>rightspeed)
//                {
//                  Motor_Control(18,16);
//                }
//                 else
//                {
//                  Motor_Control(16,18);     
//                 }
//             }
           // ab=1;
//         }
        
////       }
//       if(state==0&&forestate==4&&ab==0)
//       {
//           if(anglex==angleright)
//           {
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,8000 );
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 1000);  
//           }
//           
//          if(anglex==angleleft)
//           {
//           
//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,1000);  
//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 8000 ); 
//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
//           }
//           ab=1;
//       }
//        else if(state!=0)
//        {
//         Motor_Control(leftspeed,rightspeed);//上面是速度选择，这里是速度实现
//        ab=0;
//        }

//根据count1的值加一 来判断进行一次大转 大转的次数限定好
//if forecount11=count1
static uint8_t count123;


            
            //  if(count123!=count1)
       if(state==0&&laststate==3)
       {
           count123=count1;  
//		   if(count123==5)
//		   {
//			   Motor_Control(10,10);
//		   }
			if(count123==20)
			{
				anglex=SERVO_MIDDLE-40;
				
					Motor_Control(20,18);
					DelayMs(2);
			}
			else
			{

				if(anglex==angleleft)
				{
				Motor_Control(20,25);		//20，25 19s参数
				//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
				//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,4000);  
				//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 5000 ); 
				//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
				}		   
				else 
				{
					Motor_Control(30,20);	//30，20	19参数
					//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
					//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,5000);
					//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 3000 ); 
					//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);  
				}
			}
           
        
//          else
//          {
//              
//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,3000 );
//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);  
//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 3000 ); 
//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0); 
//          // stopmove();
//          }
       }
        else 
        {
         Motor_Control(leftspeed,rightspeed);//上面是速度选择，这里是速度实现       
        }


        
//               if(state==0)
//{
//       if(leftspeed>rightspeed)
//       {
//        Motor_Control(18,1);
//       }
//       else
//       {
//       Motor_Control(1,18);
//       
//       }         
//}
     
      
       //速度控制只在这里和下边实现
      //  Motor_Control(leftspeed,rightspeed);//上面是速度选择，这里是速度实现
     
       
       //普通避障设置延时
        if(state==1)
       {           
           DelayMs(20);
           if(qd_left_value +qd_right_value<35) DelayMs(10);
       } 

      
          
       //如果是信标避障状态那么设置一定延时，延时内方向速度不变，使小车经过并熄灭信标
    
       if(state==3)
       {
                for(int co1=0;co1<3;co1++)
            {              
             Motor_Control(leftspeed,rightspeed);
             DelayMs(delay2);
            }     
       }  
       //最好还是通过设置让信标灯处在图像的某一位置
              if(state==4)
       {
                for(int co1=0;co1<3;co1++)
            {              
             Motor_Control(leftspeed,rightspeed);
             DelayMs(delay2);
            }     
       }
       
//       if(count1==5)    
//       {DelayMs(delay2);}
       
}
  
  