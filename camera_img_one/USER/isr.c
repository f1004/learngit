/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
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
//在isr.c的中断函数，函数定义的第二个参数固定为0，请不要更改，即使你用CPU1处理中断也不要更改，需要CPU1处理中断只需要在isr_config.h内修改对应的宏定义即可
extern int16 encoder1;
extern int16 encoder2;
extern char speed_flag;
extern int32 speed1_power;
extern int32 speed2_power;
extern int adc_pwm;
extern int set_speed;
extern int limit_increase;
extern int limit_out;
extern int left_pwm,right_pwm;
extern int speed_base;
extern int adc_pwm;
extern int adc_error,adc_lasterror;
extern char adc_p1,adc_p2,adc_p3;
extern int32 distance,set_distance;
int road;
extern float adc_p,adc_d;//20
extern int adc_limit;

//PIT中断函数  示例
uint8 data;
char Flag_10ms;
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
//
//	   if(distance<set_distance )
//	        {
//	        	set_speed=0;
//
//	        }

	PIT_CLEAR_FLAG(CCU6_0, PIT_CH0);

	encoder2 = -gpt12_get(GPT12_T2);
	encoder1 = gpt12_get(GPT12_T5);

	gpt12_clear(GPT12_T2);
	gpt12_clear(GPT12_T5);

    ad_value1=(adc_p1*last_value1+adc_p2*pre_value1+adc_p3*ad_value1)/(adc_p1+adc_p2+adc_p3);
    ad_value2=(adc_p1*last_value2+adc_p2*pre_value2+adc_p3*ad_value2)/(adc_p1+adc_p2+adc_p3);
    ad_value3=(adc_p1*last_value3+adc_p2*pre_value3+adc_p3*ad_value3)/(adc_p1+adc_p2+adc_p3);

      last_value1= pre_value1;
      pre_value1=ad_value1;
      last_value3= pre_value3;
      pre_value3=ad_value3;
      last_value2= pre_value2;
      pre_value2=ad_value2;

	turn();
	adc_error=ad_error1;
	if(adc_error>adc_limit)adc_error=adc_limit;
	if(adc_error<-adc_limit)adc_error=-adc_limit;
	adc_pwm=(int)(adc_p*adc_error+adc_d*(adc_error-adc_lasterror));
	adc_lasterror=adc_error;

	if(speed_flag==2)
	{    speed_pid(encoder1,encoder2,set_speed);
        speed1_power = -adc_pwm+out1;
        speed2_power = +adc_pwm+out1;
	}
	else if(speed_flag==1)
	{
        speed1_power = -adc_pwm;
        speed2_power = +adc_pwm;


	}
	else
	{speed1_power=0;
	speed2_power=0;

	}
//    speed1_power = 800-adc_pwm;
//    speed2_power = 800+adc_pwm;


//       speed1_power = -adc_pwm;
//       speed2_power = +adc_pwm;

//	        if(out1>=limit_out)out1=limit_out;
//	        if(out1<=-limit_out)out1=-limit_out;
//	        if(out2>=limit_out)out2=limit_out;
//	        if(out2<=-limit_out)out2=-limit_out;
	//    	        increase=0;
//	        speed1_power = out1+increase;
//	        speed2_power = out2-increase;

//	        speed1_power = -adc_pwm+out1;
//	        speed2_power = +adc_pwm+out2;

//        speed1_power = -adc_pwm;
//	        speed2_power = +adc_pwm;
	        if(speed1_power>=limit_out)speed1_power=limit_out;
	        if(speed1_power<=-limit_out)speed1_power=-limit_out;
	        if(speed2_power>=limit_out)speed2_power=limit_out;
	        if(speed2_power<=-limit_out)speed2_power=-limit_out;


	        if(speed1_power>=0) //电机1   正转 设置占空比为 百分之 (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
	           	   	                {
	           	   	                    pwm_duty(MOTOR1_A, speed1_power+left_pwm);
	           	   	                    pwm_duty(MOTOR1_B, 0);
	           	   	                }
	           	   	                else                //电机1   反转
	           	   	                {
	           	   	                    pwm_duty(MOTOR1_A, 0);
	           	   	                    pwm_duty(MOTOR1_B, -speed1_power+left_pwm);
	           	   	                }
	         if(speed2_power>=0) //电机2   正转
	           	   	                {
	           	   	                    pwm_duty(MOTOR2_A, speed2_power+right_pwm);
	           	   	                    pwm_duty(MOTOR2_B, 0);
	           	   	                }
	           	   	                else                //电机2   反转
	           	   	                {
	           	   	                    pwm_duty(MOTOR2_A, 0);
	           	   	                    pwm_duty(MOTOR2_B, -speed2_power+right_pwm);
	           	   	                }
	Flag_10ms=1;


}


IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);

}

IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);

}

IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);

}




IFX_INTERRUPT(eru_ch0_ch4_isr, 0, ERU_CH0_CH4_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH0_REQ4_P10_7))//通道0中断
	{
		CLEAR_GPIO_FLAG(ERU_CH0_REQ4_P10_7);
	}

	if(GET_GPIO_FLAG(ERU_CH4_REQ13_P15_5))//通道4中断
	{
		CLEAR_GPIO_FLAG(ERU_CH4_REQ13_P15_5);
	}
}

IFX_INTERRUPT(eru_ch1_ch5_isr, 0, ERU_CH1_CH5_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH1_REQ5_P10_8))//通道1中断
	{
		CLEAR_GPIO_FLAG(ERU_CH1_REQ5_P10_8);
	}

	if(GET_GPIO_FLAG(ERU_CH5_REQ1_P15_8))//通道5中断
	{
		CLEAR_GPIO_FLAG(ERU_CH5_REQ1_P15_8);
	}
}

//由于摄像头pclk引脚默认占用了 2通道，用于触发DMA，因此这里不再定义中断函数
//IFX_INTERRUPT(eru_ch2_ch6_isr, 0, ERU_CH2_CH6_INT_PRIO)
//{
//	enableInterrupts();//开启中断嵌套
//	if(GET_GPIO_FLAG(ERU_CH2_REQ7_P00_4))//通道2中断
//	{
//		CLEAR_GPIO_FLAG(ERU_CH2_REQ7_P00_4);
//
//	}
//	if(GET_GPIO_FLAG(ERU_CH6_REQ9_P20_0))//通道6中断
//	{
//		CLEAR_GPIO_FLAG(ERU_CH6_REQ9_P20_0);
//
//	}
//}



IFX_INTERRUPT(eru_ch3_ch7_isr, 0, ERU_CH3_CH7_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH3_REQ6_P02_0))//通道3中断
	{
		CLEAR_GPIO_FLAG(ERU_CH3_REQ6_P02_0);
		if		(1 == camera_type)	mt9v03x_vsync();
		else if	(3 == camera_type)	ov7725_vsync();

	}
	if(GET_GPIO_FLAG(ERU_CH7_REQ16_P15_1))//通道7中断
	{
		CLEAR_GPIO_FLAG(ERU_CH7_REQ16_P15_1);

	}
}



IFX_INTERRUPT(dma_ch5_isr, 0, ERU_DMA_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套

	if		(1 == camera_type)	mt9v03x_dma();
	else if	(3 == camera_type)	ov7725_dma();
}


//串口中断函数  示例
IFX_INTERRUPT(uart0_tx_isr, 0, UART0_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	uart_putchar(UART_0, 0xe8);// uart address
    systick_delay_us(STM0, 20);
	uart_putchar(UART_0, 0x02);//register
	systick_delay_us(STM0, 20);
	uart_putchar(UART_0, 0xbc);//0-11m distance feedback with temporary compensate
	systick_delay_us(STM0, 20);

	uart_putchar(UART_0, 0xc9);
	systick_delay_us(STM0, 20);

    IfxAsclin_Asc_isrTransmit(&uart0_handle);
}
IFX_INTERRUPT(uart0_rx_isr, 0, UART0_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套

	if(uart_query(UART_0,&data))
	{
	uart_getchar(UART_0,&data);
	distance =  data << 8;
	uart_getchar(UART_0,&data);
	distance |= data;
    IfxAsclin_Asc_isrReceive(&uart0_handle);
	}
}
IFX_INTERRUPT(uart0_er_isr, 0, UART0_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart0_handle);
}

//串口1默认连接到摄像头配置串口
IFX_INTERRUPT(uart1_tx_isr, 0, UART1_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart1_handle);
}
IFX_INTERRUPT(uart1_rx_isr, 0, UART1_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart1_handle);
    mt9v03x_uart_callback();
}
IFX_INTERRUPT(uart1_er_isr, 0, UART1_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart1_handle);
}


//串口2默认连接到无线转串口模块
IFX_INTERRUPT(uart2_tx_isr, 0, UART2_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart2_handle);
}
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart2_handle);
    wireless_uart_callback();
}
IFX_INTERRUPT(uart2_er_isr, 0, UART2_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart2_handle);
}



IFX_INTERRUPT(uart3_tx_isr, 0, UART3_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart3_handle);
}
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart3_handle);
}
IFX_INTERRUPT(uart3_er_isr, 0, UART3_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart3_handle);
}
