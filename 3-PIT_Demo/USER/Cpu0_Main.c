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
uint32 SpeedPwm1,SpeedPwm2;
int16 Speed1,Speed2,Set_Speed=18000,Speed_Kp=0.1;

int core0_main(void)
{
	disableInterrupts();
	get_clk();//获取时钟频率  务必保留

    //用户在此处调用各种初始化函数等
	//使用CCU6_0模块的通道0 产生一个 100ms的周期中断
	pit_interrupt_ms(CCU6_0, PIT_CH0, 100);
	gtm_pwm_init(ATOM0_CH6_P02_6, 10000, 0);
	gtm_pwm_init(ATOM0_CH4_P02_4, 10000, 0);//ATOM 0模块的通道4 使用P02_4引脚输出PWM  PWM频率50HZ  占空比百分之0/GTM_ATOM0_PWM_DUTY_MAX*100  GTM_AT
	gtm_pwm_init(ATOM0_CH7_P02_7, 10000, 0);
	gtm_pwm_init(ATOM0_CH5_P02_5, 10000, 0);
	pwm_duty(ATOM0_CH4_P02_4, 0);//设置占空比为百分之5000/GTM_ATOM0_PWM_DUTY_MAX*100
	pwm_duty(ATOM0_CH6_P02_6, 2000);
	pwm_duty(ATOM0_CH3_P02_3, 0);//设置占空比为百分之5000/GTM_ATOM0_PWM_DUTY_MAX*100
	pwm_duty(ATOM0_CH7_P02_7, 2000);
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);// encoder
	gpt12_init(GPT12_T3,GPT12_T3INA_P02_6, GPT12_T3EUDA_P02_7);
	//中断函数在isr.c中 函数名称为cc60_pit_ch0_isr
	//中断相关的配置参数在isr_config.h内
	//可配置参数有 CCU6_0_CH0_INT_SERVICE 和 CCU6_0_CH0_ISR_PRIORITY
	//CCU6_0_CH0_INT_SERVICE 中断服务者，表示改中断由谁处理，0:CPU0 1:CPU1 3:DMA  不可设置为其他值
	//CCU6_0_CH0_ISR_PRIORITY 中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

	//需要特备注意的是  不可以有优先级相同的中断函数 每个中断的优先级都必须是不一样的
    enableInterrupts();

    while (TRUE)
    {
    	        Speed1 = gpt12_get(GPT12_T2);
    	    	gpt12_clear(GPT12_T2);
    	    	Speed2 = gpt12_get(GPT12_T3);
    	    	gpt12_clear(GPT12_T3);
    	    	SpeedPwm1=Speed_Kp*(Set_Speed);
    	    	SpeedPwm2=Speed_Kp*(Set_Speed);
    	    	if(SpeedPwm1>3000)
    	    	{SpeedPwm1=3000;}
    	    	if(SpeedPwm1<-3000)
    	    	{SpeedPwm1=-3000;}
    	    	if(SpeedPwm2>3000)
    	    	{SpeedPwm2=3000;}
    	    	if(SpeedPwm2<-3000)
    	    	{SpeedPwm2=-3000;}
    	    	pwm_duty(ATOM0_CH6_P02_6, SpeedPwm1);
    	    	pwm_duty(ATOM0_CH7_P02_7, SpeedPwm2);
    	    	printf("printf speedpwm2 :%d\n", SpeedPwm1);
    	    	printf("printf speed2 :%d\n", Speed1);
    	    	printf("printf speedpwm2 :%d\n", SpeedPwm2);
    	    	printf("printf speed2 :%d\n", Speed2);
    	    	systick_delay_ms(STM1, 1000);
		//在isr.c的中断函数，函数定义的第二个参数固定为0，请不要更改，即使你用CPU1处理中断也不要更改，需要CPU1处理中断只需要在isr_config.h内修改对应的宏定义即可
    	//程序运行之后 PIT中断每执行一次就会打印一次到FSS窗口



    }
}

#pragma section all restore
