/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
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
#pragma section all "cpu0_dsram"

int16 speed;

int core0_main(void)
{
	disableInterrupts();
	get_clk();//��ȡʱ��Ƶ��  ��ر���

    //�û��ڴ˴����ø��ֳ�ʼ��������
	//��һ������ ��ʾѡ��ʹ�õĶ�ʱ��
	//�ڶ������� ��ʾѡ��ļ�������    ���������뷽�����Ų��ɽ���
	//���������� ��ʾѡ��ķ�������
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    enableInterrupts();

    while (TRUE)
    {
    	speed = gpt12_get(GPT12_T2);
    	gpt12_clear(GPT12_T2);
    	//��ӡ�ɼ����ı��������� ��FSS����
    	printf("speed: %d\n", speed);
    	systick_delay_ms(STM0, 100);
        //speed
		
    	//��ת������Խ�� FSS������ʾ������Խ����ת��ֵΪ����������ֵΪ��
    }
}

#pragma section all restore
