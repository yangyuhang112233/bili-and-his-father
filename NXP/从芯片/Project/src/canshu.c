#include "head.h"

uint8_t  xideng=100;  //Ϩ��Ƶĸ���

//���Ϸ�ʽ·���滮�� 
uint8_t turn[20]={3,3,3,4,4,4,4,4,4,3,4,4,4,3,3,3,3,3,3,3};  //·���滮�� 1 ������ת�� 2 ������ת�� 3 �����룻 4 �����룻
uint8_t turn_route[20]={0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1};      
    
uint8_t speedjiasu=     58;        //Զ���ű� ֱ�߼���  
uint8_t speedxinjiansu= 20;        //�����ű� ���м��� 
int8_t speedxinbi1=     15;        //�ű���ϼ���    
uint8_t speedxinjia=    28;        //�����ű� �ٶ�̫�� ������
    
uint8_t speeddazhuan=   20;         //�Ҳ����ű��ת���ٶ�    
uint8_t speedbizhang=   2;          //���ϼ���    

uint8_t speedzhuanwan=  18;        //Ѱ���ű�ת���ٶ�
uint8_t speedzhuanwan2=  25;        //����ʱѰ���ű�ת���ٶ�    
      
    
float pianchak=1.1;//��Ե�й�ʱ��ƫ�����ϵ��



float anglek=0.43;//���ϵ��0.48
int16_t Kd=4;//���pd΢��ϵ��
 
//���ϣ�


uint16_t stopbizhangh7725=65;//7725����ʱ�ű�������С�����ֵʱ��������ͨ����

uint16_t door7620=240;//7620����ͷ���ű귧ֵ
uint16_t cammid=160;//С����ǰ����7620ͼ���е�������

uint16_t acc_stop=37;//�й�ʱ���ٽ���ʱ�������� 
float k12=1;
uint16_t xinbiaoqieguo_h=19;//�ű��й�������

//��־λ

uint8_t target_flag; //Ŀ���ҵ���־λ
uint16_t target_h=0;//Ŀ����
uint16_t target_l=0;//Ŀ����
    
uint8_t barrier_h=0;//�ϰ���Ŀ����
uint8_t barrier_l=0;//�ϰ���Ŀ����
 
bool xinbiaoqieguo=0;//�Ƿ�����ű��й�����
uint8_t jioushu=0;//ѭ��������ż����������������7620��ͼ��
uint8_t state=0;//״̬��ʶ
uint8_t state0[10];//��¼��ȥ�ĵ�״̬
uint8_t count1=0;//�жϾ����˵ڼ����ű��
uint8_t count11[5]={0,0,0,0,0};//�жϾ����˵ڼ����ű��
uint16_t count7725=0;//7725���������ظ��� 
uint8_t forestate=7;//֮ǰ��״̬
uint16_t foreangle=0;//��һ��״̬�Ķ�����
uint32_t tt1;//��¼ʱ��

//�˶�����
uint16_t speedx=0;//Ŀ���ٶ�,ʵ��Ŀ���ٶȺ�ʵ���ٶȵĸ���
uint16_t anglex=0;//���Ŀ����
uint16_t anglenow=0;//���ʵ�ʴ��

bool bama[4]={0,0,0,0};//��ȡ���뿪�ص��ĸ�����

