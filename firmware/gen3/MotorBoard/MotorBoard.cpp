#include <avr/io.h>

#include "SPISlave.h"

int main(void)
{
	// Set timer to fast PWM mode, with no prescaling, set on compare match,
	TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << CS00) | (1 << COM0A0) | (1 << COM0A1);
	
	// Set OC0A as output
	DDRB |= (1 << PINB4);
	
	// Set duty cycle to ~25% (64/255)
	OCR0A = 64;
	
	SPISlave spi;
    while(1)
    {
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