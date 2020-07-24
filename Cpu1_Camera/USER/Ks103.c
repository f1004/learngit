
#include "common.h"
#include "headfile.h"
#include "Ks103.h"
#include "isr.h"
void Ks103_init(void)
{
	//ʹ��CCU6_0ģ���ͨ��0 ����һ�� 10ms�������ж�
		pit_interrupt_ms(CCU6_0, PIT_CH0, 10);

	    uart_init(UART_0, 9600, UART0_TX_P14_0, UART0_RX_P14_1);//MODE connect to GND
	    //�û��ڴ˴����ø��ֳ�ʼ��������
		uart_putchar(UART_0, 0xe8);// uart address
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0x02); //register
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0x70);//first class denoise
		systick_delay_us(STM0, 20);
		uart_putchar(UART_0, 0xbc);//0-11m distance feedback with temporary compensate
		systick_delay_us(STM0, 20);




}

int Ks103_getdistance(void)
{
	  uint8 data;
      int distance;





	    	uart_putchar(UART_0, 0xe8);// uart address
	        systick_delay_us(STM0, 20);
	    	uart_putchar(UART_0, 0x02);//register
	    	systick_delay_us(STM0, 20);
	    	uart_putchar(UART_0, 0xbc);//0-11m distance feedback with temporary compensate
	    	systick_delay_us(STM0, 20);
//	    	uart_putchar(UART_0, 0xc9);
//	    	systick_delay_us(STM0, 20);
	    	uart_getchar(UART_0,&data);
	    	distance =  data << 8;
	    	uart_getchar(UART_0,&data);
	    	distance |= data;






            return distance;


}


