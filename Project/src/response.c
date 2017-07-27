#include "head.h"

 uint16_t deviation=0;//偏差

//寻找信标  加速前往信标位置 （避障） 靠近信标减速   信标避障减速

//每个函数改变speedx和anglex两个量

//写一个函数，在跑完后通过led屏集中看状态转化

    //没有找到信标时的动作
void lookfor()
{

//if(count1==0)
//{}
//else

//信标避障后，设置大转弯打角       
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
			// if()  //判断是否反向大转
			anglex=angleleft;         
			   
			//         if(count1==)
			//         反向大转
			break; 
			
			case 4:
			anglex=angleright;               
			break;  

			//          case 5:
			//             
			//        //反向大转
			//             anglex=angleright;         
			//               
			//             break; 
			//         case 6:
			//             //反向大转
			//             anglex=angleleft;            
			//         break;   
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
		else  //可以让打角比极限值小
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

//设置路径规划延时
//   if(count1==1)
//   {
//   DelayMs(10);
//   }

}

//进行避障
void bizhang()
{
//确定进行避障，根据障碍物列坐标设置避障打角
//打角比较小的时候重新设置打角，否则不设置

//if(forestate!=1)   //进入避障后保持避障打角不变
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
		if(barrier_l<160) //需要避障左转
		{
			if(anglex<hide_left) //如果原先打角比避障左转打角还要靠左，那么不需要改变打角
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




//前往信标位置
//根据路径规划情况设置是否减速
//舵机中值543  右极限465  左极限620
void gothere()
{

	//计算边缘经过的偏差
	piancha();

	//动态设置加减速距离
	// jiajiansujuli();

	//       //加一个根据行坐边重新赋值cammid的函数
	//      if(target_h>65)cammid=153;
	//      else if(target_h>45)cammid=154;
	//      else
	//      {
	//      cammid=155;
	//      }

	//路径规划： 1 避障左转； 2 避障右转； 3 左切入； 4 右切入；

	switch(turn[count1])//这里应当考虑到，anglex的值可能超出范围，导致anglec的值超出范围，导致程序卡死。所以后面anglenow的值应当限定范围
	{
		case 1:
		anglex=anglemid-(anglek*(cammid-target_l));
		break;
		
		case 2:
		anglex=anglemid+(anglek*(target_l-cammid));
		break;  
		
		case 3:
		//括号里的是目标位置，即希望tl处在的位置，通过反馈调节即可让tl处在那个位置 
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
		//若舵机打角小，迅速加速减速
		if(anglex>acc_right&&anglex<acc_left)
		{
			//根据信标看到时的行坐标设置加减速行坐标


			//控制加速减速过程 
			if(target_h>acc_stop1+avespeed/1.2) 
			{
				speedx=speedjiasu;          
			}	

			//前往信标位置的减速段    如果速度很慢，则改变设定速度为加速        
			else
			{   
				//在第一次进入此处时设定速度值，之后在这个函数处设定值不变。
				//第一次设定速度值时根据进入信标避障时的速度设定速度是加速还是减速
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

		//若舵机打角大，在低速下调整正方向
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
			//根据信标看到时的行坐标设置加减速行坐标
			//控制加速减速过程 
			if(target_h>acc_stop2+avespeed/k12) 
			{
				speedx=speedjiasu2;          
			}	

			//前往信标位置的减速段    如果速度很慢，则改变设定速度为加速        
			else
			{   
				//在第一次进入此处时设定速度值，之后在这个函数处设定值不变。
				//第一次设定速度值时根据进入信标避障时的速度设定速度是加速还是减速
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
		//若舵机打角大，在低速下调整正方向
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

//靠近信标时切过信标
//根据路径规划情况设置是否减速

void gothere1()
{
	//计算边缘经过的偏差
	piancha();

	//路径规划：  3 左切入； 4 右切入；
	switch(turn[count1])//这里应当考虑到，anglex的值可能超出范围，导致anglec的值超出范围，导致程序卡死。所以后面anglenow的值应当限定范围
	{  
		case 3:
		anglex=anglemid-(anglek*(cammid-target_l-deviation));
		break;
		
		case 4:
		anglex=anglemid+(anglek*(target_l-cammid-deviation));
		break;
	}

	//防止信标避障延时结束后又进行信标避障
	//之所以会忽然左转，是因为两次进入信标避障，第二次进入时turn[count1]的值变为3了，与之前的值不同，打角计算不同
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
		//       //防止信标避障时靠近信标
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

//偏差计算函数
 
void piancha()
{

	uint16_t a,b;
	//a调小，则靠近信标时偏差变小；
	if(target_h<17)
	{
		a=234;b=14907;   //234  14907  端点值要对应，否则会突变
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

	//可以乘一个比例系数，在乘比例系数的情况下满足了线性增大，同时满足曲线依然相连接

	deviation=pianchak*(b-a*target_h)/100;

}
 
 
 //信标避障  参数：进行信标避障的行坐标  信标避障的打角
 //信标避障一旦开始就一直进行直到看不到信标，这时候进行lookfor函数
void pointbizhang()
{
	//小车直线前往信标时，避障通过设置固定打角来实现

	//可以模仿边缘切过的方法，让信标处在不同位置，通过图像来看
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