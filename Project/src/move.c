#include "head.h"

 //���������ֱ�Ϊ�����Ǻ��ٶȣ��˶�״̬ȫ��������ı䣬�˺����и��ݶ������Զ����ò���
  //��������ֻ�����ǣ��Զ����ݴ�����ü����ٶ�
  //���������������ȫ�ֱ���ʹ�ú������ı��˶�״̬ʱ���ô˺���
   
  void move()//��ǣ��ٶ���Ϊȫ�ֱ�������
{        
      //�����ǿ���
      Servo_Control();
     
    
       //��ֹ�ٶȹ���
             if(qd_left_value+qd_right_value<20)
          {
          speedx=15;
          }
    
      //���ݶ��������������������ӵ�ת�٣�������pidʵ��������ת��
    
    //float proportion[5]={1.41,1.36,1.28,1.24,1.19};//���ٱ��
     float proportion[5]={1.4,1.15,1,1,1};//���ٱ���
    //���ٿ��ܵ����ڻ��ĳ��ش�
     
    uint16_t leftspeed,rightspeed;//�������趨�ٶ�
    uint16_t anglec;//���ݽǶ�ѡ�����
     
    
    //����û�в��٣�Ч��Ҳ����
             if(anglenow>anglemid-51&&anglenow<anglemid+51) 
      {
        rightspeed=speedx;
        leftspeed=speedx;         
      }        
      else
      {        
       anglec=anglenow/10;
                 
        if(anglec<46)  //��ת
        {
         anglec=anglec-41; 
         rightspeed=speedx; 
         leftspeed=proportion[anglec]*speedx;       
        }
        if(anglec>55)           //��ת
         {
          anglec=60-anglec; 
          rightspeed=proportion[anglec]*speedx; 
          leftspeed=speedx;          
         }
       } 
       
       
             if(state==0)
{
       if(leftspeed>rightspeed)
       {
        Motor_Control(18,1);
       }
       else
       {
       Motor_Control(1,18);
       
       }         
}
       else
       {
        Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��
     
       }
       
       
       //�ٶȿ���ֻ��������±�ʵ��
      //  Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��
     
       
       //��ͨ����������ʱ
        if(state==1)
       {           
           DelayMs(20);
           if(qd_left_value +qd_right_value<35) DelayMs(10);
       } 

      
          
       //������ű����״̬��ô����һ����ʱ����ʱ�ڷ����ٶȲ��䣬ʹС��������Ϩ���ű�
    
       if(state==3)
       {
                for(int co1=0;co1<3;co1++)
            {              
             Motor_Control(leftspeed,rightspeed);
             DelayMs(delay2);
            }     
       }  
       //��û���ͨ���������ű�ƴ���ͼ���ĳһλ��
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
  
  