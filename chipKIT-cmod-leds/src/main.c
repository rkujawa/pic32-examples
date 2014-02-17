#include <plib.h>
#include <stdint.h>

#include "delay.h"

int
main(void)
{
	TRISBbits.TRISB12 = 0;
	TRISC = 0;
	ANSELC = 0;

	while(1)
	{
		LATBbits.LATB12 = 0;
		LATC = 0;
		delay_us(1000000);
		LATBbits.LATB12 = 1;
		LATC = 0xFF;
		delay_us(1000000);
	}
}

