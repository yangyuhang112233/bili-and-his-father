#include "head.h"

int main(void)
{  
    jioushu=1;//用于7620和7725两幅图片的轮流采集和处理 
    
    getready();
    
    firstimage();
    duqubama();
    
  
    while(1)
    {   
        
		QD_value();
              
        
       //这里根据count1的值来重写速度值，实现速度的路径规划 
       
       //speedset();//根据count1值不同设置不同的速度
        
	   GPIO_ToggleBit(HW_GPIOA, 15); //小灯闪烁表示进入循环
       startimage();  //开始采集图像的配置 
        
        
        //sending3(); 
        //一：根据图像设定不同标志位 
             
	    findpoint();//判断是否找到信标，并更新信标位置和标志位,判断是否屏蔽普捅避障，是否开启信标避障
        
       //if(x[count1]==1){}//设置具体哪一个灯开避障
       // findbarrier();//判断前方是否需要普通避障
        
         barrier2=0;barrier=0;//关闭避障
        
        //二:根据标志位判断相应的状态 
//避障优先        设定如果一直处于避障的状态，避障打角不变  若一直避障大转
//                if(barrier2==1||barrier==1)
//                {state=1;}
//                else
//                {}
      
       if(target_flag==0)
       {
           state=0;
       }
        else
        {
            if(xinbiaoqieguo==1)
            {
            state=3;
            }
            else if(xinbiaobizhang==1)
            {
             state=4;
            }
            else 
            {
                if(barrier2==1||barrier==1)
                {
                    if(stopba==1)state=2;
                    else
                    {
                        state=1;
                    }
                }
                else
               {
                state=2;
               }
            }
        
        }
    
        
   //三：根据状态的不同执行相应的操作
        
        switch(state)
              {
                case 0://找不到信标，转一转来找到信标
//                lookfor();
                break;
                
                case 1://找到信标的状态，遇到前方有障碍物，进行避障
               // bizhang();
               
                break;
                
                case 2://找到信标的状态，前方没有障碍物，前往信标位置
                gothere();   
                break;
                
                case 3://靠近信标进行信标避障 或者进行边缘切过，则继续gothere 可以通过设置两个case来实现，使用不同的避障行坐标   
                             
                gothere1();//信标切过          
                break;
            
                
                case 4:
                pointbizhang();   //信标避障   
                break;
              
               
             default:
             break;     
              }
              
          
              
              
      //四：舵机打角和电机速度改变
              
//              if(target_flag==1)
//              {
//              kaiqi=1;
//              }
//                  
//              if(kaiqi==1)
//              {
//              }
              
               move();
//             
              
              
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,2500 );
//        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);     
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 2500 ); 
//        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
//		
      //五：判断经过了一个灯   等待采集图像完成  储存前一个状态的变量
        pass();                      
       
              
       endimage();  
              
       prestate();   
              
        //Printf();

              

      
      bamaswitch();//拔码开关函数   
    }   
}

