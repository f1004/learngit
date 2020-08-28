

#include "headfile.h"
#include "isr.h"
#include "Ks103.h"


extern int set_speed;

#pragma section all "cpu0_dsram"

int core0_main(void)
{
	disableInterrupts();

	get_clk();//获取时钟频率  务必保留

    enableInterrupts();

    while (TRUE)
    {}
}

#pragma section all restore
