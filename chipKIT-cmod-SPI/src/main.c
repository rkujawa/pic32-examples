#include <plib.h>

#define CSEE  PORTCbits.RC0 
#define TCSEE TRISCbits.TRISC0 

#define SPI_CONF 0x8120
#define SPI_BAUD 15

#define SEE_WRSR 1 
#define SEE_WRITE 2 
#define SEE_READ 3 
#define SEE_WDI 4 
#define SEE_STAT 5 
#define SEE_WEN 6

int
writeSPI1(int i)
{
	SPI1BUF = i;
	while(!SPI1STATbits.SPIRBF); 

	return SPI1BUF;
}

int
main(void)
{
	int i;

	TCSEE = 0;
	CSEE = 1;
	SPI1CON = SPI_CONF;
	SPI1BRG = SPI_BAUD;

	PPSInput(2, SDI1, RPB5); 
	PPSOutput(3, RPC1, SDO1); 

	while(1) {
		SPI_CONF;
		SPI_BAUD;
		CSEE = 0;
		writeSPI1( SEE_STAT);
		i = writeSPI1( 0);
		CSEE=1;
	}
}

