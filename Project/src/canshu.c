#include "head.h"

uint8_t  xideng=20;  //熄灭灯的个数
uint8_t  kaiqi=0; 
//参数： 
// 中值510   打角右限415  打角左限610
//4 2 5 3 1 4 2 5 1 3

//避障方式路径规划： 
uint8_t turn[20]={3,3,3,4,4,4,4,3,3,3,3,4,3,3,3,3,3,3,3,3};  //路径规划： 1 避障左转； 2 避障右转； 3 左切入； 4 右切入；

//uint8_t turn[20]={1,1,1,2,2,2,2,1,1,1,1,2,3,1,1,1,3,3,3,3};  //路径规划： 1 避障左转； 2 避障右转； 3 左切入； 4 右切入；

    
uint8_t turn11[20]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};  //在turn为3或4的情况下，经过信标后，如果找不到信标，是否反向大转
    
uint8_t delay[20]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};  //不同的灯lookfor后直线延时
    
uint8_t bizhangkaiguan[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  //是否设置避障

uint8_t speed1[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed2[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};     
uint8_t speed3[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed4[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed5[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed6[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
   
    
//  //设置速度：稳速   始终保留一组能稳定运行的  
uint8_t speedzhuanwan=  15;        //寻找信标转弯速度
uint8_t speedzhuanwan2=  25;        //低速时寻找信标转弯速度    
    
//信标切过的速度   
//uint8_t speedjiasu=     45;            //远离信标 直线加速  
//uint8_t speedxinjiansu= 7;        //靠近信标 进行减速    
//uint8_t speedxinjia=    28;          //靠近信标 速度太慢 而加速
//uint8_t speeddazhuan=   20;         //找不到信标大转弯速度    
//uint8_t speedbizhang=   6;          //避障减速    
//int8_t speedxinbi1=     -5;            //信标避障减速

//信标避障的速度  比较稳 不够快    
//uint8_t speedjiasu=     45;            //远离信标 直线加速  
//uint8_t speedxinjiansu= 20;        //靠近信标 进行减速    
//uint8_t speedxinjia=    28;          //靠近信标 速度太慢 而加速
//uint8_t speeddazhuan=   20;         //找不到信标大转弯速度    
//uint8_t speedbizhang=   6;          //避障减速    
//int8_t speedxinbi1=     10;            //信标避障减速
//     

//    
//uint8_t speedxinjia2=    28;          //靠近信标 速度太慢 而加速
//uint8_t speedxinjiansu2= 18;        //靠近信标 进行减速
//uint8_t speedjiasu2=     45;            //远离信标 直线加速
//int8_t speedxinbi2=     12;            //信标避障减速
 
uint8_t speedjiasu=     58;            //远离信标 直线加速  
uint8_t speedxinjiansu= 20;        //靠近信标 进行减速    
uint8_t speedxinjia=    28;          //靠近信标 速度太慢 而加速
uint8_t speeddazhuan=   20;         //找不到信标大转弯速度    
uint8_t speedbizhang=   2;          //避障减速    
int8_t speedxinbi1=     10;            //信标避障减速
     

    
uint8_t speedxinjia2=    28;          //靠近信标 速度太慢 而加速
uint8_t speedxinjiansu2= 18;        //靠近信标 进行减速
uint8_t speedjiasu2=     50;            //远离信标 直线加速
int8_t speedxinbi2=     7;            //信标避障减速
     
 

float pianchak=0.9;//边缘切过时的偏差计算系数

//舵机打角参数：
uint16_t anglemid=SERVO_MIDDLE;//舵机中值
uint16_t angleleft=SERVO_MIDDLE+70;//舵机左极限 
uint16_t angleright=SERVO_MIDDLE-70;//舵机右极限 

uint16_t hide_left=SERVO_MIDDLE+50;//避障的左转打角+50
uint16_t hide_right=SERVO_MIDDLE-50;//避障的右转打角-50

uint16_t acc_left=SERVO_MIDDLE+15;//加速段舵机打角左限+15
uint16_t acc_right=SERVO_MIDDLE-15;//加速度段舵机打角右限-15

uint16_t hide2_left=SERVO_MIDDLE+35;//信标避障的左转打角    +35  切过信标不使用
uint16_t hide2_right=SERVO_MIDDLE-35;//信标避障的右转打角-35

float anglek=0.43;//打角系数0.48
int16_t Kd=4;//舵机pd微分系数 

//避障：
uint16_t door_7620=65;//7620避障像素点个数阀值
uint8_t h7620=45;//7620避障距离

uint16_t delay1=13;//普通避障延时
uint16_t delay2=5;//信标避障延时

uint16_t stopbizhangh7620=65;//7620避障时信标行坐标小于这个值时不进行普通避障

uint16_t stopbizhangh7725=70;//7725避障时信标行坐标小于这个值时不进行普通避障





uint16_t door7620=240;//7620摄像头找信标阀值

uint32_t tt1;//记录时间


uint8_t xiangsuzhi=80;//障碍物在7620图像中的像素值   自适应算法不使用

uint16_t cammid=161;//小车正前方在7620图像中的列坐标

//避障行坐标 低速好用
uint16_t xinbiaobizhang_h=29;//信标避障行坐标   
float k11=1;

////快速好用
//uint16_t xinbiaobizhang_h=30;//信标避障行坐标   
//float k11=1.15;

int c=0;

uint16_t acc_stop2=38;//加速结束时的行坐标  
float k12=1.4;


uint16_t acc_stop1=20;//加速结束时的行坐标 
uint16_t xinbiaoqieguo_h=14;//信标切过行坐标

//标志位

uint16_t jishuwei=0;//用于记录程序的循环次数
uint8_t jioushu=0;//循环次数是偶数还是奇数，用于7620采图像


uint8_t target_flag; //目标找到标志位



uint16_t target_h=0;//目标行
uint16_t target_l=0;//目标列

bool barrier =0;//前方是否有障碍物标志位
    
uint8_t barrier_h=0;//障碍物目标行
uint8_t barrier_l=0;//障碍物目标列

uint8_t barrier2_h=0;//障碍物目标行
uint8_t barrier2_l=0;//障碍物目标列


bool stopba;//停止普通避障的标志位 
bool xinbiaobizhang=0;//是否进行信标避障
bool xinbiaoqieguo=0;//是否进行信标避障

uint8_t state=0;//状态标识位
  

bool seepoint=0;//判断是否在信标避障过程中看到信标
uint8_t count1=0;//判断经过了第几个信标灯
uint8_t count11[5]={0,0,0,0,0};//判断经过了第几个信标灯
uint8_t state0[10];//记录过去的的状态
  
uint16_t count7725=0;//7725看到的像素个数 
 
uint8_t forestate=7;//之前的状态
uint16_t foreangle=0;//上一个状态的舵机打角




//运动量：
uint16_t speedx=0;//目标速度,实现目标速度和实际速度的隔离
uint16_t anglex=0;//舵机目标打角
uint16_t anglenow=0;//舵机实际打角,程序的前段只改变舵机目标打角，实际打角在舵机pd中改变。实现目标值和实际值的隔离

bool bama[4]={0,0,0,0};//读取拔码开关的四个输入

