#include <avr/io.h>
#include "SPIMaster.h"

int main(void)
{
	SPIMaster spi;
    while(1)
    {
		SetWheelSpeedCommand command(SetWheelSpeedCommand::WHEEL_LB, -100);
		char r;
        spi.SendCommand(SPIMaster::MOTOR_BOARD_SLAVE, command, &r);
    }
}