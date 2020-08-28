/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,锟斤拷煽萍锟�
 * All rights reserved.
 * 锟斤拷锟斤拷锟斤拷锟斤拷QQ群锟斤拷锟斤拷群锟斤拷824575535
 *
 * 锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟捷帮拷权锟斤拷锟斤拷锟斤拷煽萍锟斤拷锟斤拷校锟轿达拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟揭碉拷锟酵撅拷锟�
 * 锟斤拷迎锟斤拷位使锟矫诧拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟睫革拷锟斤拷锟斤拷时锟斤拷锟诫保锟斤拷锟斤拷煽萍锟斤拷陌锟饺拷锟斤拷锟斤拷锟�
 *
 * @file       		main
 * @company	   		锟缴讹拷锟斤拷煽萍锟斤拷锟斤拷薰锟剿�
 * @author     		锟斤拷煽萍锟�(QQ3184284598)
 * @version    		锟介看doc锟斤拷version锟侥硷拷 锟芥本说锟斤拷
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
	get_clk();//锟斤拷取时锟斤拷频锟斤拷  锟斤拷乇锟斤拷锟�
	//oled_init();
	//lcd_init();

    //锟矫伙拷锟节此达拷锟斤拷锟矫革拷锟街筹拷始锟斤拷锟斤拷锟斤拷锟斤拷
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

    	//锟斤拷要注锟斤拷printf锟斤拷锟斤拷通锟斤拷锟斤拷锟节凤拷锟酵碉拷
    	//锟斤拷锟斤拷锟絧rintf锟斤拷通锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷锟捷凤拷锟酵碉拷FSS锟斤拷锟节的ｏ拷使锟斤拷锟斤拷锟斤拷锟饺较凤拷锟斤拷锟揭诧拷锟斤拷要占锟矫达拷锟斤拷




    	    //锟矫伙拷锟节此达拷锟斤拷锟矫革拷锟街筹拷始锟斤拷锟斤拷锟斤拷锟斤拷
    		//双锟剿碉拷使锟斤拷锟斤拷实锟杰简单ｏ拷锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷main锟叫憋拷写锟斤拷锟矫的筹拷锟津即匡拷
    		//锟斤拷锟斤拷锟斤拷使锟矫猴拷锟斤拷0 锟斤拷烁P20_8锟斤拷LED	锟斤拷锟斤拷1锟斤拷烁P20_9锟斤拷LED

    		//gpio_init(P20_8, GPO, 0, PUSHPULL);










    	//使锟斤拷printf锟斤拷时锟斤拷锟斤拷锟较ｏ拷锟斤拷锟斤拷畏锟斤拷偷锟斤拷锟斤拷锟斤拷芄锟斤拷锟斤拷锟斤拷锟紽SS锟斤拷锟斤拷锟斤拷示锟斤拷锟斤拷应锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷 \n 锟斤拷锟津单诧拷锟斤拷锟皆伙拷锟斤拷锟絧rintf锟斤拷锟斤拷之锟斤拷FSS锟斤拷锟斤拷没锟斤拷锟斤拷示
    }
}
#pragma section all restore
