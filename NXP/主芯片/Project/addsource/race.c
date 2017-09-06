#include "race.h"

uint16_t speedjiasu_list[2]={500,300};	 //远离信标 直线加速 
uint16_t speedxinjiansu_list[2]={100,100};        //靠近信标 进行减速 
uint16_t speedxinbi1_list[2]={100,100};        //信标避障减速    
uint16_t speedxinjia_list[2]={400,300};        //靠近信标 速度太慢 而加速
    
uint16_t speeddazhuan_list[2]={400,300};         //找不到信标大转弯速度    
uint16_t speedbizhang_list[2]={100,100};          //避障减速    

uint16_t speedzhuanwan_list[2]={200,200};        //寻找信标转弯速度
uint16_t speedzhuanwan2_list[2]={300,300};        //低速时寻找信标转弯速度    

uint16_t chasu_low[2]={220,150};
uint16_t chasu_high[2]={320,250};

/*路径规划*/
uint16_t turn[30]={0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
uint16_t turn_route[30]={0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
