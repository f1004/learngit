/*
 * pid.h
 *
 *  Created on: 2020��8��1��
 *      Author: ��bԶ
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
#define RowMax	    120  //����
#define ColumnMax   188 //����


/*** �ⲿ������������ ****/
#define COL     188//ͼ����   ��Χ1-752     K60�ɼ���������188
#define ROW     120//ͼ��߶�	��Χ1-480

extern uint8  img[ROW][COL];//����洢����ͼ�������,CAMERA_H(59-0),CAMERA_W(0-79)

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

/*** �������� ****/

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
#define MOTOR1_A   ATOM0_CH0_P21_2   //����1�����תPWM����      ���1��������
#define MOTOR1_B   ATOM0_CH1_P21_3   //����1�����תPWM����

#define MOTOR2_A   ATOM0_CH2_P21_4   //����2�����תPWM����
#define MOTOR2_B   ATOM0_CH3_P21_5   //����2�����תPWM����

#endif /* USER_PID_H_ */
