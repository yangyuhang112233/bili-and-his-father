#include "head.h"

            
uint8_t bamakaiguan=0;//���뿪��״̬
 uint16_t xinbiaoxiangsu;//�ű����ظ���
uint16_t xinbiao0[10];//��ȥ���ű�����ֵ
uint8_t xinbiaobiaozhi=0;//�ж��Ƿ��ű����ظ�������400
uint8_t xidengshu=0;//Ϩ���õƵĸ���

 void speedset()
 {
     //����������������������ֻ�ٶ�
     
     switch(count1)
     {
//         
//               case 1:
//    speedjiasu=     15;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 10;           //�����ű� ���м���   
//    speedxinjia=    10;          //�����ű� �ٶ�̫�� ������ 
//             break;
//         
//       case 2:
//    speedjiasu=     27;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 16;           //�����ű� ���м���   
//    speedxinjia=    25;          //�����ű� �ٶ�̫�� ������  
//         break;
          
         
         
         
//         case 0:
//             //�������
////             speedjiasu=     27;            //Զ���ű� ֱ�߼���
//// speedxinjiansu= 20;        //�����ű� ���м���
//// speedxinjia=    23;          //�����ű� �ٶ�̫�� ������ 
//         
//         
// speedjiasu=     33;            //Զ���ű� ֱ�߼���
// speedxinjiansu= 21;        //�����ű� ���м���
// speedxinjia=    26;          //�����ű� �ٶ�̫�� ������
//         
//         
//// speedzhuanwan=  15;        //Ѱ���ű�ת���ٶ�

//// speeddazhuan=   20;         //�Ҳ����ű��ת���ٶ�
//// speedbizhang=   6;          //���ϼ���
//// speedxinbi=     7;            //�ű���ϼ���
//// speedxinbijia=  23;          //�ű����ʱ̫���������
//       //��������pi����������������ı�
//         
//             break;
//         

////   
////             break;
////        case 3:
////    speedjiasu=     27;           //Զ���ű� ֱ�߼���  
////    speedxinjiansu= 16;           //�����ű� ���м���   
////    speedxinjia=    25;          //�����ű� �ٶ�̫�� ������  
////       
////             break;
//         
//                case 2:   //�������
//    speedjiasu=     18;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 12;           //�����ű� ���м���   
//    speedxinjia=    12;          //�����ű� �ٶ�̫�� ������  
//   
//             break;
//        case 3:
//    speedjiasu=     24;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 16;           //�����ű� ���м���   
//    speedxinjia=    22;          //�����ű� �ٶ�̫�� ������  
//       
//             break;
//        
//               case 4:
//    speedjiasu=     33;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 22;           //�����ű� ���м���   
//    speedxinjia=    27;          //�����ű� �ٶ�̫�� ������  
//       
//             break;
//               
//                 case 6://�������
//    speedjiasu=     24;           //Զ���ű� ֱ�߼���  
//    speedxinjiansu= 17;           //�����ű� ���м���   
//    speedxinjia=    22;          //�����ű� �ٶ�̫�� ������  
//         
//             break;
//        
//        
////         case 6:
////    speedjiasu=     28;           //Զ���ű� ֱ�߼���  
////    speedxinjiansu= 21;           //�����ű� ���м���   
////    speedxinjia=    25;          //�����ű� �ٶ�̫�� ������  
////         
////             break;
//        
         default:
             break;
     }
     
 
 }
 
