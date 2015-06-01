#include <avr/io.h>
#include "SPISlave.h"
#include "EELib.h"
#include "MotorBoard.h"
#include <util/delay.h>

int main(void)
{	
	//init();
	SPISlave spi;
	//spi.ReceiveSPI();
	Command command;
	
	
	// setup LEDs
	DDRC = 0xFF;
	PORTC = 0x00;
	
	while (1) {
		char c = spi.getChar();
		PORTC = c;
	}
	
	while(1) {
		PORTC ^= 0x02; // flip 2nd LED
		
		bool hasCommand = spi.GetCommand(&command);
		if(hasCommand)
		{
			PORTC |= 0x04; // turn on 3rd LED
			char reply = 0;
			switch(command.GetType())
			{
				case Command::WHEEL_SPEED_COMMAND:
					//SetWheelSpeedCommand* c = (SetWheelSpeedCommand*)&command;
					// TODO: execute command
				break;
			
				case Command::LED_COMMAND:
					PORTC |= 0x08; // turn on 4th LED
					LEDCommand* c2 = (LEDCommand*)&command;
					int pin = c2->getPin();
					bool on = c2->getStatus();
				
					// turn on / off LED
					
					if (on) {
						PORTC |= 1 << pin;
					}
					else {
						PORTC &= ~(1 << pin);
					}
			}
			
			spi.SetReply(reply);
		}
		else {
			// no command
			PORTC &= ~(0x04); // turn off 3rd LED
		}
		_delay_ms(100);
	}
}

void init(void)
{
	// Disable system clock prescaling (max clock frequency)
	CLKPR = (1 << CLKPCE);
	CLKPR = (1 << CLKPS0);
	
	// Enable break and dir pins as output
	DDRD |= (1 << PIND0) | (1 << PIND1) | (1 << PIND2) | (1 << PIND3) | (1 << PIND4);
}

void setBrake(bool enable)
{
	setBit(&PIND, PIND4, !enable); 
}

void setDirection(PWM pwmNum, bool dir)
{
	switch (pwmNum)
	{
		case OUTPUT1:
			setBit(&PIND, PIND0, dir);
			break;
		case OUTPUT2:
			setBit(&PIND, PIND1, dir);
			break;
		case OUTPUT3:
			setBit(&PIND, PIND2, dir);
			break;
		case OUTPUT4:
			setBit(&PIND, PIND3, dir);
			break;
	}
}