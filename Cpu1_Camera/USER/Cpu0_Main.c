/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "headfile.h"
#include "isr.h"
#pragma section all "cpu0_dsram"


int core0_main(void)
{   int distance;
	disableInterrupts();
	//Ks103_init();
	get_clk();//��ȡʱ��Ƶ��  ��ر���

    enableInterrupts();

    while (TRUE)
    {
    	 if(Flag_10ms)
    	 {
    	//distance=Ks103_getdistance();
    	//printf("distance is %d\n", distance);
    	Flag_10ms=0;

    	 }




    }
}

#pragma section all restore
