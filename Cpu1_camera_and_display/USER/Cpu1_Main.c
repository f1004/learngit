
#include "isr.h"
#include "headfile.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#include "img.h"
#include <stdlib.h>
uint8 uart_buff;
uint16 num;
int photo_Flag=0;
int pht=1;
IFX_ALIGN(4) uint8 Photo_image[MT9V03X_H][MT9V03X_W];
unsigned char Threshold2;
int a,b;
void camera_img(void);


int16 NEW_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      范围1-63 0为关闭 如果自动曝光开启  EXP_TIME命令设置的数据将会变为最大曝光时间，也就是自动曝光时间的上限
                              //一般情况是不需要开启这个功能，因为比赛场地光线一般都比较均匀，如果遇到光线非常不均匀的情况可以尝试设置该值，增加图像稳定性
    {EXP_TIME,          110}, //曝光时间          摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值
    {FPS,               50},  //图像帧率          摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
    {SET_COL,           MT9V03X_W}, //图像列数量        范围1-752     K60采集不允许超过188
    {SET_ROW,           MT9V03X_H}, //图像行数量        范围1-480
    {LR_OFFSET,         0},   //图像左右偏移量    正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {UD_OFFSET,         0},   //图像上下偏移量    正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {GAIN,              32},  //图像增益          范围16-64     增益可以在曝光时间固定的情况下改变图像亮暗程度


    {INIT,              0}    //摄像头开始初始化
};
#pragma section all "cpu1_dsram"

int core1_main(void)
{
	disableInterrupts();
	//get_clk();//获取时钟频率  务必保留
	//oled_init();

	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    uart_putstr(UART_0, "\n---uart test---\n");
    //用户在此处调用各种初始化函数等
	printf("printf demo");
	//icm20602_init_spi();
    enableInterrupts();
    lcd_init();
    mt9v03x_init();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 5000);
    int* histogram;
    while (TRUE)
    {



    	if(Flag_1s)
    {       NEW_CFG[1][1]=time;

    		//lcd_showuint16(124,124,time);//x为uint16类型
    		//printf("time is %d\n",time);
    		//printf("Real time is %d\n",MT9V03X_CFG[1][1]);
    	    set_config(MT9V03X_COF_UART, NEW_CFG);

    		if(time==110)
    		{
    			time=600;


    		}
    		else
    		{
    			time=110;


    		}



    		Flag_1s=0;
    	    	}
//    	if (mt9v03x_finish_flag==1)
//    	{
//    	//lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
//    	//adapt_otsuThreshold(mt9v03x_image[0],COL ,  ROW, &Threshold2);
//    	//halve_image(mt9v03x_image[0],image_half[0],ROW,COL);
//    	//Image_Binary(mt9v03x_image, BinaryImage,Threshold2);
//    	//printf(" %d\n", (int)Threshold2);
//
//		histogram = Histo(*mt9v03x_image);
//		Threshold2 = OtsuThreshold(histogram);
//		//Threshold2 = IterationThreshold(histogram);
//		free(histogram);
//		histogram=NULL;
//	   	Image_Binary(*mt9v03x_image, *BinaryImage,Threshold2);
//
//
//	   	lcd_displayimage032(*BinaryImage, MT9V03X_W, MT9V03X_H);
//    	//lcd_displayimage7725(BinaryImage[0], ROW , COL );
//    	mt9v03x_finish_flag=0;
//
//    	}
    	lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
    	if(mt9v03x_finish_flag==1)
    	{

       if(photo_Flag==0)
       {   mt9v03x_finish_flag=0;

    	   //lcd_displayimage032(Photo_image[0], 180, 100);
    	   //lcd_displayimage032_zoom(mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 160, 128);
       }
       else
       {   mt9v03x_finish_flag=1;




       }



       camera_img();

    	}

















    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}


void camera_img(void)
{
	if(uart_query(UART_0, &uart_buff))
	    	{
	    		photo_Flag=1;



	    		for( int i1 = 0; i1 < MT9V03X_H; i1++)
	    		    {
	    		      for( int j1 = 0; j1 < MT9V03X_W-1
	    		      ; j1++)
	    		      {
	    		     uart_putchar(UART_0, mt9v03x_image[i1][j1]);
	    		      }
	    		      uart_putstr(UART_0,"\n");
	    		    }


	    		//uart_putbuff(UART_0,mt9v03x_image[0],MT9V03X_W*MT9V03X_H);


	    	}



}

#pragma section all restore

