/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
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


#include "headfile.h"
#include "SEEKFREE_18TFT.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_MT9V03X.h"
#pragma section all "cpu0_dsram"
unsigned char Threshold2;

int core0_main(void)
{
	disableInterrupts();
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	oled_init();
	lcd_init();

    //�û��ڴ˴����ø��ֳ�ʼ��������
	printf("printf demo");
	//icm20602_init_spi();
    enableInterrupts();
    mt9v03x_init();
    while (TRUE)
    {


    	mt9v03x_finish_flag=0;
    	//get_icm20602_accdata_spi();
    	//get_icm20602_gyro_spi();
    	//printf(" %d\n", icm_acc_x);
    	//adapt_otsuThreshold(mt9v03x_image[0],COL ,  ROW, &Threshold2);
    	//Image_Binary(mt9v03x_image, BinaryImage,Threshold2);
    	//lcd_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
    	  //oled_uint16(1,6,1004);
    	//lcd_showint16(1,1,num);
    	//systick_delay_ms(STM0, 1000);

    	//��Ҫע��printf����ͨ�����ڷ��͵�
    	//�����printf��ͨ�������������ݷ��͵�FSS���ڵģ�ʹ�������ȽϷ����Ҳ���Ҫռ�ô���




    	    //�û��ڴ˴����ø��ֳ�ʼ��������
    		//˫�˵�ʹ����ʵ�ܼ򵥣�����������main�б�д���õĳ��򼴿�
    		//������ʹ�ú���0 ��˸P20_8��LED	����1��˸P20_9��LED

    		//gpio_init(P20_8, GPO, 0, PUSHPULL);
#define a 1


#ifdef a == 1
if(1)
{
	



}
 

    
    
#endif









    	//ʹ��printf��ʱ�����ϣ�����η��͵������ܹ�������FSS������ʾ����Ӧ���������� \n ���򵥲����Ի����printf����֮��FSS����û����ʾ
    }
}
#pragma section all restore
