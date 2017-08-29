#ifndef _RACE_H
#define _RACE_H

#include "stdint.h"

/*差速的参数，外轮和内轮速度*/
#define CHASU_LOW 220
#define CHASU_HIGH 320

/*摄像头参数*/
#define BIZHANG_DELTA 20
#define BIZHANG_LIMIT 145
#define DOOR7620 228

/*切灯的偏差*/
#define PIANCHA_LEFT 1.15
#define PIANCHA_RIGHT 1.3

/*经过多少灯停下 0表示不停*/
#define PASS_BEACONS 0

/*倒车的灵敏度，数值越大倒车越不灵敏*/
#define DAOCHE_YUSAI 5
#define DAOCHE_JUESAI 10

/*速度level*/
#define SPEED_LEVEL 2

/*路径规划*/
#define TURN_LEFT_ROUTE 0
#define TURN_RIGHT_ROUTE 1

extern uint16_t speedjiasu_list[SPEED_LEVEL];	 //远离信标 直线加速 
extern uint16_t speedxinjiansu_list[SPEED_LEVEL];        //靠近信标 进行减速 
extern uint16_t speedxinbi1_list[SPEED_LEVEL];        //信标避障减速    
extern uint16_t speedxinjia_list[SPEED_LEVEL];        //靠近信标 速度太慢 而加速
    
extern uint16_t speeddazhuan_list[SPEED_LEVEL];         //找不到信标大转弯速度    
extern uint16_t speedbizhang_list[SPEED_LEVEL];          //避障减速    

extern uint16_t speedzhuanwan_list[SPEED_LEVEL];        //寻找信标转弯速度
extern uint16_t speedzhuanwan2_list[SPEED_LEVEL];        //低速时寻找信标转弯速度

extern uint16_t chasu_low[2];
extern uint16_t chasu_high[2];

extern uint16_t turn[30];
extern uint16_t turn_route[30];

#endif