//count1Ϊ0������ǰ����һ���ƣ�Ϊ1������ �����һ���Ƶ��ű���� ��  ����ڶ����Ƶ��ű����֮�䡣
void pass()
{
         //�����ű����ʱ��1  
       
    //��Ϊ�ٶȱȽϿ죬�����еĵ��е�ʱ�򶶵�������û�н����ű��Ϩ���˵ƽ�����һ���ҵ���
   //���Է������������˼�������״̬����¼���������ͣ����ͨ��led��ʾ
//     if(forestate!=3&&state==3)
//      {   
//          count1++;        
//      }
//         if(forestate==2&&state==0)
//      {   
//          count1++;        
//      }
    
      //������������������ֱ�Ӵ�������ֵ����������Щԭʼ�����������
if(xinbiaobiaozhi==0)
   {
      if(xinbiaoxiangsu>350&&target_h<23)
      {
      xinbiaobiaozhi=1;
      
      }
   }
else
   {
     if(xinbiaoxiangsu<180)
     {
      count1++;
       xidengshu++;
      xinbiaobiaozhi=0;
     }         
   }
  

  
      if(count1==10)count1=0;
   
   
         //ֹͣ�˶�
      if(xidengshu==20)   
      {        
       stopmove();
      }  
   
   
   
   
   
}
      //���ű���ϵ��ٽ�����ë�̣��ű�����������΢С���������ű�״̬������������ɼ����������ű���ϣ������������
      //����ë�����⣬���Ը���ǰ��4��״̬������״̬�������Ƚ϶��״̬�����ж�״̬ 
//        if(xinbiao0[0]<400&&xinbiaoxiangsu>400)
//      {   
//          count1++;        
//      }
      
      
      
      
      
      
      



      
//      if(state0[0]==3&&state0[1]==3&&state0[2]==3&&state0[3]!=3&&state0[4]!=3)
//      {
//      count1++;    
//      }
     
      //ͨ������ֵ�仯���ж��Ƿ񾭹���
//      if(xinbiao-xinbiao0[0]>50||xinbiao0[0]-xinbiao<50)
//      {
//      count1++; 
//      }
      
      

      
      
      //������Ϊһ��ģ�壬����״̬�ı䣬Ȼ�����ǰ״̬����״̬��ֵ���жϾ����˵�
      //�����ű����ʱ��1
//      if(forestate==3&&state!=3)
//      {
//     
//      
//      }
                       

  //����ǰһ��״̬�ı���
void prestate()
{   
    jishuwei++;
    if(jishuwei>200)
    {
    jishuwei=0;
    }
    
    
 forestate=state;
 foreangle=anglex;

    
    //������������һ�����飬����������ǹ�ȥ�����ı仯��״̬
     //�洢��ȥ��״̬ 0Ϊ�ոյ�״̬ 
    
   for(uint8_t i=4;i>0;i--)
    {
    count11[i]=count11[i-1];
    }
    count11[0]=count1;

    
    for(uint8_t i=9;i>0;i--)
    {
    state0[i]=state0[i-1];
    }
    state0[0]=state;
    
    
       for(uint8_t i=9;i>0;i--)
    {
    xinbiao0[i]=xinbiao0[i-1];
    }
    xinbiao0[0]=xinbiaoxiangsu;
}


//   //����7620ͼ���ж�С���Ƿ񲻶�����������͵���   ʹ�ó������ж��Ƿ�ײ��������
//void daoche()
//{
//    
//   static uint8_t CCD_Image33[100][100];//ͼ������,�����ж�С���Ƿ�ͣס
//   uint32_t countzong=0;
//   static uint8_t i=0;//�����жϾ����˼���ѭ��
//    
//    i++;
//    
//    if(i==20)
//{
//         for(uint16_t ii=0;ii<80;ii++)	
//      {     
//          for(uint16_t jj=0;jj<80;jj++)
//        {
//         CCD_Image33[ii][jj]= CCD_Image[ii+100][jj];  //����ͨ������ȡ��ķ���   
//        }
//      }         
//}
//     //ÿ��40��ѭ��������40��ѭ��ǰ��ͼ��������ͼ��Ĳ����С
//    if(i==40)
//{
//       i=0;
//       countzong=0;
//    
//       //��������ͼ��Ĳ��� 
//          for(uint16_t ii=0;ii<80;ii++)	
//      {     
//          for(uint16_t jj=0;jj<80;jj++)
//        {
//         countzong=countzong+CCD_Image33[ii][jj]-CCD_Image[ii+100][jj];      
//        }
//      }  
//      
//      //ͼ������С���򵹳�
////    if(countzong<100000)
////    {
////        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
////        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,9000);
////    	  FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
////        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 9000 );
////        DelayMs(2000);
////    }
//         
//}
//    LCD_printf(10,5,"co:   ");
//    LCD_printf(10,5,"co:%d",countzong);

//}
