#include "head.h"

 //���������ֱ�Ϊ�����Ǻ��ٶȣ��˶�״̬ȫ��������ı䣬�˺����и��ݶ������Զ����ò���
  //��������ֻ�����ǣ��Զ����ݴ�����ü����ٶ�
  //���������������ȫ�ֱ���ʹ�ú������ı��˶�״̬ʱ���ô˺���
   
  void move()//��ǣ��ٶ���Ϊȫ�ֱ�������
{        
      //�����ǿ���
      Servo_Control();
     
    static bool ab=0;
    
       //��ֹ�ٶȹ���
       if(target_h<50)
     {
            if(qd_left_value+qd_right_value<24)
          {
          speedx=15;
          }
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
            if(ab==0)
            {
                if(forestate==3||forestate==4)
              {
                  //�ô�����ж�
                 if(leftspeed>rightspeed)
                {
                  Motor_Control(25,3);
                }
                 else
                { 
                  Motor_Control(3,25);      
                }     
               }
            else
            {
                 if(leftspeed>rightspeed)
                {
                  Motor_Control(18,16);
                }
                 else
                {
                  Motor_Control(16,18);     
                 }
             }
            ab=1;
         }
        
        }
        else
        {
         Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��
         ab=0;
        }
       
   
        
//       if(ab==0)
//{
//    
//             if((state==0&&forestate==3)||(state==0&&forestate==4))
//    {
//       if(leftspeed>rightspeed)
//       {
//        Motor_Control(25,3);
//       }
//       else
//       {
//       Motor_Control(3,25);      
//       }     
//      ab=1;       
//    }
////          else if(state==0&&forestate==4)
////    {
////       if(leftspeed>rightspeed)
////       {
////        Motor_Control(25,3);
////       }
////       else
////       {
////       Motor_Control(3,25);      
////       }    
////      a=1;           
////    }
//       else if(state==0)
//    {
//            if(leftspeed>rightspeed)
//        {
//         Motor_Control(18,16);
//        }
//        else
//        {
//        Motor_Control(16,18);     
//        }
//        ab=1;    
//    }
//      else       
//        {
//        Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��
//        ab=0;
//       }  
//        
//}
//else
//{
//   if(state!=0)
//   {
//       ab=0;
//   }
//}
 
//       
//                  if(state==0)
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
  
  