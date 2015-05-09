#include <avr/io.h>
#include "SPISlave.h"

int main(void)
{	
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