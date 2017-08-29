#include "head.h"
#include "race.h"

uint8_t  xideng=100;  //熄灭灯的个数


uint16_t speedjiasu=     500;        //远离信标 直线加速  
uint16_t speedxinjiansu= 100;        //靠近信标 进行减速 
uint16_t speedxinbi1=     100;        //信标避障减速    
uint16_t speedxinjia=    400;        //靠近信标 速度太慢 而加速
    
uint16_t speeddazhuan=   400;         //找不到信标大转弯速度    
uint16_t speedbizhang=   100;          //避障减速    

uint16_t speedzhuanwan=  200;        //寻找信标转弯速度
uint16_t speedzhuanwan2=  300;        //低速时寻找信标转弯速度    
      
    
float pianchak=1.1;//边缘切过时的偏差计算系数



float anglek=0.43;//打角系数0.48
int16_t Kd=4;//舵机pd微分系数
 
//避障：
uint16_t door_7620=65;//7620避障像素点个数阀值
uint16_t stopbizhangh7620=65;//7620避障时信标行坐标小于这个值时不进行普通避障


uint16_t door7620=DOOR7620;//7620摄像头找信标阀值
uint16_t cammid=160;//小车正前方在7620图像中的列坐标

uint16_t acc_stop=37;//切过时加速结束时的行坐标 
float k12=16;
uint16_t xinbiaoqieguo_h=19;//信标切过行坐标

//标志位

uint8_t target_flag; //目标找到标志位
uint16_t target_h=0;//目标行
uint16_t target_l=0;//目标列
    
uint8_t barrier_h=0;//障碍物目标行
uint8_t barrier_l=0;//障碍物目标列 
uint8_t beacon_right_flag;
bool xinbiaoqieguo=0;//是否进行信标切过避障
uint8_t jioushu=0;//循环次数是偶数还是奇数，用于7620采图像
uint8_t state=0;//状态标识
uint8_t state0[10];//记录过去的的状态
uint8_t count1=0;//判断经过了第几个信标灯
uint8_t count11[5]={0,0,0,0,0};//判断经过了第几个信标灯
uint16_t count7725=0;//7725看到的像素个数 
uint8_t forestate=7;//之前的状态
uint16_t foreangle=0;//上一个状态的舵机打角
uint32_t tt1;//记录时间

//运动量：
uint16_t speedx=0;//目标速度,实现目标速度和实际速度的隔离
uint16_t anglex=0;//舵机目标打角
uint16_t anglenow=0;//舵机实际打角
/*PID prameter*/
int left_speed_disire=0;
int right_speed_desire=0;


