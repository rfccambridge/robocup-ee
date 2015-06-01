#include <avr/io.h>
#include "SPIMaster.h"
#include <util/delay.h>

int main(void)
{
	SPIMaster spi;
	
	int pin = 0;
	bool status = true;
	
	// setup indicator LED
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// read in dip switches
	DDRA = 0x00;
	
    while(1)
    {
		// send and display bot ID
		PORTC = PINA & 0x0F;
		spi.sendChar(PORTC);
		_delay_ms(50);
    }
}