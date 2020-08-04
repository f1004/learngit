/*
 * pid.h
 *
 *  Created on: 2020年8月1日
 *      Author: 岑衎远
 */

#ifndef USER_PID_H_
#define USER_PID_H_
void PID_Increase(void);
void speed_pid(int en1,int en2,int s);
extern int width;
extern int total;
extern int increase;
extern int error;
extern int out1;
extern int out2;
extern float kp,ki,kd,kp1,ki1;//0.8
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚

#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚

#endif /* USER_PID_H_ */
