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

unsigned char Threshold2;
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
#pragma section all "cpu0_dsram"

int core0_main(void)
{
	disableInterrupts();
	get_clk();//获取时钟频率  务必保留
	//oled_init();
	lcd_init();
	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    uart_putstr(UART_0, "\n---uart test---\n");
    //用户在此处调用各种初始化函数等
	printf("printf demo");
	//icm20602_init_spi();
    enableInterrupts();
    mt9v03x_init();
    int* histogram;
    while (TRUE)
    {
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
       if(photo_Flag==0)
       {
    	   lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
       }
       else
       {
    	   lcd_displayimage032(Photo_image[0], MT9V03X_W, MT9V03X_H);

       }




    	int i1,j1;
    	//查询是否有数据，如果有则接收
    	if(uart_query(UART_0, &uart_buff))
    	{
    		photo_Flag=1;
    		for( i1 = 0; i1 < MT9V03X_H; i1++)
	    {
	      for( j1 = 0; j1 < MT9V03X_W; j1++)
	      {


	    	  Photo_image[i1][j1]=(uint8)mt9v03x_image[i1][j1];

	      }


	    }


    		/*for( i1 = 0; i1 < MT9V03X_H; i1++)
    		    {
    		      for( j1 = 0; j1 < MT9V03X_W; j1++)
    		      {


    		     uart_putchar(UART_0, Photo_image[i1][j1]);

    		      }
    		      uart_putstr(UART_0,"\n");

    		    }
                 */

    		uart_putbuff(UART_0,&mt9v03x_image[0],22560);

         //printf('%d\n',a);
         //printf('%d\n',b);

    	}
    	a=sizeof(Photo_image)/sizeof(Photo_image[0]);
    	b=sizeof(Photo_image)/sizeof(Photo_image[0][0]);


    	mt9v03x_finish_flag=0;

    	  //oled_uint16(1,6,1004);
    	//lcd_showint16(1,1,1);
    	//systick_delay_ms(STM0, 1000);

    	//需要注意printf不是通过串口发送的
    	//这里的printf是通过调试器将内容发送到FSS窗口的，使用起来比较方便且不需要占用串口




    	    //用户在此处调用各种初始化函数等
    		//双核的使用其实很简单，就是在两个main中编写不用的程序即可
    		//本例程使用核心0 闪烁P20_8的LED	核心1闪烁P20_9的LED

    		//gpio_init(P20_8, GPO, 0, PUSHPULL);













    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}

#pragma section all restore
