#include "common.h"

#include "zf_spi.h"
#include "zf_gpio.h"
#include "zf_assert.h"
#include "zf_stm_systick.h"
#include "SEEKFREE_PRINTF.h"
#include "isr.h"
#include "Hc_sr04.h"

void Sr04_init (void)
{  gpio_init(TRIG_PIN, GPO, 1, PULLDOWN);
   gpio_init(ECHO_PIN, GPI, 1, PULLDOWN);
   //使用CCU6_0模块的通道0 产生一个 10ms的周期中断
   pit_interrupt_ms(CCU6_0, PIT_CH0, 100);

   pit_init(CCU6_0, PIT_CH1, 1);


}

uint32 get_distance(STMN_enum stmn)
{   uint32 timevar1 = 0,timevar2 = 0;
    uint32 distance = 0;


	if(Flag_10ms)
	    {


	    	gpio_set(TRIG_PIN,1);            			//产生触发脉冲
	    	systick_delay_us(STM0, 20);
	        gpio_set(TRIG_PIN,0);

	        while(gpio_get(ECHO_PIN) == 0)
	       {timevar1 = systick_start(STM0);  					  //停止计时，获取计时时间



	        	       		}


	       	while(gpio_get(ECHO_PIN) == 1)
	       		{timevar1 = systick_getval(STM0)/100;
	       		if(timevar1>20000)
	       		{break;}//停止计时，获取计时时间



	       		}           //等待电平变低，高电平一直等待

	       	 					  //停止计时，获取计时时间
	       	distance = (int32)(timevar1*(331.4+0.607*10)/2000);//加上温度补偿，单位1/100 mms
	       	//pit_disable_interrupt(CCU6_0, PIT_CH1);
	       	time_us=0;

	    	Flag_10ms=0;




	            			//产生一个20us的高电平脉冲



}
	return timevar1;
}
