/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"

#pragma section all "cpu0_dsram"


int core0_main(void)
{
	disableInterrupts();
	get_clk();//获取时钟频率  务必保留
	uart_init(UART_0, 9600, UART0_TX_P14_0, UART0_RX_P14_1);//MODE connect to GND
    //用户在此处调用各种初始化函数等
	uart_putchar(UART_0, 0xe8);
	systick_delay_us(STM0, 20);
	uart_putchar(UART_0, 0x02);
	systick_delay_us(STM0, 20);
	uart_putchar(UART_0, 0x70);
	systick_delay_us(STM0, 20);
	uart_putchar(UART_0, 0xbc);
	systick_delay_us(STM0, 20);
    enableInterrupts();

    while (TRUE)
    {
    	uint8 data;
    	int distance;
    	uart_putchar(UART_0, 0xe8);
        systick_delay_us(STM0, 20);
    	uart_putchar(UART_0, 0x02);
    	systick_delay_us(STM0, 20);
    	uart_putchar(UART_0, 0xbc);
    	systick_delay_us(STM0, 20);
    	uart_putchar(UART_0, 0xc9);
    	systick_delay_us(STM0, 20);
    	uart_getchar(UART_0,&data);
    	distance =  data << 8;
    	uart_getchar(UART_0,&data);
    	distance |= data;



    	printf("distance  %d\n", distance);
    	systick_delay_ms(STM0, 100);

    }
}

#pragma section all restore
