#include <avr/io.h>
#include "SPISlave.h"
#include "EELib.h"

void init(void);
void setBrake(bool enable);
void setDirection(PWM pwmNum, bool dir);

int main(void)
{	
	init();
	SPISlave spi;
	spi.ReceiveSPI();
	Command command;
	bool hasCommand = spi.GetCommand(&command);
	
	if(hasCommand)
	{
		char reply = 0;
		switch(command.GetType())
		{
			case Command::WHEEL_SPEED_COMMAND:
			SetWheelSpeedCommand* c = (SetWheelSpeedCommand*)&command;
			// TODO: execute command
			break;
		}
			
		spi.SetReply(reply);
	}
}

// Set up system clock to max frequency and enable pins as output
void init(void)
{
	// Disable system clock prescaling (max clock frequency)
	CLKPR = (1 << CLKPCE);
	CLKPR = (1 << CLKPS0);
	
	// Enable break and dir pins as output
	DDRD |= (1 << PIND0) | (1 << PIND1) | (1 << PIND2) | (1 << PIND3) | (1 << PIND4);
}

// Set the break on if true (D4 low), otherwise turn break off (D4 high)
void setBrake(bool enable)
{
	setBit(&PIND, PIND4, !enable); 
}

// Given a PWM line number and a direction as bool, sets the direction of that motor
void setDirection(PWM pwmNum, bool dir)
{
	switch (pwmNum)
	{
		case PWM1:
			setBit(&PIND, PIND0, dir);
			break;
		case PWM2:
			setBit(&PIND, PIND1, dir);
			break;
		case PWM3:
			setBit(&PIND, PIND2, dir);
			break;
		case PWM4:
			setBit(&PIND, PIND3, dir);
			break;
	}
}