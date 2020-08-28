

#include "headfile.h"
#include "isr.h"
#include "img.h"
#include <stdlib.h>
#include "pid.h"
#include "key.h"
#include "Ks103.h"
#include "SEEKFREE_MT9V03X.h"

int16 encoder1;
int16 encoder2;
#define MOTOR1_A   ATOM0_CH0_P21_2   //定义1电机正转PWM引脚      电机1后视左轮
#define MOTOR1_B   ATOM0_CH1_P21_3   //定义1电机反转PWM引脚
void Two_Valued(int Threshold2);
#define MOTOR2_A   ATOM0_CH2_P21_4   //定义2电机正转PWM引脚
#define MOTOR2_B   ATOM0_CH3_P21_5   //定义2电机反转PWM引脚
int32 speed1_power;
int32 speed2_power;

int set_speed;
int limit_increase;
int limit_out;
int left_pwm,right_pwm;
int speed_base;
int adc_error,adc_lasterror,adc_pwm;
char adc_p=5,adc_d=0;
int32 distance,set_distance=200;
int  ad_value1;
int  ad_value2;
int  ad_value3;
int error1,all_error;
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
	//key_init();
	gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);
	gpt12_init(GPT12_T5, GPT12_T5INB_P10_3, GPT12_T5EUDB_P10_1);

	//uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);

	enableInterrupts();
	lcd_init();	//初始化IPS屏幕
	lcd_showstr(0, 0, "SEEKFREE MT9V03x");
	lcd_showstr(0, 1, "Initializing...");
	//Ks103_init();
    //用户在此处调用各种初始化函数等
	printf("printf demo");
	//icm20602_init_spi();
    enableInterrupts();
    lcd_init();
    mt9v03x_init();
    int* histogram;
    while (TRUE)
    {




    	if (mt9v03x_finish_flag==1)
    	    	{
			mt9v03x_finish_flag=0;
    	    	//printf(" %d\n", (int)Threshold2);

    			histogram = Histo(*mt9v03x_image);
    			Threshold2 = OtsuThreshold(histogram);
    			//Threshold2 = IterationThreshold(histogram);
    			free(histogram);
    			histogram=NULL;

    			Two_Valued(Threshold2);
    			//Image_Binary(*mt9v03x_image, *Image_Array,Threshold2);
    			//lcd_displayimage032(*mt9v03x_image, MT9V03X_W, MT9V03X_H);
    			Search_Center_Blackline();








    	    	}

    	//lcd_displayimage032(Image_Array[0], MT9V03X_W, MT9V03X_H);


    	lcd_displayimage032_zoom(*Image_Array, MT9V03X_W, MT9V03X_H, 160, 128);
	   	all_error=0;
	   	for (int i=70;i<=80;i++)
	   	{
	   		all_error=all_error+MiddleLine[i];
	   	}
//		   	for (int i=35;i<=44;i++)
//		   			   	{
//		   			   		error1=error1+0.5*MiddleLine[i];
//		   			   	}

	   	error1=80-(all_error/11);
	   	lcd_showint16(80,3,error1);









    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}
void Two_Valued(int Threshold2)
{
//  uint8 Image_Buff[MT9V03X_CSI_H][MT9V03X_CSI_W];
  for (int i = 0; i < MT9V03X_H; i++){
    for (int j = 0; j < MT9V03X_W; j++){
//      Image_Buff[i][j] = mt9v03x_csi_image[i][j];
      if (mt9v03x_image[i][j] > Threshold2){
        Image_Array[i][j] = 255;
      }else {
        Image_Array[i][j] = 0;
      }
    }
  }
}



#pragma section all restore

