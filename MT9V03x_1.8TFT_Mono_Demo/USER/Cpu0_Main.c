

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
#define MOTOR1_A   ATOM0_CH0_P21_2   //����1�����תPWM����      ���1��������
#define MOTOR1_B   ATOM0_CH1_P21_3   //����1�����תPWM����

#define MOTOR2_A   ATOM0_CH2_P21_4   //����2�����תPWM����
#define MOTOR2_B   ATOM0_CH3_P21_5   //����2�����תPWM����
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

    //�û��ڴ˴����ø��ֳ�ʼ��������


	get_clk();//��ȡʱ��Ƶ��  ��ر���

    		//Ŀǰ�Ŀ�ɼ������ ͼ�����һ��Ϊ�̶��ĺ�ɫ
    		//�������ڵ�Ƭ����ɵģ���������ͷ������
    		pit_interrupt_ms(CCU6_0, PIT_CH0, 5);

    		//�����Ļû���κ���ʾ��������Ļ����

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
    			lcd_init();	//��ʼ��IPS��Ļ
    			lcd_showstr(0, 0, "SEEKFREE MT9V03x");
    			lcd_showstr(0, 1, "Initializing...");
    		mt9v03x_init();	//��ʼ������ͷ
    		//�����Ļһֱ��ʾ��ʼ����Ϣ����������ͷ����
    	    //���ʹ�����壬һֱ����while(!uart_receive_flag)�������Ƿ�������OK?��������ͷ�����ô����뵥Ƭ�������Ƿ���ȷ
    	    //���ͼ��ֻ�ɼ�һ�Σ����鳡�ź�(VSY)�Ƿ�����OK?


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
    				mt9v03x_finish_flag = 0;//��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
    				//ע�⣺һ��Ҫ��ͼ��ʹ����Ϻ�������˱�־λ
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

    	    	if(0<=speed1_power) //���1   ��ת ����ռ�ձ�Ϊ �ٷ�֮ (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
    	        {
    	            pwm_duty(MOTOR1_A, left_pwm+speed1_power);
    	            pwm_duty(MOTOR1_B, 0);
    	        }
    	        else                //���1   ��ת
    	        {
    	            pwm_duty(MOTOR1_A, 0);
    	            pwm_duty(MOTOR1_B, -left_pwm-speed1_power);
    	        }

    	        if(0<=speed2_power) //���2   ��ת
    	        {
    	            pwm_duty(MOTOR2_A, right_pwm+speed2_power);
    	            pwm_duty(MOTOR2_B, 0);
    	        }
    	        else                //���2   ��ת
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
