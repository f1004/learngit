

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
#include "isr.h"
#include "headfile.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#include "img.h"
#include <stdlib.h>
#include "pid.h"
int16 encoder1;
int16 encoder2;
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚

#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚
int32 speed1_power;
int32 speed2_power;

int set_speed=0;
int limit_increase;
int limit_out;
int left_pwm=700,right_pwm=500;

int Threshold2;
#pragma section all "cpu0_dsram"

void core0_main(void)
{

    //用户在此处调用各种初始化函数等


	get_clk();//获取时钟频率  务必保留

    		//目前的库采集总钻风 图像最后一列为固定的黑色
    		//这是由于单片机造成的，不是摄像头的问题
    		pit_interrupt_ms(CCU6_0, PIT_CH0, 5);

    		//如果屏幕没有任何显示，请检查屏幕接线

    		    gtm_pwm_init(MOTOR1_A, 17000, 0);
    			gtm_pwm_init(MOTOR1_B, 17000, 0);
    			gtm_pwm_init(MOTOR2_A, 17000, 0);
    			gtm_pwm_init(MOTOR2_B, 17000, 0);

    			gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
    			gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);

    			uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    			limit_increase=2000;
    			limit_out=4000;
    			enableInterrupts();
    			lcd_init();	//初始化IPS屏幕
    			lcd_showstr(0, 0, "SEEKFREE MT9V03x");
    			lcd_showstr(0, 1, "Initializing...");
    		mt9v03x_init();	//初始化摄像头
    		//如果屏幕一直显示初始化信息，请检查摄像头接线
    	    //如果使用主板，一直卡在while(!uart_receive_flag)，请检查是否电池连接OK?或者摄像头的配置串口与单片机连接是否正确
    	    //如果图像只采集一次，请检查场信号(VSY)是否连接OK?


    	    int* histogram;
    	    while (TRUE)
    	    {

    	    if(flag==1)
    	    {
    	    	        histogram = Histo(*mt9v03x_image);
    	    			Threshold2 = OtsuThreshold(histogram);
    	    			//Threshold2 = IterationThreshold(histogram);
    	    			free(histogram);
    	    			histogram=NULL;
    	    		   	Image_Binary(*mt9v03x_image, *BinaryImage,Threshold2);
    	    	if(mt9v03x_finish_flag)
    	    	{
    	    		lcd_displayimage032(BinaryImage[0], MT9V03X_W, MT9V03X_H-20);
    				mt9v03x_finish_flag = 0;//在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
    				//注意：一定要在图像使用完毕后在清除此标志位
    	    	}

    			encoder1 = gpt12_get(GPT12_T2);
    			encoder2 = -gpt12_get(GPT12_T4);

    			gpt12_clear(GPT12_T2);
    			gpt12_clear(GPT12_T4);


    	    	PID_Increase();
    	        if(increase>=limit_increase)increase=limit_increase;
    	        if(increase<=-limit_increase)increase=-limit_increase;

    	//        speed1_power = speed_base+increase;
    	//        speed2_power = speed_base-increase;

    	        speed_pid(encoder1,encoder2,set_speed);
    	        if(out1>=limit_out)out1=limit_out;
    	        if(out1<=-limit_out)out1=-limit_out;
    	        if(out2>=limit_out)out2=limit_out;
    	        if(out2<=-limit_out)out2=-limit_out;
    	        speed1_power = increase;
    	        speed2_power= -increase;
//    	        speed1_power = out1+increase;
//  	            speed2_power = out2-increase;

    	        if(speed1_power>=4000)speed1_power=4000;
    	        if(speed1_power<=-4000)speed1_power=-4000;
    	        if(speed2_power>=4000)speed2_power=4000;
    	        if(speed2_power<=-4000)speed2_power=-4000;

    	        data_conversion(encoder1 , encoder2, 4, 4,virtual_scope_data);

    	    	if(0<=speed1_power) //电机1   正转 设置占空比为 百分之 (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
    	        {
    	            pwm_duty(MOTOR1_A, left_pwm+speed1_power);
    	            pwm_duty(MOTOR1_B, 0);
    	        }
    	        else                //电机1   反转
    	        {
    	            pwm_duty(MOTOR1_A, 0);
    	            pwm_duty(MOTOR1_B, -left_pwm-speed1_power);
    	        }

    	        if(0<=speed2_power) //电机2   正转
    	        {
    	            pwm_duty(MOTOR2_A, right_pwm+speed2_power);
    	            pwm_duty(MOTOR2_B, 0);
    	        }
    	        else                //电机2   反转
    	        {
    	            pwm_duty(MOTOR2_A, 0);
    	            pwm_duty(MOTOR2_B, -right_pwm-speed2_power);
    	        }

    	        lcd_showint32(20,7,error,7);
    	        lcd_showint32(80,7,encoder2,7);
    	//        lcd_showint32(30,7,encoder2,5);
    	        lcd_showint32(20,6,speed1_power,7);
    	        lcd_showint32(80,6,speed2_power,7);

    	         flag=0;
    	    }
    	    }



}
#pragma section all restore
