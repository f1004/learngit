/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		总钻风
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		tasking v6.3r1
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note
					接线定义：
					------------------------------------
					模块管脚            			单片机管脚
					SDA(51的RX)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_COF_UART_TX宏定义
					SCL(51的TX)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_COF_UART_RX宏定义
					场中断(VSY)         		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_VSYNC_PIN宏定义
					行中断(HREF)				程序没有使用，因此不连接
					像素中断(PCLK)      		查看SEEKFREE_MT9V03X.h文件中的MT9V03X_PCLK_PIN宏定义
					数据口(D0-D7)			查看SEEKFREE_MT9V03X.h文件中的MT9V03X_DATA_PIN宏定义
					------------------------------------

					默认分辨率是           			188*120
					默认FPS                 50帧
 ********************************************************************************************************************/


#include "IfxDma.h"
#include "IfxScuEru.h"
#include "zf_stm_systick.h"
#include "zf_gpio.h"
#include "zf_eru.h"
#include "zf_eru_dma.h"
#include "SEEKFREE_MT9V03X.h"


//必须4字节对齐
IFX_ALIGN(4) uint8 mt9v03x_image[MT9V03X_H][MT9V03X_W];

uint8   receive[3];
uint8   receive_num = 0;
vuint8  uart_receive_flag;
uint8 image_half[ROW/2][COL/2];//压缩后图像
uint8   link_list_num;

//需要配置到摄像头的数据
int16 MT9V03X_CFG[CONFIG_FINISH][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置      范围1-63 0为关闭 如果自动曝光开启  EXP_TIME命令设置的数据将会变为最大曝光时间，也就是自动曝光时间的上限
                              //一般情况是不需要开启这个功能，因为比赛场地光线一般都比较均匀，如果遇到光线非常不均匀的情况可以尝试设置该值，增加图像稳定性
    {EXP_TIME,          50}, //曝光时间          摄像头收到后会自动计算出最大曝光时间，如果设置过大则设置为计算出来的最大曝光值.Warning 经过实践发现每次曝光时间都会到达最大值
    {FPS,               50},  //图像帧率          摄像头收到后会自动计算出最大FPS，如果过大则设置为计算出来的最大FPS
    {SET_COL,           MT9V03X_W}, //图像列数量        范围1-752     K60采集不允许超过188
    {SET_ROW,           MT9V03X_H}, //图像行数量        范围1-480
    {LR_OFFSET,         0},   //图像左右偏移量    正值 右偏移   负值 左偏移  列为188 376 752时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {UD_OFFSET,         0},   //图像上下偏移量    正值 上偏移   负值 下偏移  行为120 240 480时无法设置偏移    摄像头收偏移数据后会自动计算最大偏移，如果超出则设置计算出来的最大偏移
    {GAIN,              32},  //图像增益          范围16-64     增益可以在曝光时间固定的情况下改变图像亮暗程度


    {INIT,              0}    //摄像头开始初始化
};

//从摄像头内部获取到的配置数据
int16 GET_CFG[CONFIG_FINISH-1][2]=
{
    {AUTO_EXP,          0},   //自动曝光设置
    {EXP_TIME,          0},   //曝光时间
    {FPS,               0},   //图像帧率
    {SET_COL,           0},   //图像列数量
    {SET_ROW,           0},   //图像行数量
    {LR_OFFSET,         0},   //图像左右偏移量
    {UD_OFFSET,         0},   //图像上下偏移量
    {GAIN,              0},   //图像增益
};


