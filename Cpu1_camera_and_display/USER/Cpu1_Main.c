
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
    {AUTO_EXP,          0},   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
                              //һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
    {EXP_TIME,          110}, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ
    {FPS,               50},  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
    {SET_COL,           MT9V03X_W}, //ͼ��������        ��Χ1-752     K60�ɼ���������188
    {SET_ROW,           MT9V03X_H}, //ͼ��������        ��Χ1-480
    {LR_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {UD_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {GAIN,              32},  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�


    {INIT,              0}    //����ͷ��ʼ��ʼ��
};
#pragma section all "cpu1_dsram"

int core1_main(void)
{
	disableInterrupts();
	//get_clk();//��ȡʱ��Ƶ��  ��ر���
	//oled_init();

	uart_init(UART_0, 115200, UART0_TX_P14_0, UART0_RX_P14_1);
    uart_putstr(UART_0, "\n---uart test---\n");
    //�û��ڴ˴����ø��ֳ�ʼ��������
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

    		//lcd_showuint16(124,124,time);//xΪuint16����
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

















    	//ʹ��printf��ʱ�����ϣ�����η��͵������ܹ�������FSS������ʾ����Ӧ���������� \n ���򵥲����Ի����printf����֮��FSS����û����ʾ
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

