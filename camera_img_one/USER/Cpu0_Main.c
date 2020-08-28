

#include "headfile.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#include "img.h"
#include <stdlib.h>
//int16 encoder1;
//int16 encoder2;
//#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
//#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚
//
//#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
//#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚
//int32 speed1_power;
//int32 speed2_power;
//extern int front;
//int set_speed;
//int limit_increase;
//int limit_out;
//int left_pwm,right_pwm;
//int speed_base;
//int adc_error,adc_lasterror,adc_pwm;
//char adc_p1=5,adc_p2=5,adc_p3=50;
//uint32 distance,set_distance=200;
//int  ad_value1,pre_value1,last_value1;
//int  ad_value2,pre_value2,last_value2;
//int  ad_value3,pre_value3,last_value3;

uint8 uart_buff;
uint16 num;
int photo_Flag=0;
int pht=1;
IFX_ALIGN(4) uint8 Photo_image[MT9V03X_H][MT9V03X_W];

int a,b;
void camera_img(void);

#pragma section all "cpu0_dsram"

int core0_main(void)
{
	disableInterrupts();
	get_clk();
	   //获取时钟频率  务必保留
	//oled_init();
//	lcd_init();
//	adc_init(ADC_0, ADC0_CH0_A0);
//	adc_init(ADC_0, ADC0_CH1_A1);
//	adc_init(ADC_0, ADC0_CH2_A2);
//	//uart_init(UART_1, 115200, UART1_TX_P11_12, UART1_RX_P11_10);
//    //uart_putstr(UART_1, "\n---uart test---\n");
//    //用户在此处调用各种初始化函数等
//	printf("printf demo");
	//icm20602_init_spi();
//	gtm_pwm_init(MOTOR1_A, 17000, 0);
//	gtm_pwm_init(MOTOR1_B, 17000, 0);
//	gtm_pwm_init(MOTOR2_A, 17000, 0);
//	gtm_pwm_init(MOTOR2_B, 17000, 0);
    enableInterrupts();
//
//    //oled_init();
//    //mt9v03x_init();
//    int* histogram;
//    speed1_power = 0;
//    speed2_power = 0;

    while (TRUE)
    {

    	//get_icm20602_accdata_spi();
    	//get_icm20602_gyro_spi();
    	//IMUupdate(icm_acc_x, icm_acc_y, icm_acc_z,icm_gyro_x, icm_gyro_y,icm_gyro_z);


//    	if (mt9v03x_finish_flag==1)
//    	{
//    	//lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
//    	//adapt_otsuThreshold(mt9v03x_image[0],COL ,  ROW, &Threshold2);
//    	//halve_image(mt9v03x_image[0],image_half[0],ROW,COL);
//    	//Image_Binary(mt9v03x_image, BinaryImage,Threshold2);
//    	//printf(" %d\n", (int)Threshold2);
//
////		histogram = Histo(*mt9v03x_image);
////		Threshold2 = OtsuThreshold(histogram);
////		//Threshold2 = IterationThreshold(histogram);
////		free(histogram);
////		histogram=NULL;
//	   	//Image_Binary(*mt9v03x_image, *BinaryImage,Threshold2);
//
//	   //	oled_dis_bmp(X_WIDTH, Y_WIDTH, *mt9v03x_image,Threshold2);
//	   	//lcd_displayimage032(*BinaryImage, MT9V03X_W, MT9V03X_H);
//    	//lcd_displayimage7725(BinaryImage[0], ROW , COL );
//    	//mt9v03x_finish_flag=0;
//
//    	}
       if(photo_Flag==0)
       {
    	   //lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
    	   //lcd_displayimage032(Photo_image[0], 180, 100);
    	   //lcd_displayimage032_zoom(mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 160, 128);
       }
       else
       {
    	   //lcd_displayimage032(Photo_image[0], MT9V03X_W, MT9V03X_H);

       }



       //camera_img();
    	//mt9v03x_finish_flag=0;
//      	ad_value1=adc_get(ADC_0, ADC0_CH0_A0, ADC_8BIT);
//      	ad_value2=adc_get(ADC_0, ADC0_CH1_A1, ADC_8BIT);
//      	ad_value3=adc_get(ADC_0, ADC0_CH2_A2, ADC_8BIT);
//
//
////         ad_value1=adc_p1*last_value1+adc_p2*pre_value1+adc_p3*ad_value1/(adc_p1+adc_p2+adc_p3);
////         ad_value2=adc_p2*last_value2+adc_p2*pre_value2+adc_p3*ad_value2/(adc_p1+adc_p2+adc_p3);;
////         ad_value3=adc_p3*last_value3+adc_p3*pre_value3+adc_p3*ad_value3/(adc_p1+adc_p2+adc_p3);;
//
//
//
//    	       last_value1= pre_value1;
//    	       pre_value1=ad_value1;
//    	       last_value2= pre_value2  ;
//    	       pre_value2=ad_value2;
//    	       last_value3= pre_value3  ;
//    	       pre_value3=ad_value3;
//
//    	    lcd_showint32(60,7,ad_value1,7);
//            lcd_showint32(60,6,ad_value2,7);
//    	    lcd_showint32(60,5,ad_value3,7);
//    	    lcd_showstr(20,7,"ad_value1");
//    	    lcd_showstr(20,6,"ad_value2");
//    	    lcd_showstr(20,5,"ad_value3");
//            if(0<=speed1_power) //电机1   正转 设置占空比为 百分之 (1000/GTM_ATOM0_PWM_DUTY_MAX*100)
//            {
//                pwm_duty(MOTOR1_A, speed1_power);
//                pwm_duty(MOTOR1_B, 0);
//            }
//            else                //电机1   反转
//            {
//                pwm_duty(MOTOR1_A, 0);
//                pwm_duty(MOTOR1_B, -speed1_power);
//            }
//
//            if(0<=speed2_power) //电机2   正转
//            {
//                pwm_duty(MOTOR2_A, speed2_power);
//                pwm_duty(MOTOR2_B, 0);
//            }
//            else                //电机2   反转
//            {
//                pwm_duty(MOTOR2_A, 0);
//                pwm_duty(MOTOR2_B, -speed2_power);
//            }
//
//
//
//



    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}






#pragma section all restore

