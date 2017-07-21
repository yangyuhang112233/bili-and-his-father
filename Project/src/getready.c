#include "head.h"

 uint16_t tt=0;//初始化1ms中断函数的变量
 //1ms中断回调函数
 
void PIT1_HandlerU( void )
{
	tt++;
}

 void getready()
 {
    
  DelayInit();
    
    /* PTA4设置成输入，防止死机 */
    GPIO_QuickInit (HW_GPIOA ,4,kGPIO_Mode_OPP);
    
    /* 正常运行指示灯初始化 */
    GPIO_QuickInit(HW_GPIOA ,15, kGPIO_Mode_OPP); 

    /* UART端口初始化 */
    UART_QuickInit(UART0_RX_PB16_TX_PB17, 115200);
		 
    /* IO口模拟IIC端口初始化 */    /* 如需更改端口请去io2iic.h头文件中修改 */
    GPIO_QuickInit(IIC_SCL_PORT , IIC_SCL_PIN , kGPIO_Mode_OPP);
    GPIO_QuickInit(IIC_SDA_PORT , IIC_SDA_PIN , kGPIO_Mode_OPP);
    
     /* 拨码开关初始化 */
    GPIO_QuickInit(HW_GPIOB, 8 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 9 , kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 10, kGPIO_Mode_IPU);
    GPIO_QuickInit(HW_GPIOB, 11, kGPIO_Mode_IPU);
     
    /* 初始化正交解码，端口号分别为左：PA12,PA13;右：PB18,PB19*/      
    FTM_QD_QuickInit(FTM1_QD_PHA_PA12_PHB_PA13, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding);
    FTM_QD_QuickInit(FTM2_QD_PHA_PB18_PHB_PB19, kFTM_QD_NormalPolarity, kQD_CountDirectionEncoding); 

    /* 舵机初始化 */
    CMT_PWM_QuickInit (55,0);
    /* 设置舵机初使占空比，范围0-10000分别表示0-100% */
    anglex=anglemid;
    CMT_PWM_ChangDuty (anglex);
    
    /* FTM快速初始化 */
    FTM_PWM_QuickInit(FTM0_CH0_PC01, kPWM_EdgeAligned ,10000);     /* 设置PC03为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH1_PC02, kPWM_EdgeAligned ,10000);     /* 设置PD04为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH2_PC03, kPWM_EdgeAligned ,10000);     /* 设置PC03为电机输出端口，频率设定为5000Hz*/
    FTM_PWM_QuickInit(FTM0_CH3_PC04, kPWM_EdgeAligned ,10000);     /* 设置PD04为电机输出端口，频率设定为5000Hz*/
    /* 设置FTM初使占空比，范围0-10000分别表示0-100% */
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH0, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH1, 0);
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH2, 0); 
    FTM_PWM_ChangeDuty(HW_FTM0, HW_FTM_CH3, 0);
		
		 //初始化pit模块的0通道，产生20ms的中断
      PIT_QuickInit(HW_PIT_CH0, 20000);
      PIT_CallbackInstall(HW_PIT_CH0, QD_value ); //注册通道0的回调函数为：QD_value（）
      PIT_ITDMAConfig(HW_PIT_CH0, kPIT_IT_TOF, ENABLE); //开起模块0通道中断 
        
        //初始化pit模块的1通道，产生1ms的中断
	  PIT_QuickInit(HW_PIT_CH1, 1000);
      PIT_CallbackInstall(HW_PIT_CH1, PIT1_HandlerU ); //注册通道1的回调函数为：PIT1_HandlerU（）		
	  PIT_ITDMAConfig(HW_PIT_CH1, kPIT_IT_TOF, ENABLE); //开起模块1通道中断 
		
  
		//turn_side=TurnSide_Array[0];
    //小液晶初始化
    LCD_Init();
    
    //摄像头初始化
    OV7620_Init();
    ov7725_Init();

    /* 看门狗初始化   500ms  */
