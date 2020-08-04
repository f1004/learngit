/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		isr
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "isr_config.h"
#include "isr.h"
#include "headfile.h"
#include "isr.h"
#include "img.h"
#include <stdlib.h>
#include "pid.h"
#include "key.h"
#include "Ks103.h"
//��isr.c���жϺ�������������ĵڶ��������̶�Ϊ0���벻Ҫ���ģ���ʹ����CPU1�����ж�Ҳ��Ҫ���ģ���ҪCPU1�����ж�ֻ��Ҫ��isr_config.h���޸Ķ�Ӧ�ĺ궨�弴��
extern int16 encoder1;
extern int16 encoder2;
#define MOTOR1_A   ATOM0_CH0_P21_2   //����1�����תPWM����      ���1��������
#define MOTOR1_B   ATOM0_CH1_P21_3   //����1�����תPWM����

#define MOTOR2_A   ATOM0_CH2_P21_4   //����2�����תPWM����
#define MOTOR2_B   ATOM0_CH3_P21_5   //����2�����תPWM����
extern int32 speed1_power;
extern int32 speed2_power;

extern int set_speed;
extern int limit_increase;
extern int limit_out;
extern int left_pwm,right_pwm;
extern int speed_base;





//PIT�жϺ���  ʾ��

char Flag_10ms;
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	enableInterrupts();//�����ж�Ƕ��
	PIT_CLEAR_FLAG(CCU6_0, PIT_CH0);

	encoder1 = gpt12_get(GPT12_T2);
	encoder2 = -gpt12_get(GPT12_T4);
	gpt12_clear(GPT12_T2);
	gpt12_clear(GPT12_T4);



	        speed_pid(encoder1,encoder2,set_speed);
	        if(out1>=limit_out)out1=limit_out;
	        if(out1<=-limit_out)out1=-limit_out;
	        if(out2>=limit_out)out2=limit_out;
	        if(out2<=-limit_out)out2=-limit_out;
	//    	        increase=0;
//	        speed1_power = out1+increase;
//	        speed2_power = out2-increase;
//	        speed1_power = out1;
//	        speed2_power = out2;

	        if(speed1_power>=0)speed1_power=speed1_power+left_pwm;
	        if(speed1_power<0)speed1_power=speed1_power-left_pwm;
	        if(speed2_power>=0)speed2_power=speed2_power+right_pwm;
	        if(speed2_power<0)speed2_power=speed2_power-right_pwm;

	        if(speed1_power>=4000)speed1_power=4000;
	        if(speed1_power<=-4000)speed1_power=-4000;
	        if(speed2_power>=4000)speed2_power=4000;
	        if(speed2_power<=-4000)speed2_power=-4000;
	        if(0<=speed1_power) //���1   ��ת ����ռ�ձ�Ϊ �ٷ�֮ (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
	                {
	                    pwm_duty(MOTOR1_A, speed1_power);
	                    pwm_duty(MOTOR1_B, 0);
	                }
	                else                //���1   ��ת
	                {
	                    pwm_duty(MOTOR1_A, 0);
	                    pwm_duty(MOTOR1_B, -speed1_power);
	                }

	                if(0<=speed2_power) //���2   ��ת
	                {
	                    pwm_duty(MOTOR2_A, speed2_power);
	                    pwm_duty(MOTOR2_B, 0);
	                }
	                else                //���2   ��ת
	                {
	                    pwm_duty(MOTOR2_A, 0);
	                    pwm_duty(MOTOR2_B, -speed2_power);
	                }
	Flag_10ms=1;


}


IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
	enableInterrupts();//�����ж�Ƕ��
	PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);

}

IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
{
	enableInterrupts();//�����ж�Ƕ��
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);

}

IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
	enableInterrupts();//�����ж�Ƕ��
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);

}




