#include <avr/io.h>
#include "SPISlave.h"
#include "EELib.h"
#include "MotorBoard.h"

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