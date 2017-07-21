#ifndef _CANSHU_H_
#define _CANSHU_H_


#include "stdint.h"
#include "stdbool.h"


//¸ÄÓÃ±äÁ¿µÄĞÎÊ½

////¹Ì¶¨¼ÓËÙ¶ÎËÙ¶È£¬»òÕßÓÃº¯Êı
//#define  speedzhuanwan   15  //Ñ°ÕÒĞÅ±ê×ªÍäËÙ¶È
//#define  speedjiasu      30  //Ô¶ÀëĞÅ±ê Ö±Ïß¼ÓËÙ
//#define  speedxinjiansu  10  //¿¿½üĞÅ±ê ½øĞĞ¼õËÙ
//#define  speedxinjia     25  //¿¿½üĞÅ±ê ËÙ¶ÈÌ«Âı ¶ø¼ÓËÙ
//#define  speeddazhuan    15  //ÕÒ²»µ½ĞÅ±ê´ó×ªÍäËÙ¶È
//#define  speedbizhang    10   //±ÜÕÏ¼õËÙ
//#define  speedxinbi      10   //ĞÅ±ê±ÜÕÏ¼õËÙ
//#define  speedxinbijia      15   //ĞÅ±ê±ÜÕÏÊ±Ì«Âı£¬Ôò¼ÓËÙ
//20 34 26 15 10 10  ÀÏµç³Ø
//27 40 18 22 7 9
extern    uint8_t speedxinjia2;          //¿¿½üĞÅ±ê ËÙ¶ÈÌ«Âı ¶ø¼ÓËÙ
extern    uint8_t speedxinjiansu2;        //¿¿½üĞÅ±ê ½øĞĞ¼õËÙ
 extern   uint8_t speedjiasu2;            //Ô¶ÀëĞÅ±ê Ö±Ïß¼ÓËÙ
extern uint8_t  kaiqi;
extern uint8_t speedzhuanwan2;
extern uint8_t  xideng;
extern uint8_t speedzhuanwan;
extern uint8_t speedjiasu;
extern uint8_t speedxinjiansu;
extern uint8_t speedxinjia;
extern uint8_t speeddazhuan;
extern uint8_t speedbizhang;
extern int8_t speedxinbi1;
//extern uint8_t speedxinbijia;
extern int8_t speedxinbi2;
extern uint8_t jioushu;
extern uint16_t foreangle;
extern  uint16_t cammid;
extern int16_t Kd;

extern uint8_t target_flag; //Ä¿±êÕÒµ½±êÖ¾Î»
extern uint16_t target_h;//Ä¿±êĞĞ
extern uint16_t target_l;//Ä¿±êÁĞ
extern uint32_t tt1;//¼ÇÂ¼Ê±¼ä²î
extern uint8_t forestate;
extern uint16_t stopbizhangh7620;//ĞÅ±êĞĞ×ø±êĞ¡ÓÚÕâ¸öÖµÊ±²»½øĞĞÆÕÍ¨±ÜÕ
extern uint16_t stopbizhangh7725;
extern bool stopba;//Í£Ö¹ÆÕÍ¨±ÜÕÏµÄ±êÖ¾Î»
extern uint8_t h7620;  
extern bool barrier;//ÕÏ°­ÎïÕÒµ½±êÖ¾Î»
extern uint8_t barrier_h;//Ä¿±êĞĞ
extern uint8_t barrier_l;//Ä¿±êÁĞ
extern uint16_t anglenow;//¶æ»úÊµ¼Ê´ò½Ç
extern uint8_t count1;//ÅĞ¶Ï¾­¹ıÁËµÚ¼¸¸öĞÅ±êµÆ
extern bool seepoint;//ÅĞ¶ÏÊÇ·ñÔÚ±ÜÕÏºóÕÒ²»µ½ĞÅ±ê
extern bool xinbiaobizhang;//ĞÅ±ê±ÜÕÏ±êÖ¾Î»
extern float k11;
extern float k12;
extern uint8_t turn[20];
extern uint16_t xiangsuzh;
extern uint16_t acc_stop2;//¼ÓËÙ½áÊøÊ±µÄĞĞ×ø±ê
extern uint16_t acc_stop1;
extern uint16_t speedx;//ËÙ¶È
extern uint16_t anglex;//½Ç¶È
extern int c;
extern uint8_t barrier2_h;//ÕÏ°­ÎïÄ¿±êĞĞ
extern uint8_t barrier2_l;//ÕÏ°­ÎïÄ¿±êÁĞ

extern uint16_t anglemid;//¶æ»úÖĞÖµ
extern uint16_t angleleft;//¶æ»ú×ó¼«ÏŞ
extern uint16_t angleright;//¶æ»úÓÒ¼«ÏŞ
extern float anglek;//´ò½ÇÏµÊı
extern uint16_t count7725;//7725²É¼¯ÏñËØÖµ

extern uint8_t state;//×´Ì¬±êÖ¾Î»

extern float pianchak;//Æ«²î¼ÆËãÏµÊı

extern uint8_t xiangsuzhi;
extern uint16_t door7620;//7620ÉãÏñÍ··§Öµ
extern uint16_t jishuwei;
extern uint8_t count11[5];

extern uint16_t xinbiaobizhang_h;//ĞÅ±ê±ÜÕÏĞĞ×ø±ê
extern uint16_t door_7620;//7725±ÜÕÏ·§Öµ
extern bool xinbiaoqieguo;
extern uint16_t hide_left;//±ÜÕÏ×ó×ª´ò½Ç
extern uint16_t hide_right;//±ÜÕÏÓÒ×ª´ò½Ç
extern uint16_t xinbiaoqieguo_h;
extern uint16_t hide2_left;//ĞÅ±ê±ÜÕÏµÄ×ó×ª´ò½Ç
extern uint16_t hide2_right;//ĞÅ±ê±ÜÕÏµÄÓÒ×ª´ò½Ç

extern uint16_t acc_left;//¼ÓËÙ¶Î¶æ»ú´ò½Ç×óÏŞ
extern uint16_t acc_right;//¼ÓËÙ¶È¶Î¶æ»ú´ò½ÇÓÒÏŞ

extern uint16_t acc_stop;//¼ÓËÙ½áÊøÊ±µÄĞĞ×ø±ê

extern uint16_t delay1;//7725±ÜÕÏÑÓÊ±
extern uint16_t delay2;//7620±ÜÕÏÑÓÊ±
extern uint8_t state0[10];
extern bool bama[4];

#endif