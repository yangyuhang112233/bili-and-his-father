#include "head.h"
#include "race.h"

uint8_t  xideng=100;  //Ϩ��Ƶĸ���


uint16_t speedjiasu=     500;        //Զ���ű� ֱ�߼���  
uint16_t speedxinjiansu= 100;        //�����ű� ���м��� 
uint16_t speedxinbi1=     100;        //�ű���ϼ���    
uint16_t speedxinjia=    400;        //�����ű� �ٶ�̫�� ������
    
uint16_t speeddazhuan=   400;         //�Ҳ����ű��ת���ٶ�    
uint16_t speedbizhang=   100;          //���ϼ���    

uint16_t speedzhuanwan=  200;        //Ѱ���ű�ת���ٶ�
uint16_t speedzhuanwan2=  300;        //����ʱѰ���ű�ת���ٶ�    
      
    
float pianchak=1.1;//��Ե�й�ʱ��ƫ�����ϵ��



float anglek=0.43;//���ϵ��0.48
int16_t Kd=4;//���pd΢��ϵ��
 
//���ϣ�
uint16_t door_7620=65;//7620�������ص������ֵ
uint16_t stopbizhangh7620=65;//7620����ʱ�ű�������С�����ֵʱ��������ͨ����


uint16_t door7620=DOOR7620;//7620����ͷ���ű귧ֵ
uint16_t cammid=160;//С����ǰ����7620ͼ���е�������

uint16_t acc_stop=37;//�й�ʱ���ٽ���ʱ�������� 
float k12=16;
uint16_t xinbiaoqieguo_h=19;//�ű��й�������

//��־λ

uint8_t target_flag; //Ŀ���ҵ���־λ
uint16_t target_h=0;//Ŀ����
uint16_t target_l=0;//Ŀ����
    
uint8_t barrier_h=0;//�ϰ���Ŀ����
uint8_t barrier_l=0;//�ϰ���Ŀ���� 
uint8_t beacon_right_flag;
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
/*PID prameter*/
int left_speed_disire=0;
int right_speed_desire=0;


