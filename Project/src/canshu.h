#ifndef _CANSHU_H_
#define _CANSHU_H_


#include "stdint.h"
#include "stdbool.h"

#define SERVO_MIDDLE 772
#define SPEED_RATE 7
#define SPEED_LOW	20

//改用变量的形式

////固定加速段速度，或者用函数
//#define  speedzhuanwan   15  //寻找信标转弯速度
//#define  speedjiasu      30  //远离信标 直线加速
//#define  speedxinjiansu  10  //靠近信标 进行减速
//#define  speedxinjia     25  //靠近信标 速度太慢 而加速
//#define  speeddazhuan    15  //找不到信标大转弯速度
//#define  speedbizhang    10   //避障减速
//#define  speedxinbi      10   //信标避障减速
//#define  speedxinbijia      15   //信标避障时太慢，则加速
//20 34 26 15 10 10  老电池
//27 40 18 22 7 9
extern    uint8_t speedxinjia2;          //靠近信标 速度太慢 而加速
extern    uint8_t speedxinjiansu2;        //靠近信标 进行减速
 extern   uint8_t speedjiasu2;            //远离信标 直线加速
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

extern uint8_t target_flag; //目标找到标志位
extern uint16_t target_h;//目标行
extern uint16_t target_l;//目标列
extern uint32_t tt1;//记录时间差
extern uint8_t forestate;
extern uint16_t stopbizhangh7620;//信标行坐标小于这个值时不进行普通避�
extern uint16_t stopbizhangh7725;
extern bool stopba;//停止普通避障的标志位
extern uint8_t h7620;  
extern bool barrier;//障碍物找到标志位
extern uint8_t barrier_h;//目标行
extern uint8_t barrier_l;//目标列
extern uint16_t anglenow;//舵机实际打角
extern uint8_t count1;//判断经过了第几个信标灯
extern bool seepoint;//判断是否在避障后找不到信标
extern bool xinbiaobizhang;//信标避障标志位
extern float k11;
extern float k12;
extern uint8_t turn[20];
extern uint8_t turn_route[20];
extern uint16_t xiangsuzh;
extern uint16_t acc_stop2;//加速结束时的行坐标
extern uint16_t acc_stop1;
extern uint16_t speedx;//速度
extern uint16_t anglex;//角度
extern int c;
extern uint8_t barrier2_h;//障碍物目标行
extern uint8_t barrier2_l;//障碍物目标列

extern uint16_t anglemid;//舵机中值
extern uint16_t angleleft;//舵机左极限
extern uint16_t angleright;//舵机右极限
extern float anglek;//打角系数
extern uint16_t count7725;//7725采集像素值

extern uint8_t state;//状态标志位

extern float pianchak;//偏差计算系数

extern uint8_t xiangsuzhi;
extern uint16_t door7620;//7620摄像头阀值
extern uint16_t jishuwei;
extern uint8_t count11[5];

extern uint16_t xinbiaobizhang_h;//信标避障行坐标
extern uint16_t door_7620;//7725避障阀值
extern bool xinbiaoqieguo;
extern uint16_t hide_left;//避障左转打角
extern uint16_t hide_right;//避障右转打角
extern uint16_t xinbiaoqieguo_h;
extern uint16_t hide2_left;//信标避障的左转打角
extern uint16_t hide2_right;//信标避障的右转打角

extern uint16_t acc_left;//加速段舵机打角左限
extern uint16_t acc_right;//加速度段舵机打角右限

extern uint16_t acc_stop;//加速结束时的行坐标

extern uint16_t delay1;//7725避障延时
extern uint16_t delay2;//7620避障延时
extern uint8_t state0[10];
extern bool bama[4];

#endif