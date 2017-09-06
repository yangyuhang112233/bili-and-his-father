#include "head.h"

uint8_t  xideng=100;  //熄灭灯的个数

//避障方式路径规划： 
uint8_t turn[20]={3,3,3,4,4,4,4,4,4,3,4,4,4,3,3,3,3,3,3,3};  //路径规划： 1 避障左转； 2 避障右转； 3 左切入； 4 右切入；
uint8_t turn_route[20]={0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1};      
    
uint8_t speedjiasu=     58;        //远离信标 直线加速  
uint8_t speedxinjiansu= 20;        //靠近信标 进行减速 
int8_t speedxinbi1=     15;        //信标避障减速    
uint8_t speedxinjia=    28;        //靠近信标 速度太慢 而加速
    
uint8_t speeddazhuan=   20;         //找不到信标大转弯速度    
uint8_t speedbizhang=   2;          //避障减速    

uint8_t speedzhuanwan=  18;        //寻找信标转弯速度
uint8_t speedzhuanwan2=  25;        //低速时寻找信标转弯速度    
      
    
float pianchak=1.1;//边缘切过时的偏差计算系数



float anglek=0.43;//打角系数0.48
int16_t Kd=4;//舵机pd微分系数
 
//避障：


uint16_t stopbizhangh7725=65;//7725避障时信标行坐标小于这个值时不进行普通避障

uint16_t door7620=240;//7620摄像头找信标阀值
uint16_t cammid=160;//小车正前方在7620图像中的列坐标

uint16_t acc_stop=37;//切过时加速结束时的行坐标 
float k12=1;
uint16_t xinbiaoqieguo_h=19;//信标切过行坐标

//标志位

uint8_t target_flag; //目标找到标志位
uint16_t target_h=0;//目标行
uint16_t target_l=0;//目标列
    
uint8_t barrier_h=0;//障碍物目标行
uint8_t barrier_l=0;//障碍物目标列
 
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

bool bama[4]={0,0,0,0};//读取拔码开关的四个输入

