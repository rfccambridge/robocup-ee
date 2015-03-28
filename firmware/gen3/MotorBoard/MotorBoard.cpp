#include <avr/io.h>

#include "SPISlave.h"
void handleQEI(Wheel wheel);

int main(void)
{
	SPISlave spi;
    while(1)
    {
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
    }
}

void handleQEI(Wheel wheel)
{
    
}