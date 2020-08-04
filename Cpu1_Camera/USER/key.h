/*
 * key.h
 *
 *  Created on: 2020年8月3日
 *      Author: 岑衎远
 */


#ifndef USER_KEY_H_
#define USER_KEY_H_
#include "common.h"
//定义按键引脚
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P22_2
#define KEY4    P22_3
//定义拨码开关引脚
#define SW1     P33_12
#define SW2     P33_13


//拨码开关状态变量
extern uint8 sw1_status;
extern uint8 sw2_status;

//开关状态变量
extern uint8 key1_status ;
extern uint8 key2_status ;
extern uint8 key3_status ;
extern uint8 key4_status ;

//上一次开关状态变量
extern uint8 key1_last_status;
extern uint8 key2_last_status;
extern uint8 key3_last_status;
extern uint8 key4_last_status;

//开关标志位
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;
void key_init(void);
void key_get(void);
void key_init(void);
#endif /* USER_KEY_H_ */
