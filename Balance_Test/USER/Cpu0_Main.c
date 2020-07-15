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
uint16 num;

int core0_main(void)
{
	disableInterrupts();
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//oled_init();
	//lcd_init();
    //�û��ڴ˴����ø��ֳ�ʼ��������
	printf("printf demo");
	icm20602_init_spi();
    enableInterrupts();

    while (TRUE)
    {
    	//num++;
    	//printf("printf num :%d\n", num);
    	get_icm20602_accdata_spi();
    	get_icm20602_gyro_spi();
    	printf("icm_acc_x:%f\n", Pitch);
    	printf("icm_acc_y:%f\n", Roll);
    	//printf("icm_acc_z :%f\n", Yaw);
    	lcd_showfloat(0,0,Pitch,2,3);
    	lcd_showfloat(0,0,Yaw,3,4);
    	IMUupdate(icm_acc_x, icm_acc_y, icm_acc_z,icm_gyro_x, icm_gyro_y,icm_gyro_z);
    	  //oled_uint16(1,6,1004);
    	//lcd_showint16(1,1,num);
    	//systick_delay_ms(STM0, 100);

    	//��Ҫע��printf����ͨ�����ڷ��͵�
    	//�����printf��ͨ�������������ݷ��͵�FSS���ڵģ�ʹ�������ȽϷ����Ҳ���Ҫռ�ô���




    	    //�û��ڴ˴����ø��ֳ�ʼ��������
    		//˫�˵�ʹ����ʵ�ܼ򵥣�����������main�б�д���õĳ��򼴿�
    		//������ʹ�ú���0 ��˸P20_8��LED	����1��˸P20_9��LED

    		gpio_init(P20_8, GPO, 0, PUSHPULL);













    	//ʹ��printf��ʱ�����ϣ�����η��͵������ܹ�������FSS������ʾ����Ӧ���������� \n ���򵥲����Ի����printf����֮��FSS����û����ʾ
    }
}
