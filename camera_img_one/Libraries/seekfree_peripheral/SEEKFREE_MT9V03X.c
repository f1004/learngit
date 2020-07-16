/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ����������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		�����
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note		
					���߶��壺
					------------------------------------ 
					ģ��ܽ�            			��Ƭ���ܽ�
					SDA(51��RX)         		�鿴SEEKFREE_MT9V03X.h�ļ��е�MT9V03X_COF_UART_TX�궨��
					SCL(51��TX)         		�鿴SEEKFREE_MT9V03X.h�ļ��е�MT9V03X_COF_UART_RX�궨��
					���ж�(VSY)         		�鿴SEEKFREE_MT9V03X.h�ļ��е�MT9V03X_VSYNC_PIN�궨��
					���ж�(HREF)				����û��ʹ�ã���˲�����
					�����ж�(PCLK)      		�鿴SEEKFREE_MT9V03X.h�ļ��е�MT9V03X_PCLK_PIN�궨��
					���ݿ�(D0-D7)			�鿴SEEKFREE_MT9V03X.h�ļ��е�MT9V03X_DATA_PIN�궨��
					------------------------------------ 
	
					Ĭ�Ϸֱ�����           			188*120
					Ĭ��FPS                 50֡
 ********************************************************************************************************************/


#include "IfxDma.h"
#include "IfxScuEru.h"
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_eru.h"
#include "zf_eru_dma.h"
#include "SEEKFREE_MT9V03X.h"


//����4�ֽڶ���
IFX_ALIGN(4) uint8 mt9v03x_image[MT9V03X_H][MT9V03X_W];

uint8   receive[3];
uint8   receive_num = 0;
vuint8  uart_receive_flag;
uint8 image_half[ROW/2][COL/2];//ѹ����ͼ��
uint8   link_list_num;

//��Ҫ���õ�����ͷ������
int16 MT9V03X_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����      ��Χ1-63 0Ϊ�ر� ����Զ��ع⿪��  EXP_TIME�������õ����ݽ����Ϊ����ع�ʱ�䣬Ҳ�����Զ��ع�ʱ�������
                              //һ������ǲ���Ҫ����������ܣ���Ϊ�������ع���һ�㶼�ȽϾ��ȣ�����������߷ǳ������ȵ�������Գ������ø�ֵ������ͼ���ȶ���
    {EXP_TIME,          50}, //�ع�ʱ��          ����ͷ�յ�����Զ����������ع�ʱ�䣬������ù���������Ϊ�������������ع�ֵ.Warning ����ʵ������ÿ���ع�ʱ�䶼�ᵽ�����ֵ
    {FPS,               50},  //ͼ��֡��          ����ͷ�յ�����Զ���������FPS���������������Ϊ������������FPS
    {SET_COL,           MT9V03X_W}, //ͼ��������        ��Χ1-752     K60�ɼ�����������188
    {SET_ROW,           MT9V03X_H}, //ͼ��������        ��Χ1-480
    {LR_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ188 376 752ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {UD_OFFSET,         0},   //ͼ������ƫ����    ��ֵ ��ƫ��   ��ֵ ��ƫ��  ��Ϊ120 240 480ʱ�޷�����ƫ��    ����ͷ��ƫ�����ݺ���Զ��������ƫ�ƣ�������������ü�����������ƫ��
    {GAIN,              32},  //ͼ������          ��Χ16-64     ����������ع�ʱ��̶�������¸ı�ͼ�������̶�

    
    {INIT,              0}    //����ͷ��ʼ��ʼ��
};

//������ͷ�ڲ���ȡ������������
int16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //�Զ��ع�����      
    {EXP_TIME,          0},   //�ع�ʱ��          
    {FPS,               0},   //ͼ��֡��          
    {SET_COL,           0},   //ͼ��������        
    {SET_ROW,           0},   //ͼ��������        
    {LR_OFFSET,         0},   //ͼ������ƫ����    
    {UD_OFFSET,         0},   //ͼ������ƫ����    
    {GAIN,              0},   //ͼ������          
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷ�����жϺ���
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	
//  @note       �˺�����isr.c�� �������жϺ�������
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_uart_callback(void)
{
	while(uart_query(MT9V03X_COF_UART, &receive[receive_num]))
	{
		receive_num++;

        if(1==receive_num && 0XA5!=receive[0])  receive_num = 0;
        if(3 == receive_num)
        {
            receive_num = 0;
            uart_receive_flag = 1;
        }

	}
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��������ͷ�ڲ�������Ϣ
//  @param      uartn       ѡ��ʹ�õĴ���
//  @param      buff        ����������Ϣ�ĵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void set_config(UARTN_enum uartn, int16 buff[CONFIG_FINISH-1][2])
{
	uint16 temp, i;
    uint8  send_buffer[4];

    uart_receive_flag = 0;
    
    //���ò���  ������ο���������ֲ�
    //��ʼ��������ͷ�����³�ʼ��
    for(i=0; i<CONFIG_FINISH; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = (uint8)buff[i][0];
        temp = buff[i][1];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn,send_buffer,4);
        systick_delay_ms(STM0, 2);
    }
    //�ȴ�����ͷ��ʼ���ɹ�
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    while((0xff != receive[1]) || (0xff != receive[2]));
    //���ϲ��ֶ�����ͷ���õ�����ȫ�����ᱣ��������ͷ��51��Ƭ����eeprom��
    //����set_exposure_time�����������õ��ع����ݲ��洢��eeprom��
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�ڲ�������Ϣ
//  @param      uartn       ѡ��ʹ�õĴ���
//  @param      buff        ����������Ϣ�ĵ�ַ
//  @return     void
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
void get_config(UARTN_enum uartn, int16 buff[CONFIG_FINISH-1][2])
{
	uint16 temp, i;
    uint8  send_buffer[4];
    
    for(i=0; i<CONFIG_FINISH-1; i++)
    {
        send_buffer[0] = 0xA5;
        send_buffer[1] = GET_STATUS;
        temp = buff[i][0];
        send_buffer[2] = temp>>8;
        send_buffer[3] = (uint8)temp;
        
        uart_putbuff(uartn,send_buffer,4);
        
        //�ȴ����ܻش�����
        while(!uart_receive_flag);
        uart_receive_flag = 0;
        
        buff[i][1] = receive[1]<<8 | receive[2];
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ��ȡ����ͷ�̼��汾
//  @param      uartn       ѡ��ʹ�õĴ���
//  @return     void
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
uint16 get_version(UARTN_enum uartn)
{
    uint16 temp;
    uint8  send_buffer[4];
    send_buffer[0] = 0xA5;
    send_buffer[1] = GET_STATUS;
    temp = GET_VERSION;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
        
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    return ((uint16)(receive[1]<<8) | receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������������ͷ�ع�ʱ��
//  @param      uartn       ѡ��ʹ�õĴ���
//  @param      light       �����ع�ʱ��Խ��ͼ��Խ��������ͷ�յ������ݷֱ��ʼ�FPS��������ع�ʱ��������õ����ݹ�����ô����ͷ��������������ֵ
//  @return     uint16      ��ǰ�ع�ֵ������ȷ���Ƿ���ȷд��
//  @since      v1.0
//  Sample usage:           ���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
uint16 set_exposure_time(UARTN_enum uartn, uint16 light)
{
	uint16 temp;
    uint8  send_buffer[4];

    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_EXP_TIME;
    temp = light;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
    
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ������ͷ�ڲ��Ĵ�������д����
//  @param      uartn       ѡ��ʹ�õĴ���
//  @param      addr        ����ͷ�ڲ��Ĵ�����ַ
//  @param      data        ��Ҫд�������
//  @return     uint16      �Ĵ�����ǰ���ݣ�����ȷ���Ƿ�д��ɹ�
//  @since      v1.0
//  Sample usage:			���øú���ǰ���ȳ�ʼ������
//-------------------------------------------------------------------------------------------------------------------
uint16 set_mt9v03x_reg(UARTN_enum uartn, uint8 addr, uint16 data)
{
	uint16 temp;
    uint8  send_buffer[4];
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_ADDR;
    temp = addr;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
    systick_delay_ms(STM0, 10);
    
    send_buffer[0] = 0xA5;
    send_buffer[1] = SET_DATA;
    temp = data;
    send_buffer[2] = temp>>8;
    send_buffer[3] = (uint8)temp;
    
    uart_putbuff(uartn,send_buffer,4);
    
    //�ȴ����ܻش�����
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    
    temp = receive[1]<<8 | receive[2];
    return temp;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷ��ʼ��
//  @param      NULL
//  @return     void					
//  @since      v1.0
//  Sample usage:	ʹ��FLEXIO�ӿڲɼ�����ͷ	
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_init(void)
{
	uint8 i;
    camera_type = 1;//������������ͷ����

    boolean interrupt_state = disableInterrupts();

    uart_init (MT9V03X_COF_UART, 9600, MT9V03X_COF_UART_TX, MT9V03X_COF_UART_RX);	//��ʼ������ ��������ͷ
    enableInterrupts();//�����ж�

    //�ȴ�����ͷ�ϵ��ʼ���ɹ� ��ʽ�����֣���ʱ����ͨ����ȡ���õķ�ʽ ��ѡһ
    //systick_delay_ms(STM0, 1000);//��ʱ��ʽ
    get_config(MT9V03X_COF_UART, GET_CFG);//��ȡ���õķ�ʽ

    uart_receive_flag = 0;
    set_config(MT9V03X_COF_UART, MT9V03X_CFG);

    //��ȡ���ñ��ڲ鿴�����Ƿ���ȷ
    get_config(MT9V03X_COF_UART, GET_CFG);

    disableInterrupts();

	//����ͷ�ɼ���ʼ��
	//��ʼ�� ��������
	for(i=0; i<8; i++)
	{
		gpio_init((PIN_enum)(MT9V03X_DATA_PIN+i), GPI, 0, PULLUP);
	}

    link_list_num = eru_dma_init(MT9V03X_DMA_CH, GET_PORT_IN_ADDR(MT9V03X_DATA_PIN), mt9v03x_image[0], MT9V03X_PCLK_PIN, RISING, MT9V03X_W*MT9V03X_H);

    eru_init(MT9V03X_VSYNC_PIN, FALLING);	//��ʼ�����жϣ�������Ϊ�½��ش����ж�
    restoreInterrupts(interrupt_state);
}


uint8   mt9v03x_finish_flag = 0;    //һ��ͼ��ɼ���ɱ�־λ
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷ���ж�
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				�˺�����isr.c�б�eru��GPIO�жϣ��жϵ���
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_vsync(void)
{
	CLEAR_GPIO_FLAG(MT9V03X_VSYNC_PIN);

	if(!mt9v03x_finish_flag)//�鿴ͼ�������Ƿ�ʹ����ϣ����δʹ������򲻿�ʼ�ɼ���������ַ��ʳ�ͻ
	{
		dma_start(MT9V03X_DMA_CH);
	}

}

uint8	mt9v03x_dma_int_num;	//��ǰDMA�жϴ���
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X����ͷDMA����ж�
//  @param      NULL
//  @return     void			
//  @since      v1.0
//  Sample usage:				�˺�����isr.c�б�dma�жϵ���
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_dma(void)
{
	CLEAR_DMA_FLAG(MT9V03X_DMA_CH);
	mt9v03x_dma_int_num++;

	if(mt9v03x_dma_int_num >= link_list_num)
	{
		//�ɼ����
		mt9v03x_dma_int_num = 0;
		mt9v03x_finish_flag = 1;//һ��ͼ��Ӳɼ���ʼ���ɼ�������ʱ3.8MS����(50FPS��188*120�ֱ���)
		dma_stop(MT9V03X_DMA_CH);

	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���������ͷͼ��������λ���鿴ͼ��
//  @param      uartn			ʹ�õĴ��ں�
//  @param      image			��Ҫ���͵�ͼ���ַ
//  @param      width			ͼ�����
//  @param      height			ͼ�����
//  @return     void			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_03x(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height)
{
	uart_putchar(uartn,0x00);uart_putchar(uartn,0xff);uart_putchar(uartn,0x01);uart_putchar(uartn,0x01);//��������
    uart_putbuff(uartn, image, width*height);  //����ͼ��
}
/***************************************************************
�򻯴��  1.01ms  ��������ʱ 1.5ms    ������Сʱ0.7ms

* �������ƣ�uint8 otsuThreshold(uint8 Image[ROW][COL], uint16 col, uint16 row)
* ����˵������ȡͼ��ĻҶ���Ϣ ȡ�����ֵ
* ����˵����
* �������أ�void uint8 threshold
* �޸�ʱ�䣺2018��3��7��
* �� ע��
***************************************************************/
unsigned char adapt_otsuThreshold(uint8 *image, uint16 col, uint16 row, unsigned char *threshold)   //ע�������ֵ��һ��Ҫ��ԭͼ��
{
       #define GrayScale 256
       uint16 width = col;
       uint16 height = row;
       int pixelCount[GrayScale];  //ÿ�����ص�ĸ���
       float pixelPro[GrayScale];  //ÿ�����ص�ռ�����ص�ı���
       int i, j, pixelSum = width * height/4;
       //uint8 threshold = 0;
       uint8* data = image;  //ָ���������ݵ�ָ��
       for (i = 0; i < GrayScale; i++)
       {
	      pixelCount[i] = 0;
	      pixelPro[i] = 0;
       }

       uint32 gray_sum=0;
       //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
       for (i = 0; i < height; i+=2)
       {
	      for (j = 0; j < width; j+=2)
	      {
		     pixelCount[(int)data[i * width + j]]++;  //����ǰ�ĵ������ֵ��Ϊ����������±�
		     gray_sum+=(int)data[i * width + j];       //�Ҷ�ֵ�ܺ�
	      }
       }

       //����ÿ������ֵ�ĵ�������ͼ���еı���

       for (i = 0; i < GrayScale; i++)
       {
	      pixelPro[i] = (float)pixelCount[i] / pixelSum;

       }

       //�����Ҷȼ�[0,255]
       float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;



       w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
       for (j = 0; j < GrayScale; j++)
       {

	      w0 += pixelPro[j];  //��������ÿ���Ҷ�ֵ�����ص���ռ����֮��   ���������ֵı���
	      u0tmp += j * pixelPro[j];  //�������� ÿ���Ҷ�ֵ�ĵ�ı��� *�Ҷ�ֵ

	      w1=1-w0;
	      u1tmp=gray_sum/pixelSum-u0tmp;

	      u0 = u0tmp / w0;              //����ƽ���Ҷ�
	      u1 = u1tmp / w1;              //ǰ��ƽ���Ҷ�
	      u = u0tmp + u1tmp;            //ȫ��ƽ���Ҷ�
	      deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
	      if (deltaTmp > deltaMax)
	      {
		     deltaMax = deltaTmp;
		     *threshold = j;
	      }
	      if (deltaTmp < deltaMax)
	      {
		     *threshold+=0;
		     break;
	      }
       }
       return *threshold;
}
/*----------------------------------------------------------------------------------------------------------------
*  @brief  	ͼ����뺯��  ����������3/4
*  @param  	*p ͼ�������ַ
*		*p1 ת��ͼ���ַ
*		rowͼ����
*                  colͼ����
*  @return	void
*  @since	v1.0
*  Sample usage:      halve_image(image_buff[0],image[0],ROW,COL);    //���image[0]
//-----------------------------------------------------------------------------------------------------------------*/
void halve_image(unsigned char *p_in,unsigned char  *p_out,unsigned char row,unsigned char col) //ͼ�����
{
       int i, j;
       for (i = 0; i<row/2; i++)
       {
	      for (j = 0;j<col/2; j++)
	      {
		     *(p_out+i*col/2+j)=*(p_in+i*2*col+j*2);
	      }
       }

}

/********************************
             ȫ�ֶ�ֵ��
********************************/
uint8 BinaryImage[ROW][COL];
uint8 threshold;
void Image_Binary(uint8 Image[ROW][COL], uint8 Binary_Image[ROW][COL], int GateValue)
{
    for(int i = 0; i < ROW; i++)
    {
      for(int j = 0; j < COL; j++)
      {
        if(Image[i][j] > GateValue)
        {
          Binary_Image[i][j] = 255;
        }
        else
        {
          Binary_Image[i][j] = 0;
        }
      }
    }
}



