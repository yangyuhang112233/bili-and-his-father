#include "head.h"

 uint16_t deviation=0;//偏差

//没有找到信标时的动作
void lookfor()
{
    //只在这里调用从机
    
     //信标避障后，设置大转弯打角       
   if(forestate==3)
{    
   if(GPIO_ReadBit(HW_GPIOC, 0)==1)
   {
   anglex=angleright;
   }
   else
   {
   anglex=angleleft;    
   }      
}    
  else   
   { 
     //如果之前的状态为1（避障），那么肯定是从状态2（gothere）切换到了状态1，又切换到了状态0（lookfor）。
     //那么是因为避障转角而引起的看不到信标，则需要让打角反转
    if(forestate!=1)
  {
          if(anglex>anglemid)
        {  
        anglex=angleleft;    
        }      
          else
        {
        anglex=angleright;
        }     
  } 
else 
      {   
           if(anglex>anglemid)
           {  
           anglex=angleright;              
           }      
           else
           {
            anglex=angleleft;             
           }           
      }      
   }
     
      speedx=speeddazhuan;
   
}
  
 //进行避障
void bizhang()
  {

   if(barrier==1)  
 {          
  if(barrier_l>38) 
  {
      if(anglex<hide_left)
      {      
         anglex=hide_left;         
      }
  }      
  else
  {
        if(anglex>hide_right)
      {            
         anglex=hide_right;
      }         
  }
 }  
  speedx=speedbizhang;
}
  

void gothere()
{
    piancha();
                
    if(target_l<cammid)
    {
    anglex=anglemid+anglek*(target_l-(cammid-deviation));
    }
    else
    {
    anglex=anglemid+anglek*(target_l-(cammid+deviation));
    }  

      //若舵机打角小，迅速加速减速
     if(anglex>acc_right&&anglex<acc_left)
     {                                     
        //控制加速减速过程 
        if(target_h>acc_stop+avespeed/k12) 
        {
            speedx=speedjiasu;          
        }	

      //前往信标位置的减速段    如果速度很慢，则改变设定速度为加速        
          else
          {                
              if(speedx!=speedxinjiansu&&speedx!=speedxinjia)
              {      
                if(avespeed>18)
                {
                  speedx=speedxinjiansu;     
                }
                else
                {
                  speedx=speedxinjia;   
                }             
              }
          }
      }
     
      //若舵机打角大，在低速下调整正方向
     else
     {
         if(avespeed>25)speedx=speedzhuanwan;
         else
             speedx=speedzhuanwan2;
     }

}

void gothere1()
{
    piancha();
      
    if(target_l<cammid)
    {
    anglex=anglemid+anglek*(target_l-(cammid-deviation));
    }
    else
    {
    anglex=anglemid+anglek*(target_l-(cammid+deviation));
    }  
     
   //防止信标避障延时结束后又进行信标避障
   //之所以会忽然左转，是因为两次进入信标避障，第二次进入时turn[count1]的值变为3了，与之前的值不同，打角计算不同
   if(target_h<16) 
   {    
        if(turn[count1]==4)
        {
            anglex=anglemid-1;
               if(target_h<16) 
           {     
            anglex=anglemid-6;
           }
        }
         
        if(turn[count1]==3)
        {
          anglex=anglemid+1;
          if(target_h<16) 
          {     
           anglex=anglemid+6;
          }
        }
   }
    speedx=speedxinbi1;
}
  
void piancha()
{

      uint16_t a,b;
    //a调小，则靠近信标时偏差变小；
      if(target_h<17)
      {
      a=234;b=14907;   //端点值要对应，否则会突变
      }
      else if(target_h<43)
      { 
      a=185;b=14477;  
      }
      else if(target_h<70)
      {
      a=122;b=11864;  
      }
      else 
      {
      a=115;b=11374;
      }
      //可以乘一个比例系数，在乘比例系数的情况下满足了线性增大，同时满足曲线依然相连接    
      deviation=pianchak*(b-a*target_h)/100;
}
 