//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X摄像头串口中断函数
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:
//  @note       此函数在isr.c中 被串口中断函数调用
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
//  @brief      配置摄像头内部配置信息
//  @param      uartn       选择使用的串口
//  @param      buff        发送配置信息的地址
//  @return     void
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
//-------------------------------------------------------------------------------------------------------------------
void set_config(UARTN_enum uartn, int16 buff[CONFIG_FINISH-1][2])
{
	uint16 temp, i;
    uint8  send_buffer[4];

    uart_receive_flag = 0;

    //设置参数  具体请参看问题锦集手册
    //开始配置摄像头并重新初始化
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
    //等待摄像头初始化成功
    while(!uart_receive_flag);
    uart_receive_flag = 0;
    while((0xff != receive[1]) || (0xff != receive[2]));
    //以上部分对摄像头配置的数据全部都会保存在摄像头上51单片机的eeprom中
    //利用set_exposure_time函数单独配置的曝光数据不存储在eeprom中
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头内部配置信息
//  @param      uartn       选择使用的串口
//  @param      buff        接收配置信息的地址
//  @return     void
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
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

        //等待接受回传数据
        while(!uart_receive_flag);
        uart_receive_flag = 0;

        buff[i][1] = receive[1]<<8 | receive[2];
    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      获取摄像头固件版本
//  @param      uartn       选择使用的串口
//  @return     void
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
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

    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;

    return ((uint16)(receive[1]<<8) | receive[2]);
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      单独设置摄像头曝光时间
//  @param      uartn       选择使用的串口
//  @param      light       设置曝光时间越大图像越亮，摄像头收到后会根据分辨率及FPS计算最大曝光时间如果设置的数据过大，那么摄像头将会设置这个最大值
//  @return     uint16      当前曝光值，用于确认是否正确写入
//  @since      v1.0
//  Sample usage:           调用该函数前请先初始化串口
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

    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;

    temp = receive[1]<<8 | receive[2];
    return temp;

}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      对摄像头内部寄存器进行写操作
//  @param      uartn       选择使用的串口
//  @param      addr        摄像头内部寄存器地址
//  @param      data        需要写入的数据
//  @return     uint16      寄存器当前数据，用于确认是否写入成功
//  @since      v1.0
//  Sample usage:			调用该函数前请先初始化串口
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

    //等待接受回传数据
    while(!uart_receive_flag);
    uart_receive_flag = 0;

    temp = receive[1]<<8 | receive[2];
    return temp;

}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X摄像头初始化
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:	使用FLEXIO接口采集摄像头
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_init(void)
{
	uint8 i;
    camera_type = 1;//设置连接摄像头类型

    boolean interrupt_state = disableInterrupts();

    uart_init (MT9V03X_COF_UART, 9600, MT9V03X_COF_UART_TX, MT9V03X_COF_UART_RX);	//初始换串口 配置摄像头
    enableInterrupts();//开启中断

    //等待摄像头上电初始化成功 方式有两种：延时或者通过获取配置的方式 二选一
    //systick_delay_ms(STM0, 1000);//延时方式
    get_config(MT9V03X_COF_UART, GET_CFG);//获取配置的方式

    uart_receive_flag = 0;
    set_config(MT9V03X_COF_UART, MT9V03X_CFG);

    //获取配置便于查看配置是否正确
    get_config(MT9V03X_COF_UART, GET_CFG);

    disableInterrupts();

	//摄像头采集初始化
	//初始化 数据引脚
	for(i=0; i<8; i++)
	{
		gpio_init((PIN_enum)(MT9V03X_DATA_PIN+i), GPI, 0, PULLUP);
	}

    link_list_num = eru_dma_init(MT9V03X_DMA_CH, GET_PORT_IN_ADDR(MT9V03X_DATA_PIN), mt9v03x_image[0], MT9V03X_PCLK_PIN, RISING, MT9V03X_W*MT9V03X_H);

    eru_init(MT9V03X_VSYNC_PIN, FALLING);	//初始化场中断，并设置为下降沿触发中断
    restoreInterrupts(interrupt_state);
}


uint8   mt9v03x_finish_flag = 0;    //一场图像采集完成标志位
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X摄像头场中断
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				此函数在isr.c中被eru（GPIO中断）中断调用
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_vsync(void)
{
	CLEAR_GPIO_FLAG(MT9V03X_VSYNC_PIN);

	if(!mt9v03x_finish_flag)//查看图像数组是否使用完毕，如果未使用完毕则不开始采集，避免出现访问冲突
	{
		dma_start(MT9V03X_DMA_CH);
	}

}

uint8	mt9v03x_dma_int_num;	//当前DMA中断次数
//-------------------------------------------------------------------------------------------------------------------
//  @brief      MT9V03X摄像头DMA完成中断
//  @param      NULL
//  @return     void
//  @since      v1.0
//  Sample usage:				此函数在isr.c中被dma中断调用
//-------------------------------------------------------------------------------------------------------------------
void mt9v03x_dma(void)
{
	CLEAR_DMA_FLAG(MT9V03X_DMA_CH);
	mt9v03x_dma_int_num++;

	if(mt9v03x_dma_int_num >= link_list_num)
	{
		//采集完成
		mt9v03x_dma_int_num = 0;
		mt9v03x_finish_flag = 1;//一副图像从采集开始到采集结束耗时3.8MS左右(50FPS、188*120分辨率)
		dma_stop(MT9V03X_DMA_CH);

	}
}



//-------------------------------------------------------------------------------------------------------------------
//  @brief      总钻风摄像头图像发送至上位机查看图像
//  @param      uartn			使用的串口号
//  @param      image			需要发送的图像地址
//  @param      width			图像的列
//  @param      height			图像的行
//  @return     void
//  @since      v1.0
//  Sample usage:
//-------------------------------------------------------------------------------------------------------------------
void seekfree_sendimg_03x(UARTN_enum uartn, uint8 *image, uint16 width, uint16 height)
{
	uart_putchar(uartn,0x00);uart_putchar(uartn,0xff);uart_putchar(uartn,0x01);uart_putchar(uartn,0x01);//发送命令
    uart_putbuff(uartn, image, width*height);  //发送图像
}
/***************************************************************
简化大津法  1.01ms  计算量大时 1.5ms    计算量小时0.7ms

* 函数名称：uint8 otsuThreshold(uint8 Image[ROW][COL], uint16 col, uint16 row)
* 功能说明：获取图像的灰度信息 取最佳阈值
* 参数说明：
* 函数返回：void uint8 threshold
* 修改时间：2018年3月7日
* 备 注：
***************************************************************/
unsigned char adapt_otsuThreshold(uint8 *image, uint16 col, uint16 row, unsigned char *threshold)   //注意计算阈值的一定要是原图像
{
       #define GrayScale 256
       uint16 width = col;
       uint16 height = row;
       int pixelCount[GrayScale];  //每个像素点的个数
       float pixelPro[GrayScale];  //每个像素点占总像素点的比例
       int i, j, pixelSum = width * height/4;
       //uint8 threshold = 0;
       uint8* data = image;  //指向像素数据的指针
       for (i = 0; i < GrayScale; i++)
       {
	      pixelCount[i] = 0;
	      pixelPro[i] = 0;
       }

       uint32 gray_sum=0;
       //统计灰度级中每个像素在整幅图像中的个数
       for (i = 0; i < height; i+=2)
       {
	      for (j = 0; j < width; j+=2)
	      {
		     pixelCount[(int)data[i * width + j]]++;  //将当前的点的像素值作为计数数组的下标
		     gray_sum+=(int)data[i * width + j];       //灰度值总和
	      }
       }

       //计算每个像素值的点在整幅图像中的比例

       for (i = 0; i < GrayScale; i++)
       {
	      pixelPro[i] = (float)pixelCount[i] / pixelSum;

       }

       //遍历灰度级[0,255]
       float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;



       w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
       for (j = 0; j < GrayScale; j++)
       {

	      w0 += pixelPro[j];  //背景部分每个灰度值的像素点所占比例之和   即背景部分的比例
	      u0tmp += j * pixelPro[j];  //背景部分 每个灰度值的点的比例 *灰度值

	      w1=1-w0;
	      u1tmp=gray_sum/pixelSum-u0tmp;

	      u0 = u0tmp / w0;              //背景平均灰度
	      u1 = u1tmp / w1;              //前景平均灰度
	      u = u0tmp + u1tmp;            //全局平均灰度
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
*  @brief  	图像减半函数  数据量减少3/4
*  @param  	*p 图像数组地址
*		*p1 转换图像地址
*		row图像行
*                  col图像列
*  @return	void
*  @since	v1.0
*  Sample usage:      halve_image(image_buff[0],image[0],ROW,COL);    //输出image[0]
//-----------------------------------------------------------------------------------------------------------------*/
void halve_image(unsigned char *p_in,unsigned char  *p_out,unsigned char row,unsigned char col) //图像减半
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
             全局二值化
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




