#include "head.h"

uint8_t  xideng=20;  //Ϩ��Ƶĸ���
uint8_t  kaiqi=0; 
//������ 
// ��ֵ510   �������415  �������610
//4 2 5 3 1 4 2 5 1 3

//���Ϸ�ʽ·���滮�� 
uint8_t turn[20]={3,3,3,4,4,4,4,3,3,3,3,4,3,3,3,3,3,3,3,3};  //·���滮�� 1 ������ת�� 2 ������ת�� 3 �����룻 4 �����룻

//uint8_t turn[20]={1,1,1,2,2,2,2,1,1,1,1,2,3,1,1,1,3,3,3,3};  //·���滮�� 1 ������ת�� 2 ������ת�� 3 �����룻 4 �����룻

    
uint8_t turn11[20]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};  //��turnΪ3��4������£������ű������Ҳ����ű꣬�Ƿ����ת
    
uint8_t delay[20]={4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4};  //��ͬ�ĵ�lookfor��ֱ����ʱ
    
uint8_t bizhangkaiguan[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  //�Ƿ����ñ���

uint8_t speed1[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed2[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};     
uint8_t speed3[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed4[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed5[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
uint8_t speed6[20]={1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};  
   
    
//  //�����ٶȣ�����   ʼ�ձ���һ�����ȶ����е�  
uint8_t speedzhuanwan=  15;        //Ѱ���ű�ת���ٶ�
uint8_t speedzhuanwan2=  25;        //����ʱѰ���ű�ת���ٶ�    
    
//�ű��й����ٶ�   
//uint8_t speedjiasu=     45;            //Զ���ű� ֱ�߼���  
//uint8_t speedxinjiansu= 7;        //�����ű� ���м���    
//uint8_t speedxinjia=    28;          //�����ű� �ٶ�̫�� ������
//uint8_t speeddazhuan=   20;         //�Ҳ����ű��ת���ٶ�    
//uint8_t speedbizhang=   6;          //���ϼ���    
//int8_t speedxinbi1=     -5;            //�ű���ϼ���

//�ű���ϵ��ٶ�  �Ƚ��� ������    
//uint8_t speedjiasu=     45;            //Զ���ű� ֱ�߼���  
//uint8_t speedxinjiansu= 20;        //�����ű� ���м���    
//uint8_t speedxinjia=    28;          //�����ű� �ٶ�̫�� ������
//uint8_t speeddazhuan=   20;         //�Ҳ����ű��ת���ٶ�    
//uint8_t speedbizhang=   6;          //���ϼ���    
//int8_t speedxinbi1=     10;            //�ű���ϼ���
//     

//    
//uint8_t speedxinjia2=    28;          //�����ű� �ٶ�̫�� ������
//uint8_t speedxinjiansu2= 18;        //�����ű� ���м���
//uint8_t speedjiasu2=     45;            //Զ���ű� ֱ�߼���
//int8_t speedxinbi2=     12;            //�ű���ϼ���
 
uint8_t speedjiasu=     58;            //Զ���ű� ֱ�߼���  
uint8_t speedxinjiansu= 20;        //�����ű� ���м���    
uint8_t speedxinjia=    28;          //�����ű� �ٶ�̫�� ������
uint8_t speeddazhuan=   20;         //�Ҳ����ű��ת���ٶ�    
uint8_t speedbizhang=   2;          //���ϼ���    
int8_t speedxinbi1=     10;            //�ű���ϼ���
     

    
uint8_t speedxinjia2=    28;          //�����ű� �ٶ�̫�� ������
uint8_t speedxinjiansu2= 18;        //�����ű� ���м���
uint8_t speedjiasu2=     50;            //Զ���ű� ֱ�߼���
int8_t speedxinbi2=     7;            //�ű���ϼ���
     
 

float pianchak=0.9;//��Ե�й�ʱ��ƫ�����ϵ��

//�����ǲ�����
uint16_t anglemid=SERVO_MIDDLE;//�����ֵ
uint16_t angleleft=SERVO_MIDDLE+70;//������� 
uint16_t angleright=SERVO_MIDDLE-70;//����Ҽ��� 

uint16_t hide_left=SERVO_MIDDLE+50;//���ϵ���ת���+50
uint16_t hide_right=SERVO_MIDDLE-50;//���ϵ���ת���-50

uint16_t acc_left=SERVO_MIDDLE+15;//���ٶζ���������+15
uint16_t acc_right=SERVO_MIDDLE-15;//���ٶȶζ���������-15

uint16_t hide2_left=SERVO_MIDDLE+35;//�ű���ϵ���ת���    +35  �й��ű겻ʹ��
uint16_t hide2_right=SERVO_MIDDLE-35;//�ű���ϵ���ת���-35

float anglek=0.43;//���ϵ��0.48
int16_t Kd=4;//���pd΢��ϵ�� 

//���ϣ�
uint16_t door_7620=65;//7620�������ص������ֵ
uint8_t h7620=45;//7620���Ͼ���

uint16_t delay1=13;//��ͨ������ʱ
uint16_t delay2=5;//�ű������ʱ

uint16_t stopbizhangh7620=65;//7620����ʱ�ű�������С�����ֵʱ��������ͨ����

uint16_t stopbizhangh7725=70;//7725����ʱ�ű�������С�����ֵʱ��������ͨ����





uint16_t door7620=240;//7620����ͷ���ű귧ֵ

uint32_t tt1;//��¼ʱ��


uint8_t xiangsuzhi=80;//�ϰ�����7620ͼ���е�����ֵ   ����Ӧ�㷨��ʹ��

uint16_t cammid=161;//С����ǰ����7620ͼ���е�������

//���������� ���ٺ���
uint16_t xinbiaobizhang_h=29;//�ű����������   
float k11=1;

////���ٺ���
//uint16_t xinbiaobizhang_h=30;//�ű����������   
//float k11=1.15;

int c=0;

uint16_t acc_stop2=38;//���ٽ���ʱ��������  
float k12=1.4;


uint16_t acc_stop1=20;//���ٽ���ʱ�������� 
uint16_t xinbiaoqieguo_h=14;//�ű��й�������

//��־λ

uint16_t jishuwei=0;//���ڼ�¼�����ѭ������
uint8_t jioushu=0;//ѭ��������ż����������������7620��ͼ��


uint8_t target_flag; //Ŀ���ҵ���־λ



uint16_t target_h=0;//Ŀ����
uint16_t target_l=0;//Ŀ����

bool barrier =0;//ǰ���Ƿ����ϰ����־λ
    
uint8_t barrier_h=0;//�ϰ���Ŀ����
uint8_t barrier_l=0;//�ϰ���Ŀ����

uint8_t barrier2_h=0;//�ϰ���Ŀ����
uint8_t barrier2_l=0;//�ϰ���Ŀ����


bool stopba;//ֹͣ��ͨ���ϵı�־λ 
bool xinbiaobizhang=0;//�Ƿ�����ű����
bool xinbiaoqieguo=0;//�Ƿ�����ű����

uint8_t state=0;//״̬��ʶλ
  

bool seepoint=0;//�ж��Ƿ����ű���Ϲ����п����ű�
uint8_t count1=0;//�жϾ����˵ڼ����ű��
uint8_t count11[5]={0,0,0,0,0};//�жϾ����˵ڼ����ű��
uint8_t state0[10];//��¼��ȥ�ĵ�״̬
  
uint16_t count7725=0;//7725���������ظ��� 
 
uint8_t forestate=7;//֮ǰ��״̬
uint16_t foreangle=0;//��һ��״̬�Ķ�����




//�˶�����
uint16_t speedx=0;//Ŀ���ٶ�,ʵ��Ŀ���ٶȺ�ʵ���ٶȵĸ���
uint16_t anglex=0;//���Ŀ����
uint16_t anglenow=0;//���ʵ�ʴ��,�����ǰ��ֻ�ı���Ŀ���ǣ�ʵ�ʴ���ڶ��pd�иı䡣ʵ��Ŀ��ֵ��ʵ��ֵ�ĸ���

bool bama[4]={0,0,0,0};//��ȡ���뿪�ص��ĸ�����

