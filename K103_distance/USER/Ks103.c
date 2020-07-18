
#include "common.h"
#include "headfile.h"
#include "Ks103.h"
#include "isr.h"
void Ks103_init(void)
{
	//使用CCU6_0模块的通道0 产生一个 10ms的周期中断
		pit_interrupt_ms(CCU6_0, PIT_CH0, 10);

	    uart_init(UART_0, 9600, UART0_TX_P14_0, UART0_RX_P14_1);//MODE connect to GND
	    //用户在此处调用各种初始化函数等
		uart_putchar(UART_0, 0xe8);
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0x02);
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0x70);
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0xbc);
		systick_delay_us(STM0, 20);




}

int Ks103_getdistance(void)
{
	  uint8 data;
      int distance;





	    	uart_putchar(UART_0, 0xe8);
	        systick_delay_us(STM0, 20);
	    	uart_putchar(UART_0, 0x02);
	    	systick_delay_us(STM0, 20);
	    	uart_putchar(UART_0, 0xbc);
	    	systick_delay_us(STM0, 20);
	    	uart_putchar(UART_0, 0xc9);
	    	systick_delay_us(STM0, 20);
	    	uart_getchar(UART_0,&data);
	    	distance =  data << 8;
	    	uart_getchar(UART_0,&data);
	    	distance |= data;






            return distance;


}


