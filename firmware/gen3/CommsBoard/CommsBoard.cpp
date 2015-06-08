#include <avr/io.h>
#include "SPIMaster.h"
#include "EELib.h"
#include "CommsBoard.h"
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
	bool blink = true;
	
    while(1)
    {
		blink = !blink;
		bool led = getBit(BID3);
		setBit(GLED1, led);
		setBit(GLED2, blink);
		
		
		// create an LED command based on bot ID
		LEDCommand led_cmd = LEDCommand(0, led);
		
		// send message
		char reply;
		bool result;
		result = spi.SendCommand(0, led_cmd, &reply);
		
		// indicate status
		bool good = (reply == 0x42);
		
		//PORTC = reply;
		//(blink << 0) | (led << 1) | (result << 2) | (good << 3);
		_delay_ms(500);
    }
}