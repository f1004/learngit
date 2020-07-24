

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
       {   mt9v03x_finish_flag=0;
    	   lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
    	   //lcd_displayimage032(Photo_image[0], 180, 100);
    	   //lcd_displayimage032_zoom(mt9v03x_image[0], MT9V03X_W, MT9V03X_H, 160, 128);
       }
       else
       {   mt9v03x_finish_flag=1;
    	   lcd_displayimage032(Photo_image[0], MT9V03X_W, MT9V03X_H);



       }


       camera_img();



















    	//使用printf的时候如果希望本次发送的内容能够立即在FSS窗口显示，则应该在最后加入 \n 否则单步调试会出现printf运行之后FSS窗口没有显示
    }
}


void camera_img(void)
{
	if(uart_query(UART_0, &uart_buff))
	    	{
	    		photo_Flag=1;



	    		/*for( i1 = 0; i1 < MT9V03X_H; i1++)
	    		    {
	    		      for( j1 = 0; j1 < MT9V03X_W; j1++)
	    		      {
	    		     uart_putchar(UART_0, Photo_image[i1][j1]);
	    		      }
	    		      uart_putstr(UART_0,"\n");
	    		    }
	                 */

	    		uart_putbuff(UART_0,&mt9v03x_image[0],MT9V03X_W*MT9V03X_H);


	    	}



}

#pragma section all restore

