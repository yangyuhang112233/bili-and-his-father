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
	    uint16_t leftspeed,rightspeed;//�������趨�ٶ�
    uint16_t anglec;//���ݽǶ�ѡ�����
	        rightspeed=speedx;
      leftspeed=speedx; 
//      //���ݶ��������������������ӵ�ת�٣�������pidʵ��������ת��
//    
//    //float proportion[5]={1.41,1.36,1.28,1.24,1.19};//���ٱ�
//     float proportion[5]={1.4,1.15,1,1,1};//���ٱ���
//     float bili=0;//���ٱ���
//     
//    //���ٿ��ܵ����ڻ��ĳ��ش�
//     

//     
//  
//    
//    //����û�в��٣�Ч��Ҳ����
//             if(anglenow>anglemid-51&&anglenow<anglemid+51) 
//      {
//        rightspeed=speedx;
//        leftspeed=speedx;         
//      }        
//      else
//      {        
//       anglec=anglenow/10;
//                 
//        if(anglec<46)  //��ת
//        {
//         anglec=anglec-41; 
//         rightspeed=speedx;
//          bili=proportion[anglec];           
//         leftspeed=bili*speedx;       
//        }
//        if(anglec>55)           //��ת
//         {
//          anglec=60-anglec; 
//           bili=proportion[anglec];   
//          rightspeed=bili*speedx; 
//          leftspeed=speedx;          
//         }
//       } 
//       if(state==4)
//       {
//            if(anglec<46)  //��ת
//          {
//          
//         rightspeed=speedx;
//                  
//         leftspeed=1.7*speedx;       
//        }
//        if(anglec>55)           //��ת
//         {
//          rightspeed=1.7*speedx; 
//          leftspeed=speedx;          
//         }           
//       }
//      
       
       //ע��һ�����⣺��state==0ʱ���ܽ���һ���жϺ�Ͳ������жϣ�������ռ�ձȻ�̶����䣬����Ҫ��һ���ж�
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
//         Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��
//        ab=0;
//        }

//����count1��ֵ��һ ���жϽ���һ�δ�ת ��ת�Ĵ����޶���
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
				Motor_Control(20,25);		//20��25 19s����
				//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
				//            FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,4000);  
				//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 5000 ); 
				//            FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
				}		   
				else 
				{
					Motor_Control(30,20);	//30��20	19����
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
         Motor_Control(leftspeed,rightspeed);//�������ٶ�ѡ���������ٶ�ʵ��       
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
  
  