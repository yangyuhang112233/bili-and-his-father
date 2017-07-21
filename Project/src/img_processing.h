#ifndef _IMG_PROCESSING_H_
#define _IMG_PROCESSING_H_

#include <stdint.h>
#define Num 0xf4
//#define fabs(Number) (((Number) < 0)?(-(Number)):(Number))
#define Avoid_Obs           (1)
#define No_Obs_Found        (2)
#define Remote_Turn_left    (3)
#define Remote_Turn_right   (4)
#define JustGofor_Target    (5)
#define Go_Forward          (6)
#define Right_Target_Found  (7)
#define Left_Target_Found   (8)
#define Start_For_Target    (9)
#define Cam_1_ToRight       (10)
#define Cam_1_ToLeft        (11)
#define Speed_Down_For_Target (12)
#define Speed_Up_Left       (13)
#define Speed_Up_Right      (14)

extern uint8_t Run_mode;

extern uint8_t target_l_flag;
extern uint8_t target_r_flag;

extern uint16_t desire_l ;
extern uint16_t desire_l_back ;

extern uint16_t count_target;

/*跳线搜索函数*/


/*正常边线搜索模式*/


/*外部调用中心线搜索函数*/
void Track_Search(void) ;
void Track_Search2(void) ;//后摄像头处理
/*图片串口发送函数*/
void sending(void);
void sending2(void);
void sending3(void);
void sending_7(void);

void getimage(void);
#endif
