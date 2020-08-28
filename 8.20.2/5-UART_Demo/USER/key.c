/*
 * key.c
 *
 *  Created on: 2020年8月3日
 *      Author: 岑衎远
 */


#include "key.h"
#include "common.h"
#include "headfile.h"

//拨码开关状态变量
uint8 sw1_status;
uint8 sw2_status;

//开关状态变量
uint8 key1_status = 1;
uint8 key2_status = 1;
uint8 key3_status = 1;
uint8 key4_status = 1;

//上一次开关状态变量
uint8 key1_last_status;
uint8 key2_last_status;
uint8 key3_last_status;
uint8 key4_last_status;

//开关标志位
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

	    //拨码开关初始化
	    gpio_init(SW1,GPI,0,PULLUP);
	    gpio_init(SW2,GPI,0,PULLUP);




}


void key_get(void)
{
    sw1_status = gpio_get(SW1);
    sw2_status = gpio_get(SW2);

    //在TFT上显示拨码开关状态


    //使用此方法优点在于，不需要使用while(1) 等待，避免处理器资源浪费
    //保存按键状态
    key1_last_status = key1_status;
    key2_last_status = key2_status;
    key3_last_status = key3_status;
    key4_last_status = key4_status;
    //读取当前按键状态
    key1_status = gpio_get(KEY1);
    key2_status = gpio_get(KEY2);
    key3_status = gpio_get(KEY3);
    key4_status = gpio_get(KEY4);
    if(key1_status && !key1_last_status)    key1_flag = 1;
    if(key2_status && !key2_last_status)    key2_flag = 1;
    if(key3_status && !key3_last_status)    key3_flag = 1;
    if(key4_status && !key4_last_status)    key4_flag = 1;


}