//   	WDOG_QuickInit(500);
 
 
 }
 
//不好用的中断延时函数
// void wait(uint16_t time)
// {
//     uint16_t tt1,tt2;
//    tt2=tt;
//     if(tt2>65535-time)tt2=time-(65535-tt2);//防止tt到65535后重置为0
//     else
//         tt2=tt2+time;
//     while(tt1>tt2)
//     {
//     tt1=tt;
//     }
// 
// }
  
 
  /**************************************************************
* 函数名称:void Printf()
* 简介：变量显示
**************************************************************/
void Printf()
{
   //信标显示
    LCD_printf(10,5,"target:   ");
    LCD_printf(10,5,"target:%d",target_flag);
    
    LCD_printf(60,5,"th:   ");
    LCD_printf(60,5,"th:%d",target_h);
    
    LCD_printf(10,20,"tl:   ");
    LCD_printf(10,20,"tl:%d",target_l);

    //障碍物显示
//    LCD_printf(60,20,"bar2:    "); 
//    LCD_printf(60,20,"bar2:%d",barrier); 
//    
//    LCD_printf(10,35,"bh:   ");
//    LCD_printf(10,35,"bh:%d",barrier_h);
//    
//    LCD_printf(60,35,"bl:   ");
//    LCD_printf(60,35,"bl:%d",barrier_l);
    
        LCD_printf(60,20,"bar2:    "); 
    LCD_printf(60,20,"bar2:%d",barrier); 
    
    LCD_printf(10,35,"bh:   ");
    LCD_printf(10,35,"bh:%d",barrier);
    
    LCD_printf(60,35,"bl:   ");
    LCD_printf(60,35,"bl:%d",barrier);
    
    
    //经过第几个灯
    LCD_printf(10,50,"co1:    "); 
    LCD_printf(10,50,"co1:%d",count1); 
    
    LCD_printf(60,50,"7c:  "); 
    LCD_printf(60,50,"7c:%d",countbz7620); 
    
//        LCD_printf(60,50,"7c:  "); 
//    LCD_printf(60,50,"7c:%d",count7725); 
    
    LCD_printf(10,65,"state:   ");
    LCD_printf(10,65,"state:%d",state);
    
    //障碍物和信标灯之间的平方距离
    LCD_printf(60,65,"juli:   ");
    LCD_printf(60,65,"juli:%d",juli);
    
  
    LCD_printf(10,75,"fazhi:   ");
    LCD_printf(10,75,"fazhi:%d",xiangsuzhi);
    
    
    LCD_printf(10,95,"speed:    "); 
    LCD_printf(10,95,"speed:%d",speedx);

    LCD_printf(60,95,"xx:    "); 
    LCD_printf(60,95,"xx:%d",xinbiaoxiangsu);
//    LCD_printf(10,75,"st:   ");
//    LCD_printf(10,75,"st:%d",stopba);
//    
//    LCD_printf(10,95,"xbb:    "); 
//    LCD_printf(10,95,"xbb:%d",xinbiaobizhang);
    

    
}
void duqubama()
{
		if(GPIO_ReadBit(HW_GPIOB, 8)==0)    //拨码开关控制  
       {
		   bama[0]=1;
       }      
       	if(GPIO_ReadBit(HW_GPIOB, 9)==0)    //拨码开关控制  
       {
		 bama[1]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 10)==0)    //拨码开关控制  
       {
		bama[2]=1;
       }
       	if(GPIO_ReadBit(HW_GPIOB, 11)==0)    //拨码开关控制  
       {
		 bama[3]=1;
       }   
       bamakaiguan=bama[0]+2* bama[1]+2*2*bama[2]+2*2*2*bama[3];
}
void bamaswitch()
{
    
             //拔码开关状态情况

    switch(bamakaiguan)
{
         
case 1:  //打开led显示屏
Printf();
        break;
case  2://设置低速跑
                     
speedzhuanwan=15;        //寻找信标转弯速度
speedjiasu=15;            //远离信标 直线加速
speedxinjiansu=15;        //靠近信标 进行减速
speedxinjia=15;          //靠近信标 速度太慢 而加速
speeddazhuan=15;         //找不到信标大转弯速度
speedbizhang=15;          //避障减速
speedxinbi1=15;            //信标避障减速
speedxinbi2=15;            //信标避障减速

//speedxinbijia=15;          //信标避障时太慢，则加速                

      break; 
         
case 4:
sending3();
        
      break;   
        
case 8:   //看7725图像
    
       //7725摄像头采集图像  
     ov7725_Get_Imge();
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));

    uint8_t colour[2] = {0xfe, 0x00};
    uint8_t temp=0;
    for(uint16_t i=0;i<(OV7725_H*OV7725_W);i++)
    {
        if(i==(temp*OV7725_W +center[temp]))
        {
            temp++;
            UART_WriteByte (HW_UART0 ,0);
        }
        else
            UART_WriteByte (HW_UART0 ,colour [img[i]]);
    }
    UART_WriteByte(HW_UART0,0xff);
 break;
      
    case  3:
                 xideng=1;    
                

      break;
        case  5:
                 xideng=5;    
               
      break;
        
       case  7:
           
       xideng=5;    
 speedzhuanwan=15;        //寻找信标转弯速度
