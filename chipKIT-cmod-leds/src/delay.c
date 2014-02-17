#include <plib.h>
#include <stdint.h>

#include "delay.h"

/* delay in microseconds */
void
delay_us(uint32_t delay)
{
	uint32_t ticks;	/* 1 core tick = 2 SYS ticks */

	us_ticks = (F_CPU/1000000)/2;
	WriteCoreTimer(0);

	while(ReadCoreTimer() < delay*us_ticks); /* do nothing */
} 
