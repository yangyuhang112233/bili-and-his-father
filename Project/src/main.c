#include "head.h"

int main(void)
{  
    jioushu=1;//����7620��7725����ͼƬ�������ɼ��ʹ��� 
    
    getready();
    
    firstimage();
    duqubama();
    
  
    while(1)
    {   
        
		QD_value();
              
        
       //�������count1��ֵ����д�ٶ�ֵ��ʵ���ٶȵ�·���滮 
       
       //speedset();//����count1ֵ��ͬ���ò�ͬ���ٶ�
        
	   GPIO_ToggleBit(HW_GPIOA, 15); //С����˸��ʾ����ѭ��
       startimage();  //��ʼ�ɼ�ͼ������� 
        
        
        //sending3(); 
        //һ������ͼ���趨��ͬ��־λ 
             
	    findpoint();//�ж��Ƿ��ҵ��ű꣬�������ű�λ�úͱ�־λ,�ж��Ƿ�������ͱ���ϣ��Ƿ����ű����
        
       //if(x[count1]==1){}//���þ�����һ���ƿ�����
       // findbarrier();//�ж�ǰ���Ƿ���Ҫ��ͨ����
        
         barrier2=0;barrier=0;//�رձ���
        
        //��:���ݱ�־λ�ж���Ӧ��״̬ 
//��������        �趨���һֱ���ڱ��ϵ�״̬�����ϴ�ǲ���  ��һֱ���ϴ�ת
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
    
        
   //��������״̬�Ĳ�ִͬ����Ӧ�Ĳ���
        
        switch(state)
              {
                case 0://�Ҳ����ű꣬תһת���ҵ��ű�
//                lookfor();
                break;
                
                case 1://�ҵ��ű��״̬������ǰ�����ϰ�����б���
               // bizhang();
               
                break;
                
                case 2://�ҵ��ű��״̬��ǰ��û���ϰ��ǰ���ű�λ��
                gothere();   
                break;
                
                case 3://�����ű�����ű���� ���߽��б�Ե�й��������gothere ����ͨ����������case��ʵ�֣�ʹ�ò�ͬ�ı���������   
                             
                gothere1();//�ű��й�          
                break;
            
                
                case 4:
                pointbizhang();   //�ű����   
                break;
              
               
             default:
             break;     
              }
              
          
              
              
      //�ģ������Ǻ͵���ٶȸı�
              
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
      //�壺�жϾ�����һ����   �ȴ��ɼ�ͼ�����  ����ǰһ��״̬�ı���
        pass();                      
       
              
       endimage();  
              
       prestate();   
              
        //Printf();

              

      
      bamaswitch();//���뿪�غ���   
    }   
}

