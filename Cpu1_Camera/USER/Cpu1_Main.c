

#include "headfile.h"
#include "isr.h"
#include "img.h"
#include <stdlib.h>
#include "pid.h"
#include "key.h"
#include "Ks103.h"
int16 encoder1;
int16 encoder2;
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚

#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚
int32 speed1_power;
int32 speed2_power;

int set_speed;
int limit_increase;
int limit_out;
int left_pwm,right_pwm;
int speed_base;
uint32 distance,set_distance=200;

uint32 tim;
int Threshold2;

#pragma section all "cpu1_dsram"

int core1_main(void)
{
	disableInterrupts();
	//get_clk();//获取时钟频率  务必保留
	//oled_init();
    gtm_pwm_init(MOTOR1_A, 17000, 0);
	gtm_pwm_init(MOTOR1_B, 17000, 0);
	gtm_pwm_init(MOTOR2_A, 17000, 0);
	gtm_pwm_init(MOTOR2_B, 17000, 0);
	key_init();
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);

	//uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);

	enableInterrupts();
	lcd_init();	//初始化IPS屏幕
	lcd_showstr(0, 0, "SEEKFREE MT9V03x");
	lcd_showstr(0, 1, "Initializing...");
	Ks103_init();
    //用户在此处调用各种初始化函数等
	printf("printf demo");
	//icm20602_init_spi();
    enableInterrupts();
    lcd_init();
    mt9v03x_init();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5);
    int* histogram;
	speed_base=1500;
	set_speed=800;
	limit_increase=2000;
	limit_out=4000;
	left_pwm=500;
	right_pwm=400;
	systick_start(STM1);

    while (TRUE)
    {

    	 if(key1_flag)
    	 {
    	 key1_flag=0;
    	 }

    	if (mt9v03x_finish_flag==1)
    	    	{

    	    	//printf(" %d\n", (int)Threshold2);

    			histogram = Histo(*mt9v03x_image);
    			Threshold2 = OtsuThreshold(histogram);
    			//Threshold2 = IterationThreshold(histogram);
    			free(histogram);
    			histogram=NULL;
    		   	Image_Binary(*mt9v03x_image, *BinaryImage,Threshold2);


//    	    	adapt_otsuThreshold(mt9v03x_image[0],MT9V03X_H ,  MT9V03X_W, &Threshold2);
//
//    	    	Image_Binary(mt9v03x_image, BinaryImage,Threshold2);

    			//lcd_displayimage032(*BinaryImage, MT9V03X_W, MT9V03X_H);
 //   		   	lcd_displayimage032(*BinaryImage, MT9V03X_W, MT9V03X_H);

    	        PID_Increase();
    	        if(increase>=limit_increase)increase=limit_increase;
    	        if(increase<=-limit_increase)increase=-limit_increase;
    		   	mt9v03x_finish_flag=0;




    	    	}


    if(Flag_10ms)
    {

    	key_get();






//              speed1_power = speed_base+increase;
//              speed2_power = speed_base-increase;
    	        speed1_power = increase;
    	        speed2_power= -increase;
//              speed1_power = out1+increase;
//              speed2_power = out2-increase;



//        data_conversion(encoder1 , encoder2, 4, 4,virtual_scope_data);

	   	tim=systick_getval_ms(STM1);
	    distance=Ks103_getdistance();


        lcd_showint32(20,7,speed1_power,7);
        lcd_showint32(80,7,speed2_power,7);
//        lcd_showint32(80,7,total/20,7);
//        lcd_showint32(30,7,tim,5);
        lcd_showint32(20,6,total/20,7);
        lcd_showint32(80,5,out2,7);
        lcd_showint32(20,5,out1,7);
        lcd_showint32(80,4,increase,7);
//	    lcd_showint32(20,7,distance,7);
//	    lcd_showint32(80,7,set_speed,7);




        if(distance<set_distance && tim>1000)
        {
        	set_speed=0;

        }

    	Flag_10ms=0;

    }












    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}




#pragma section all restore

