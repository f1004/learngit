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
#include "pid.h"
#include "key.h"
#include "Ks103.h"
#include "zf_uart.h"
#pragma section all "cpu1_dsram"
int16 encoder1;
int16 encoder2;
int time1;
int32 speed1_power;
int32 speed2_power;
extern int front;
int set_speed=150;
int limit_increase;
int limit_out=5000;
int adc_limit=300;
int left_pwm=400,right_pwm=400;//400
int speed_base,adc_pwm;
int adc_error,adc_lasterror;
char adc_p1=1,adc_p2=1,adc_p3=5;
int32 distance,set_distance=200;
char speed_flag,sq_flag;
float adc_p=7,adc_d=0.19;//20

void core1_main(void)
{
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());

    //用户在此处调用各种初始化函数等
	lcd_init();
	adc_init(ADC_0, ADC0_CH0_A0);
	adc_init(ADC_0, ADC0_CH1_A1);
	adc_init(ADC_0, ADC0_CH2_A2);

	//uart_init(UART_1, 115200, UART1_TX_P11_12, UART1_RX_P11_10);
    //uart_putstr(UART_1, "\n---uart test---\n");
    //用户在此处调用各种初始化函数等
	printf("printf demo");
//	icm20602_init_spi();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
	gtm_pwm_init(MOTOR1_A, 17000, 0);
	gtm_pwm_init(MOTOR1_B, 17000, 0);
	gtm_pwm_init(MOTOR2_A, 17000, 0);
	gtm_pwm_init(MOTOR2_B, 17000, 0);
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T5, GPT12_T5INB_P10_3, GPT12_T5EUDB_P10_1);
	 key_init();

    enableInterrupts();
    //icm20602_init_spi();
    //oled_init();
    //mt9v03x_init();
   // int* histogram;
	Ks103_init();
	uart_set_interrupt_priority(UART_0);
    while (TRUE)
    {    //systick_start(STM1);
      	adc_get(ADC_0, ADC0_CH0_A0,ADC0_CH1_A1,ADC0_CH2_A2, ADC_8BIT);


      //	time1=systick_getval_us(STM1);
      	key_get();
	    lcd_showint32(20,7,ad_value1,3);
        lcd_showint32(20,6,ad_value2,3);
	    lcd_showint32(20,5,ad_value3,3);

	    lcd_showfloat(80,4,adc_d,2,2);
	    lcd_showfloat(80,3,adc_p,3,2);

	    lcd_showint32(80,1,distance,6);
    	lcd_showint32(80,0,set_speed,3);

	    lcd_showint32(80,2,adc_error,3);
//	    lcd_showint32(80,1,speed1_power,7);
//	    lcd_showint32(80,0,speed2_power,7);
	    lcd_showstr(0,7,"ad1");
	    lcd_showstr(0,6,"ad2");
	    lcd_showstr(0,5,"ad3");
	    lcd_showstr(0,4,"adc_d");
	    lcd_showstr(0,3,"adc_p");
	    lcd_showstr(0,2,"error");
	    lcd_showstr(0,1,"distance1");
	    lcd_showstr(0,0,"set_speed");



   if (key1_flag)
  {


	speed_flag++;
	if(speed_flag>2)
	{speed_flag=0;}

	key1_flag=0;
  }

        //	        speed1_power = out1+increase;
        //	        speed2_power = out2-increase;


  if(key2_flag)
  {
	  sq_flag++;
	  if(sq_flag>2)
	  {
		  sq_flag=0;

	  }
	  key2_flag=0;

  }
  if(key3_flag)
  {

	  switch(sq_flag)
	  {  case 0:adc_p=adc_p+0.1;break;
	      case 1:adc_d=adc_d+0.1;break;
	      case 2:set_speed=set_speed+10;break;

	  }

	  key3_flag=0;
  }

  if(key4_flag)
  {

	  switch(sq_flag)
	  {  case 0:adc_p=adc_p-0.1;break;
	      case 1:adc_d=adc_d-0.1;break;
	      case 2:set_speed=set_speed-10;break;

	  }
	  key4_flag=0;

  }







    }
}
#pragma section all restore
