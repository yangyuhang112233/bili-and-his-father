#include "head.h"

 uint16_t deviation=0;//ƫ��

//Ѱ���ű�  ����ǰ���ű�λ�� �����ϣ� �����ű����   �ű���ϼ���

//ÿ�������ı�speedx��anglex������

//дһ���������������ͨ��led�����п�״̬ת��

    //û���ҵ��ű�ʱ�Ķ���
void lookfor()
{

//if(count1==0)
//{}
//else

//�ű���Ϻ����ô�ת����       
	if(forestate==3)
	{
		switch(turn[count11[3]]) 
		{
			case 1:
			anglex=SERVO_MIDDLE-20; 
			break;
			
			case 2:
			anglex=angleright;         
			break;   
			
			case 3:
			// if()  //�ж��Ƿ����ת
			anglex=angleleft;         
			   
			//         if(count1==)
			//         �����ת
			break; 
			
			case 4:
			anglex=angleright;               
			break;  

			//          case 5:
			//             
			//        //�����ת
			//             anglex=angleright;         
			//               
			//             break; 
			//         case 6:
			//             //�����ת
			//             anglex=angleleft;            
			//         break;   
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
		else  //�����ô�Ǳȼ���ֵС
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

//����·���滮��ʱ
//   if(count1==1)
//   {
//   DelayMs(10);
//   }

}

//���б���
void bizhang()
{
//ȷ�����б��ϣ������ϰ������������ñ��ϴ��
//��ǱȽ�С��ʱ���������ô�ǣ���������

//if(forestate!=1)   //������Ϻ󱣳ֱ��ϴ�ǲ���
//{
	if(barrier2==1)  
	{          
		if(barrier2_l>38) 
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

	if(barrier==1)  
	{          
		if(barrier_l<160) //��Ҫ������ת
		{
			if(anglex<hide_left) //���ԭ�ȴ�Ǳȱ�����ת��ǻ�Ҫ������ô����Ҫ�ı���
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
	//}

}




//ǰ���ű�λ��
//����·���滮��������Ƿ����
//�����ֵ543  �Ҽ���465  ����620
void gothere()
{

	//�����Ե������ƫ��
	piancha();

	//��̬���üӼ��پ���
	// jiajiansujuli();

	//       //��һ���������������¸�ֵcammid�ĺ���
	//      if(target_h>65)cammid=153;
	//      else if(target_h>45)cammid=154;
	//      else
	//      {
	//      cammid=155;
	//      }

	//·���滮�� 1 ������ת�� 2 ������ת�� 3 �����룻 4 �����룻

	switch(turn[count1])//����Ӧ�����ǵ���anglex��ֵ���ܳ�����Χ������anglec��ֵ������Χ�����³����������Ժ���anglenow��ֵӦ���޶���Χ
	{
		case 1:
		anglex=anglemid-(anglek*(cammid-target_l));
		break;
		
		case 2:
		anglex=anglemid+(anglek*(target_l-cammid));
		break;  
		
		case 3:
		//���������Ŀ��λ�ã���ϣ��tl���ڵ�λ�ã�ͨ���������ڼ�����tl�����Ǹ�λ�� 
		anglex=anglemid+anglek*(target_l-(cammid-deviation));
		break; 
		
		case 4:
		anglex=anglemid+anglek*(target_l-(cammid+deviation));
		break;
	}

	uint16_t avespeed;
	avespeed=(qd_left_value+qd_right_value)/2;

	if(turn[count1]==3||turn[count1]==4)
	{
		//��������С��Ѹ�ټ��ټ���
		if(anglex>acc_right&&anglex<acc_left)
		{
			//�����ű꿴��ʱ�����������üӼ���������


			//���Ƽ��ټ��ٹ��� 
			if(target_h>acc_stop1+avespeed/1.2) 
			{
				speedx=speedjiasu;          
			}	

			//ǰ���ű�λ�õļ��ٶ�    ����ٶȺ�������ı��趨�ٶ�Ϊ����        
			else
			{   
				//�ڵ�һ�ν���˴�ʱ�趨�ٶ�ֵ��֮��������������趨ֵ���䡣
				//��һ���趨�ٶ�ֵʱ���ݽ����ű����ʱ���ٶ��趨�ٶ��Ǽ��ٻ��Ǽ���
				if(speedx!=speedxinjiansu&&speedx!=speedxinjia)
				{
					if(avespeed>15)
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
			if(avespeed>25)
			{
				speedx=speedzhuanwan;
			}
			else
			{
				speedx=speedzhuanwan2;
			}
		}
	}
	else
	{
		if(anglex>acc_right&&anglex<acc_left)
		{
			//�����ű꿴��ʱ�����������üӼ���������
			//���Ƽ��ټ��ٹ��� 
			if(target_h>acc_stop2+avespeed/k12) 
			{
				speedx=speedjiasu2;          
			}	

			//ǰ���ű�λ�õļ��ٶ�    ����ٶȺ�������ı��趨�ٶ�Ϊ����        
			else
			{   
				//�ڵ�һ�ν���˴�ʱ�趨�ٶ�ֵ��֮��������������趨ֵ���䡣
				//��һ���趨�ٶ�ֵʱ���ݽ����ű����ʱ���ٶ��趨�ٶ��Ǽ��ٻ��Ǽ���
				if(speedx!=speedxinjiansu2&&speedx!=speedxinjia2)
				{
					if(avespeed>20)
					{
						speedx=speedxinjiansu2;     
					}
					else
					{
						speedx=speedxinjia2;   
					}

				}
			}
		}
		//�������Ǵ��ڵ����µ���������
		else
		{
			if(avespeed>25)
			{
				speedx=speedzhuanwan;
			}
			else
			{
				speedx=speedzhuanwan2;
			}
		}
	}
}

//�����ű�ʱ�й��ű�
//����·���滮��������Ƿ����

void gothere1()
{
	//�����Ե������ƫ��
	piancha();

	//·���滮��  3 �����룻 4 �����룻
	switch(turn[count1])//����Ӧ�����ǵ���anglex��ֵ���ܳ�����Χ������anglec��ֵ������Χ�����³����������Ժ���anglenow��ֵӦ���޶���Χ
	{  
		case 3:
		anglex=anglemid-(anglek*(cammid-target_l-deviation));
		break;
		
		case 4:
		anglex=anglemid+(anglek*(target_l-cammid-deviation));
		break;
	}

	//��ֹ�ű������ʱ�������ֽ����ű����
	//֮���Ի��Ȼ��ת������Ϊ���ν����ű���ϣ��ڶ��ν���ʱturn[count1]��ֵ��Ϊ3�ˣ���֮ǰ��ֵ��ͬ����Ǽ��㲻ͬ
	if(target_h<16) 
	{    
		if(turn[count1]==4)
		{
			anglex=anglemid-1;
		
			if(target_h<14) 
			{     
				anglex=anglemid-6;
			}
		}
		if(turn[count1]==3)
		{
			anglex=anglemid+1;
			if(target_h<14) 
			{     
				anglex=anglemid+6;
			}
		}
		//       //��ֹ�ű����ʱ�����ű�
		//      if(anglex<560&&anglex>534)
		//      {
		//      anglex=543;
		//      }
		//      else
		//      {
		//       anglex=foreangle;
		//      }          
	}
	speedx=speedxinbi1;
}

//ƫ����㺯��
 
void piancha()
{

	uint16_t a,b;
	//a��С���򿿽��ű�ʱƫ���С��
	if(target_h<17)
	{
		a=234;b=14907;   //234  14907  �˵�ֵҪ��Ӧ�������ͻ��
	}
	else if(target_h<43)
	{ 
		a=185;b=14477;  //176 14090  
	}
	else if(target_h<70)
	{
		a=122;b=11864;  //11920
	}
	else 
	{
		a=115;b=11374;  //11332
	}

	//���Գ�һ������ϵ�����ڳ˱���ϵ�����������������������ͬʱ����������Ȼ������

	deviation=pianchak*(b-a*target_h)/100;

}
 
 
 //�ű����  �����������ű���ϵ�������  �ű���ϵĴ��
 //�ű����һ����ʼ��һֱ����ֱ���������ű꣬��ʱ�����lookfor����
void pointbizhang()
{
	//С��ֱ��ǰ���ű�ʱ������ͨ�����ù̶������ʵ��

	//����ģ�±�Ե�й��ķ��������ű괦�ڲ�ͬλ�ã�ͨ��ͼ������
	if(turn[count1]==2) 
	{
		anglex=hide2_right;
	}		
	if(turn[count1]==1)
	{
		anglex=hide2_left;             
	}
	speedx=speedxinbi2;
}