speedjiasu=15;            //远离信标 直线加速
speedxinjiansu=15;        //靠近信标 进行减速
speedxinjia=15;          //靠近信标 速度太慢 而加速
speeddazhuan=15;         //找不到信标大转弯速度
speedbizhang=15;          //避障减速
speedxinbi1=15;            //信标避障减速
speedxinbi2=15;            //信标避障减速
//speedxinbijia=15;          //信标避障时太慢，则加速  
      break;
        
default:break;    
}
         
         
         
}

void firstimage()
{
         //先让车停住，看到灯再开始跑
//         while(target_flag==0)
//        {
//          findpoint();
//        }
    
   
     //采集第一幅图像
    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
   	
     //7725摄像头采集图像  
     ov7725_Get_Imge();
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));
       
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);            //等待图像采集完毕
}

void startimage()
{
    if(jioushu==0)jioushu=1;
    else 
    {
    jioushu=0;
    }

     if(jioushu==1)
    {
       DMA_InitStruct1.dAddr = (uint32_t)CCD_Image;      
    }
    
    else
    {
    DMA_InitStruct1.dAddr = (uint32_t)CCD_Image22;  
    }
    
    //7620摄像头开始采集图像
    ov7620_img_flag = OV7620_STATE_IDLE;            //空闲状态，开始采集图像
    PORTE->ISFR = ~0; //清除后置摄像头标志位 	
    enable_irq(OV7620_VSYN_GPIO_IRQ);
   	    
   
     //7725摄像头开始采集图像
    ov7725_img_flag = IMG_START;                    //开始采集图像
    PORTA->ISFR = ~0;                               //写1请中断标志位
    enable_irq(PORTA_IRQn);                         //允许PTA的中断
    
    
}

 void endimage()
{
    
      //7725 采集图像结束       
    while(ov7725_img_flag != IMG_FINISH)            //等待图像采集完毕
    {
        if(ov7725_img_flag == IMG_FAIL)           //加入图像采集错误，则重新采集
        {
            ov7725_img_flag = IMG_START;            //开始采集图像
            PORTA->ISFR = ~0;                       //写1请中断标志位
            enable_irq(PORTA_IRQn);                 //允许PTA的中断
        }
    }  
       
       if(jioushu==1)
    {
     img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));
    }
    else
    {
     img_extract(img22, CCDBufferPool ,OV7725_H*(OV7725_W/8));
    }
    
    
    //7620 采集图像结束  
    while(ov7620_img_flag != OV7620_STATE_COMPLETE);   //等待图像采集完毕           
} 


