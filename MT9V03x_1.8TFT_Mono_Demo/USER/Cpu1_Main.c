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
#include "isr.h"
#include "SEEKFREE_MT9V03X.h"
#pragma section all "cpu1_dsram"


int core1_main(void)
{
	disableInterrupts();
	//Ks103_init();


    enableInterrupts();

    while (TRUE)
    {
    	//printf("time is %d\n",time);
    	//systick_delay_ms(STM1,1000);




    }
}

#pragma section all restore
