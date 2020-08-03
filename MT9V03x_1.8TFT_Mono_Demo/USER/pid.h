/*
 * pid.h
 *
 *  Created on: 2020Äê8ÔÂ1ÈÕ
 *      Author: á¯ĞbÔ¶
 */

#ifndef USER_PID_H_
#define USER_PID_H_
void PID_Increase(void);
void speed_pid(int en1,int en2,int s);


extern int increase;
extern int error;
extern int out1;
extern int out2;

#endif /* USER_PID_H_ */
