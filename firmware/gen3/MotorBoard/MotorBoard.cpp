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
	TCCR1A |= (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
	TCCR1B |= (1 << WGM12) | (1 << CS10);
	TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << CS20) | (1 << COM2A1);
	TCCR1C &= (0 << FOC1A) | (0 << FOC1B);
	
	// Set OC0A as output
	DDRB |= (1 << PINB4) | (1 << PINB5) | (1 << PINB6) | (1 << PINB7);
	
	PORTB |= (1 << PINB6);
	DDRD |= (1 << PIND4) | (1 << PIND0) | (1 << PIND1) | (1 << PIND2) | (1 << PIND3);
	PORTD |= (1 << PIND4) | (1 << PIND0) | (1 << PIND1) | (1 << PIND2) | (1 << PIND3);
	
	// Set duty cycle to ~25% (64/255)
	OCR0A = 40;
	OCR1A = 255;
	//OCR1B = 40;
	//OCR2A = 40;
	
	SPISlave spi;
    while(1)
    {
		while(OCR0A < 240)
		{
			_delay_ms(500);
			OCR0A += 10;
			//OCR1A += 10;
			//OCR1B += 10;
			//OCR2A += 10;
		}
		
		while(OCR0A > 20)
		{
			_delay_ms(500);
			OCR0A -= 10;
			//OCR1A -= 10;
			//OCR1B -= 10;
			//OCR2A -= 10;
		}
		
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