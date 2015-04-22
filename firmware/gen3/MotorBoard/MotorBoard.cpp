#include <avr/io.h>

#include "SPISlave.h"
#include <util/delay.h>

int main(void)
{
	// Enable system clock setting
	CLKPR = (1 << CLKPCE);
	
	
	CLKPR = (1 << CLKPS0);
	// Set timer to fast PWM mode, with no prescaling, clear on compare match,
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << CS00) | (1 << COM0A1);
	TCNT0 =  
	// Set OC0A as output
	DDRB |= (1 << PINB4);
	
	// Set duty cycle to ~25% (64/255)
	OCR0A = 64;
	
	SPISlave spi;
    while(1)
    {
		_delay_ms(500);
		OCR0A += 10;
		/*
		spi.ReceiveSPI();
		
		Command command;
		bool hasCommand = spi.GetCommand(&command);
		if(hasCommand) {
			char reply = 0;
			switch(command.GetType()) {
			case Command::WHEEL_SPEED_COMMAND:
				SetWheelSpeedCommand* c = (SetWheelSpeedCommand*)&command;
				// TODO: execute command
				break;
			}
			
			spi.SetReply(reply);
		}
		*/
		
    }
}