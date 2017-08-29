#ifndef _CANSHU_H_
#define _CANSHU_H_

#include "stdint.h"
#include "stdbool.h"

#define anglemid        807   //813  768
#define hide2_left      anglemid+48         //信标避障的左转打角
#define hide2_right     anglemid-48         //信标避障的右转打角
#define hide_left       anglemid+50         //避障左转打角
#define hide_right      anglemid-50         //避障右转打角
#define acc_left        anglemid+15         //加速段舵机打角左限
#define acc_right       anglemid-15         //加速度段舵机打角右限
#define angleleft       anglemid+75         //舵机左极限
#define angleright      anglemid-75         //舵机右极限

#define ERR_SUM_LIMIT 10000
#define ENCODER_RATE 10
#define BEACON_RIGHT_FIND 1
#define BEACON_RIGHT_LOST 0


//速度
extern uint16_t speedzhuanwan2;
extern uint16_t speedzhuanwan;
extern uint16_t speedjiasu;
extern uint16_t speedxinjiansu;
extern uint16_t speedxinjia;
extern uint16_t speeddazhuan;
extern uint16_t speedbizhang;
extern uint16_t speedxinbi1;
//变量 标志位
extern uint8_t jioushu;
extern uint16_t foreangle;
extern uint8_t forestate;
extern uint16_t anglenow;//舵机实际打角
extern uint8_t count1;//判断经过了第几个信标灯
extern uint8_t count11[5];
extern uint8_t state0[10];
extern uint8_t state;//状态标志位
extern uint16_t speedx;//速度
extern uint16_t anglex;//角度
extern uint8_t target_flag; //目标找到标志位
extern uint16_t target_h;//目标行
extern uint16_t target_l;//目标列
extern uint32_t tt1;//记录时间差
extern uint8_t barrier_h;//障碍物目标行
extern uint8_t barrier_l;//障碍物目标列
extern uint8_t  xideng;
extern uint8_t beacon_right_flag;
//参数
extern uint16_t door_7620;
extern uint16_t stopbizhangh7620;
extern  uint16_t cammid;
extern float anglek;//打角系数
extern int16_t Kd;//舵机打角KD
extern uint16_t count7725;//7725采集像素值
extern bool xinbiaoqieguo;
extern uint16_t xinbiaoqieguo_h;
extern uint16_t acc_stop;
extern float pianchak;//偏差计算系数
extern uint16_t door7620;//7620摄像头阀值
extern float k12;//加速结束时的行坐标计算系数 
extern uint16_t stopbizhangh7725;

/*PID prameter*/
extern int left_speed_disire;
extern int right_speed_desire;

#endif