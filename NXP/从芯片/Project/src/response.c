#include "head.h"

 uint16_t deviation=0;//ƫ��

//û���ҵ��ű�ʱ�Ķ���
void lookfor()
{
    //ֻ��������ôӻ�
    
     //�ű���Ϻ����ô�ת����       
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
     //���֮ǰ��״̬Ϊ1�����ϣ�����ô�϶��Ǵ�״̬2��gothere���л�����״̬1�����л�����״̬0��lookfor����
     //��ô����Ϊ����ת�Ƕ�����Ŀ������ű꣬����Ҫ�ô�Ƿ�ת
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
  
 //���б���
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
    piancha();
      
    if(target_l<cammid)
    {
    anglex=anglemid+anglek*(target_l-(cammid-deviation));
    }
    else
    {
    anglex=anglemid+anglek*(target_l-(cammid+deviation));
    }  
     
   //��ֹ�ű������ʱ�������ֽ����ű����
   //֮���Ի��Ȼ��ת������Ϊ���ν����ű���ϣ��ڶ��ν���ʱturn[count1]��ֵ��Ϊ3�ˣ���֮ǰ��ֵ��ͬ����Ǽ��㲻ͬ
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
 
