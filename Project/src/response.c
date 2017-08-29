#include "head.h"
#include "rtp.h"

 uint16_t deviation=0;//偏差

//没有找到信标时的动作
void lookfor()
{
    //只在这里调用从机
    
     //信标避障后，设置大转弯打角       
  
	
	
	if (route_selection_switch)
	{	
		   if(forestate==3)
		{  
			if(turn_route[count1]==0)
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
			if(forestate==0)
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
				if(beacon_right_flag==BEACON_RIGHT_FIND)
				{
					anglex=angleright;
				}
				else
				{
					anglex=angleleft;    
				}
				
			} 
		}
	
	}
	else
	{
		if(beacon_right_flag==BEACON_RIGHT_FIND)
		{
			anglex=angleright;
		}
		else
		{
			anglex=angleleft;    
		} 

		if(forestate==0)
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
				
	}
      speedx=speeddazhuan;
   
}
  
 //进行避障
void bizhang()
  {

   if(barrier==1)  
 {          
  if(barrier_l<cammid) 
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
   
    if (mode_data==8)
	{
		if(turn[count1]==0)
		{
			
			pianchak=PIANCHA_LEFT;
			piancha();
			anglex=anglemid+anglek*(target_l-(cammid-deviation));
		}
		else
		{
			pianchak=PIANCHA_RIGHT;
			piancha();
			anglex=anglemid+anglek*(target_l-(cammid+deviation));
		}  
	}
	else
	{
		if(target_l<cammid)
		{
			pianchak=PIANCHA_LEFT;
			piancha();
			anglex=anglemid+anglek*(target_l-(cammid-deviation));
		}
		else
		{
			pianchak=PIANCHA_RIGHT;
			piancha();
			anglex=anglemid+anglek*(target_l-(cammid+deviation));
		}  
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
   
      
    if(target_l<cammid)
    {
		pianchak=PIANCHA_LEFT;
		piancha();
    anglex=anglemid+anglek*(target_l-(cammid-deviation));
    }
    else
    {
		pianchak=PIANCHA_RIGHT;
		piancha();
    anglex=anglemid+anglek*(target_l-(cammid+deviation));
    }  
     
   //防止信标避障延时结束后又进行信标避障
   //之所以会忽然左转，是因为两次进入信标避障，第二次进入时turn[count1]的值变为3了，与之前的值不同，打角计算不同
   if(target_h<16) 
   {    
        if(target_l>cammid)
        {
            anglex=anglemid-1;
               if(target_h<16) 
           {     
            anglex=anglemid-5;
           }
        }
         
        if(target_l<cammid)
        {
          anglex=anglemid+1;
          if(target_h<16) 
          {     
           anglex=anglemid+5;
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
 