IFX_INTERRUPT(eru_ch0_ch4_isr, 0, ERU_CH0_CH4_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
	if(GET_GPIO_FLAG(ERU_CH0_REQ4_P10_7))//ͨ��0�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH0_REQ4_P10_7);
	}

	if(GET_GPIO_FLAG(ERU_CH4_REQ13_P15_5))//ͨ��4�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH4_REQ13_P15_5);
	}
}

IFX_INTERRUPT(eru_ch1_ch5_isr, 0, ERU_CH1_CH5_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
	if(GET_GPIO_FLAG(ERU_CH1_REQ5_P10_8))//ͨ��1�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH1_REQ5_P10_8);
	}

	if(GET_GPIO_FLAG(ERU_CH5_REQ1_P15_8))//ͨ��5�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH5_REQ1_P15_8);
	}
}

//��������ͷpclk����Ĭ��ռ���� 2ͨ�������ڴ���DMA��������ﲻ�ٶ����жϺ���
//IFX_INTERRUPT(eru_ch2_ch6_isr, 0, ERU_CH2_CH6_INT_PRIO)
//{
//	enableInterrupts();//�����ж�Ƕ��
//	if(GET_GPIO_FLAG(ERU_CH2_REQ7_P00_4))//ͨ��2�ж�
//	{
//		CLEAR_GPIO_FLAG(ERU_CH2_REQ7_P00_4);
//
//	}
//	if(GET_GPIO_FLAG(ERU_CH6_REQ9_P20_0))//ͨ��6�ж�
//	{
//		CLEAR_GPIO_FLAG(ERU_CH6_REQ9_P20_0);
//
//	}
//}



IFX_INTERRUPT(eru_ch3_ch7_isr, 0, ERU_CH3_CH7_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
	if(GET_GPIO_FLAG(ERU_CH3_REQ6_P02_0))//ͨ��3�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH3_REQ6_P02_0);
		if		(1 == camera_type)	mt9v03x_vsync();
		else if	(3 == camera_type)	ov7725_vsync();

	}
	if(GET_GPIO_FLAG(ERU_CH7_REQ16_P15_1))//ͨ��7�ж�
	{
		CLEAR_GPIO_FLAG(ERU_CH7_REQ16_P15_1);

	}
}



IFX_INTERRUPT(dma_ch5_isr, 0, ERU_DMA_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��

	if		(1 == camera_type)	mt9v03x_dma();
	else if	(3 == camera_type)	ov7725_dma();
}


//�����жϺ���  ʾ��
IFX_INTERRUPT(uart0_tx_isr, 0, UART0_TX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrTransmit(&uart0_handle);
}
IFX_INTERRUPT(uart0_rx_isr, 0, UART0_RX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrReceive(&uart0_handle);
}
IFX_INTERRUPT(uart0_er_isr, 0, UART0_ER_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrError(&uart0_handle);
}

//����1Ĭ�����ӵ�����ͷ���ô���
IFX_INTERRUPT(uart1_tx_isr, 0, UART1_TX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrTransmit(&uart1_handle);
}
IFX_INTERRUPT(uart1_rx_isr, 0, UART1_RX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrReceive(&uart1_handle);
    mt9v03x_uart_callback();
}
IFX_INTERRUPT(uart1_er_isr, 0, UART1_ER_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrError(&uart1_handle);
}


//����2Ĭ�����ӵ�����ת����ģ��
IFX_INTERRUPT(uart2_tx_isr, 0, UART2_TX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrTransmit(&uart2_handle);
}
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrReceive(&uart2_handle);
    wireless_uart_callback();
}
IFX_INTERRUPT(uart2_er_isr, 0, UART2_ER_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrError(&uart2_handle);
}



IFX_INTERRUPT(uart3_tx_isr, 0, UART3_TX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrTransmit(&uart3_handle);
}
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrReceive(&uart3_handle);
}
IFX_INTERRUPT(uart3_er_isr, 0, UART3_ER_INT_PRIO)
{
	enableInterrupts();//�����ж�Ƕ��
    IfxAsclin_Asc_isrError(&uart3_handle);
}
