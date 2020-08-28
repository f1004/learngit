/*
 * pid.h
 *
 *  Created on: 2020年8月1日
 *      Author: 岑衎远
 */

#ifndef USER_PID_H_
#define USER_PID_H_
#include "common.h"
#include "Vadc/Adc/IfxVadc_Adc.h"
#include "zf_assert.h"
#include "zf_vadc.h"
#include "stdio.h"
void PID_Increase(void);
void speed_pid(int en1,int en2,int s);
void adc_get(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn1, VADC_CHN_enum vadc_chn2, VADC_CHN_enum vadc_chn3, VADC_RES_enum vadc_res);
#define Black_Point 0
#define White_Point 255
#define RowMax	    120  //行数
#define ColumnMax   188 //列数


/*** 外部函数变量申明 ****/
#define COL     188//图像宽度   范围1-752     K60采集不允许超过188
#define ROW     120//图像高度	范围1-480

extern uint8  img[ROW][COL];//定义存储接收图像的数组,CAMERA_H(59-0),CAMERA_W(0-79)

//extern uint8 imgbuff[CAMERA_SIZE];
extern int   AllLose;
extern int BlackEndL;
extern int BlackEndM;
extern int BlackEndR;
extern  int   RightEdge[RowMax+1];
extern  int   LeftEdge[RowMax+1];
extern  int   MiddleLine[RowMax+1];
extern int   LastLine;
extern int   Width[RowMax+1];
extern int   LeftLose;
extern int   RightLose ;
extern unsigned char LoopFlag;

extern  unsigned char LoopRightControlFlag;
extern  unsigned char LoopLeftControlFlag;
extern  int MotivateLoopDlayFlagR;
extern  int MotivateLoopDlayFlagL;
extern  unsigned char MotivateLoopDlayFlagLOK;
extern  unsigned char MotivateLoopDlayFlagROK;
extern  unsigned char OpenLoopExitRepairFlagL;
extern  unsigned char OpenLoopExitRepairFlagR;
extern  unsigned char RightInflectionPointFlag;
extern  unsigned char LeftInflectionPointFlag;

/*** 函数声明 ****/

void FindInflectionPoint();
extern int width;
extern int total;
extern int ad_error1;
void turn(void);
extern char l_flag1;
extern int increase;
extern int error;
extern int out1;
extern int out2;
extern int mid[20];
extern int  ad_value1,pre_value1,last_value1;
extern int  ad_value2,pre_value2,last_value2;
extern int  ad_value3,pre_value3,last_value3;
extern float kp,ki,kd,kp1,ki1;//0.8
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚

#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚

#endif /* USER_PID_H_ */
