#include "head.h"
#include "rtp.h"

 uint16_t deviation=0;//ƫ��

//û���ҵ��ű�ʱ�Ķ���
void lookfor()
{
    //ֻ��������ôӻ�
    
     //�ű���Ϻ����ô�ת����       
  
	
	
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
  
 //���б���
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
      //��������С��Ѹ�ټ��ټ���
     if(anglex>acc_right&&anglex<acc_left)
     {                                     
        //���Ƽ��ټ��ٹ��� 
        if(target_h>acc_stop+avespeed/k12) 
        {
            speedx=speedjiasu;          
        }	

      //ǰ���ű�λ�õļ��ٶ�    ����ٶȺ�������ı��趨�ٶ�Ϊ����        
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
     
      //�������Ǵ��ڵ����µ���������
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
     
   //��ֹ�ű������ʱ�������ֽ����ű����
   //֮���Ի��Ȼ��ת������Ϊ���ν����ű���ϣ��ڶ��ν���ʱturn[count1]��ֵ��Ϊ3�ˣ���֮ǰ��ֵ��ͬ����Ǽ��㲻ͬ
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
    //a��С���򿿽��ű�ʱƫ���С��
      if(target_h<17)
      {
      a=234;b=14907;   //�˵�ֵҪ��Ӧ�������ͻ��
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
      //���Գ�һ������ϵ�����ڳ˱���ϵ�����������������������ͬʱ����������Ȼ������    
      deviation=pianchak*(b-a*target_h)/100;
}
 
