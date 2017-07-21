#include "head.h"

 //Á½¸ö²ÎÊı·Ö±ğÎª¶æ»ú´ò½ÇºÍËÙ¶È£¬ÔË¶¯×´Ì¬È«²¿ÔÚÕâÀï¸Ä±ä£¬´Ëº¯ÊıÖĞ¸ù¾İ¶æ»ú´ò½Ç×Ô¶¯ÉèÖÃ²îËÙ
  //×î¼ÑÇé¿öÊÇÖ»´«Èë´ò½Ç£¬×Ô¶¯¸ù¾İ´ò½ÇÉèÖÃ¼«ÏŞËÙ¶È
  //²»´«Èë²ÎÊı£¬¸ù¾İÈ«¾Ö±äÁ¿Ê¹ÓÃº¯Êı£¬¸Ä±äÔË¶¯×´Ì¬Ê±µ÷ÓÃ´Ëº¯Êı
   
  void move()//´ò½Ç£¬ËÙ¶È×÷ÎªÈ«¾Ö±äÁ¿ÒıÓÃ
{        
      //¶æ»ú´ò½Ç¿ØÖÆ
      Servo_Control();
     
    
       //·ÀÖ¹ËÙ¶È¹ıµÍ
             if(qd_left_value+qd_right_value<20)
          {
          speedx=15;
          }
    
      //¸ù¾İ¶æ»ú´ò½ÇÉèÖÃ×óÓÒÁ½¸öÂÖ×ÓµÄ×ªËÙ£¬²¢µ÷ÓÃpidÊµÏÖ×óÓÒÂÖ×ªËÙ
    
    //float proportion[5]={1.41,1.36,1.28,1.24,1.19};//²îËÙ±ÈÀ
     float proportion[5]={1.4,1.15,1,1,1};//²îËÙ±ÈÀı
    //²îËÙ¿ÉÄÜµ¼ÖÂÔÚ»¬µÄ³¡µØ´ò»¬
     
    uint16_t leftspeed,rightspeed;//×óÓÒÂÖÉè¶¨ËÙ¶È
    uint16_t anglec;//¸ù¾İ½Ç¶ÈÑ¡Ôñ²îËÙ
     
    
    //±¾À´Ã»ÓĞ²îËÙ£¬Ğ§¹ûÒ²»¹ºÃ
             if(anglenow>anglemid-51&&anglenow<anglemid+51) 
      {
        rightspeed=speedx;
        leftspeed=speedx;         
      }        
      else
      {        
       anglec=anglenow/10;
                 
        if(anglec<46)  //ÓÒ×ª
        {
         anglec=anglec-41; 
         rightspeed=speedx; 
         leftspeed=proportion[anglec]*speedx;       
        }
        if(anglec>55)           //×ó×ª
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
        Motor_Control(leftspeed,rightspeed);//ÉÏÃæÊÇËÙ¶ÈÑ¡Ôñ£¬ÕâÀïÊÇËÙ¶ÈÊµÏÖ
     
       }
       
       
       //ËÙ¶È¿ØÖÆÖ»ÔÚÕâÀïºÍÏÂ±ßÊµÏÖ
      //  Motor_Control(leftspeed,rightspeed);//ÉÏÃæÊÇËÙ¶ÈÑ¡Ôñ£¬ÕâÀïÊÇËÙ¶ÈÊµÏÖ
     
       
       //ÆÕÍ¨±ÜÕÏÉèÖÃÑÓÊ±
        if(state==1)
       {           
           DelayMs(20);
           if(qd_left_value +qd_right_value<35) DelayMs(10);
       } 

      
          
       //Èç¹ûÊÇĞÅ±ê±ÜÕÏ×´Ì¬ÄÇÃ´ÉèÖÃÒ»¶¨ÑÓÊ±£¬ÑÓÊ±ÄÚ·½ÏòËÙ¶È²»±ä£¬Ê¹Ğ¡³µ¾­¹ı²¢Ï¨ÃğĞÅ±ê
    
       if(state==3)
       {
                for(int co1=0;co1<3;co1++)
            {              
             Motor_Control(leftspeed,rightspeed);
             DelayMs(delay2);
            }     
       }  
       //×îºÃ»¹ÊÇÍ¨¹ıÉèÖÃÈÃĞÅ±êµÆ´¦ÔÚÍ¼ÏñµÄÄ³Ò»Î»ÖÃ
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
  
  