/*
 * pid.h
 *
 *  Created on: 2020��8��1��
 *      Author: ��bԶ
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
#define MOTOR1_A   ATOM0_CH0_P21_2   //����1�����תPWM����      ���1��������
#define MOTOR1_B   ATOM0_CH1_P21_3   //����1�����תPWM����

#define MOTOR2_A   ATOM0_CH2_P21_4   //����2�����תPWM����
#define MOTOR2_B   ATOM0_CH3_P21_5   //����2�����תPWM����

#endif /* USER_PID_H_ */
