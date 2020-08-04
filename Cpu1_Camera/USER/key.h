/*
 * key.h
 *
 *  Created on: 2020��8��3��
 *      Author: ��bԶ
 */


#ifndef USER_KEY_H_
#define USER_KEY_H_
#include "common.h"
//���尴������
#define KEY1    P22_0
#define KEY2    P22_1
#define KEY3    P22_2
#define KEY4    P22_3
//���岦�뿪������
#define SW1     P33_12
#define SW2     P33_13


//���뿪��״̬����
extern uint8 sw1_status;
extern uint8 sw2_status;

//����״̬����
extern uint8 key1_status ;
extern uint8 key2_status ;
extern uint8 key3_status ;
extern uint8 key4_status ;

//��һ�ο���״̬����
extern uint8 key1_last_status;
extern uint8 key2_last_status;
extern uint8 key3_last_status;
extern uint8 key4_last_status;

//���ر�־λ
extern uint8 key1_flag;
extern uint8 key2_flag;
extern uint8 key3_flag;
extern uint8 key4_flag;
void key_init(void);
void key_get(void);
void key_init(void);
#endif /* USER_KEY_H_ */
