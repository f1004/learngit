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
#include "SEEKFREE_MT9V03X.h"
void PID_Increase(void);
void speed_pid(int en1,int en2,int s);
int adc_get(VADCN_enum vadc_n, VADC_CHN_enum vadc_chn, VADC_RES_enum vadc_res);
extern int width;
extern int total;
extern int increase;
extern int error;
extern int out1;
extern int out2;
extern int mid[20];
extern float kp,ki,kd,kp1,ki1;//0.8
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚

#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚


/*********define for SearchCenterBlackline**********/
#define RowMax	    120  //行数
#define ColumnMax   160 //列数
extern int   MiddleLine[RowMax+1];
void Search_Center_Blackline(void);
extern uint8 Image_Array[MT9V03X_H][MT9V03X_W];

#define Black_Point 0
#define White_Point 255
#endif /* USER_PID_H_ */