//刹车函数
void stopmove()
{
     uint16_t leftspeed=0;
     uint16_t rightspeed=0;
             
    static int16_t Kp=1200;
    static int16_t Ki=0;
    
    static int16_t leftsum ;
    static int16_t rightsum ;
              
                 
      int16_t lefterror;//速度偏差
      int16_t righterror;  
      int32_t pwm_out1;//pwm输出	
      int32_t pwm_out2;  
      uint16_t avespeed; //当前速度
       
    
          while(1)       
     {         
      //基本变量：
              
   
  
    
      //状态判断以及参数赋值：  
     avespeed=(qd_left_value+qd_right_value)/2;
    

          
     //pi具体实现  

      lefterror = leftspeed - qd_left_value ;
      righterror= rightspeed - qd_right_value ;	
		
	  leftsum+= lefterror ;//积分调节的积分量
      rightsum  += righterror ;
       
	  if(leftsum >= 800)leftsum = 800;
	  if(leftsum <= -400)leftsum = -400;
	  if(rightsum  >= 800) rightsum  = 800;
	  if(rightsum  <= -400)rightsum  = -400;
            
      pwm_out1 =   Kp*lefterror + Ki*leftsum  ;
	  pwm_out2 =   Kp*righterror + Ki*rightsum   ;

	  	
	  
	     
         //防止值超过限度
		if(pwm_out1>=7000)
		{
			pwm_out1=7000;
		}
		if(pwm_out2>=7000)
		{
			pwm_out2=7000;
		}
        
		if(pwm_out1<-7000)
		{
			pwm_out1=-7000;
		}
		if(pwm_out2<-7000)
		{
			pwm_out2=-7000;
		}
	     
	    if(pwm_out1 > 0)
		{
	    FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,pwm_out1 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
		}
		else
		{
		pwm_out1 = -pwm_out1 ;	
		FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
        FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,pwm_out1 );
		}
		
		if(pwm_out2 > 0)
		{
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, pwm_out2 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
		}
		else
		{
		pwm_out2 = -pwm_out2 ;	
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0 ); 
        FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, pwm_out2 );
		}
        
        if(qd_left_value+qd_right_value<1)
        {
         while(1)
         {
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH1 ,0 );
         FTM_PWM_ChangeDuty (HW_FTM0 ,HW_FTM_CH0 ,0);
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH3, 0); 
         FTM_PWM_ChangeDuty (HW_FTM0, HW_FTM_CH2, 0);
         }
        }
        
      }
}



  //测试函数
  void test()
  {
      uint16_t ch;
      uint8_t ch1;
   if(UART_ReadByte(HW_UART0, &ch) == 0)
    {
               
           UART_WriteByte(HW_UART0,ch);//串口接受数据的寄存器是16位的
        
           ch1=(uint8_t)ch;

           UART_WriteByte(HW_UART0,ch);//串口输出接受到的字符
        
               
               
                 switch(ch1)
              {
                  
                case '1':
                    
                 while(1)
                {
//                ov7725_Get_Imge();                    //获取图像
//                img_extract(img, CCDBufferPool ,OV7725_H*(OV7725_W/8));   //将图像保存在数组img中  0表示白色 1表示黑色                 
//                sending_7();
              
                }
                break;
             
                case '2':
                 while(1)
                {
                   
                sending3();
                             
                }     
        
                break;
               
//                  
//                case '3':
//                    CMT_PWM_ChangDuty (600);
//                break;
//                  
//                case '4':   
//                    CMT_PWM_ChangDuty (590);
//                break;
//                   
//                case '5':
//                      CMT_PWM_ChangDuty (580);
//                break;
//                  case '6':
//                    CMT_PWM_ChangDuty (570);
//                break;
//                  
//                case '7':   
//                    CMT_PWM_ChangDuty (560);
//                break;
//                   
//                case '8':
//                      CMT_PWM_ChangDuty (535);
//                break;
                default:
                    break;
             }
     }
  
  
  }