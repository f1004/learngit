/*
 * key.c
 *
 *  Created on: 2020��8��3��
 *      Author: ��bԶ
 */


#include "key.h"
#include "common.h"
#include "headfile.h"

//���뿪��״̬����
uint8 sw1_status;
uint8 sw2_status;

//����״̬����
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//��һ�ο���״̬����
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//���ر�־λ
uint8 key1_flag;
uint8 key2_flag;
uint8 key3_flag;
uint8 key4_flag;
void key_init(void)
{


	    gpio_init(KEY1,GPI,0,PULLUP);
	    gpio_init(KEY2,GPI,0,PULLUP);
	    gpio_init(KEY3,GPI,0,PULLUP);
	    gpio_init(KEY4,GPI,0,PULLUP);

	    //���뿪�س�ʼ��
	    gpio_init(SW1,GPI,0,PULLUP);
	    gpio_init(SW2,GPI,0,PULLUP);




}


void key_get(void)
{
    sw1_status = gpio_get(SW1);
    sw2_status = gpio_get(SW2);

    //��TFT����ʾ���뿪��״̬


    //ʹ�ô˷����ŵ����ڣ�����Ҫʹ��while(1) �ȴ������⴦������Դ�˷�
    //���水��״̬
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    //��ȡ��ǰ����״̬
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);
    key4_status = gpio_get(KEY4);
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;


}
