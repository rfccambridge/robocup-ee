#include <avr/io.h>
#include "SPISlave.h"
#include "Command.h"
#include "EELib.h"
#include "KickerBoard.h"
#include "Breakbeam.h"
#include "CapCharger.h"
#include "Kicker.h"

SPISlave spi = SPISlave();
Command command;
Breakbeam breakbeam = Breakbeam(BB_OUT, BB_IN);
CapCharger capCharger = CapCharger(CHARGE, DONE, DISCHARGE, DIVCAP, CHARGE_LIMIT);
Kicker kicker = Kicker(KICK_ENABLE, CHIP_ENABLE);
bool bbKickPending = false;

int main(void)
{
	bbKickPending = false;
	
	// At startup, stop charging
	capCharger.stopCharge();
	DDRC = 0xFF;
	PORTC = 0x00;
    while(1)
    {
		setBit(BLED1,true);
        spi.ReceiveSPI();
		if(spi.GetCommand(command))
		{
			setBit(BLED2, true);
			processCommand(command);
		}
		capCharger.update();
		breakbeam.update();
		if(bbKickPending && breakbeam.isBroken())
		{
			kicker.kick();
			bbKickPending = false;
		}
    }
}

int processCommand(Command &command)
{
	switch(command.GetType())
	{
		case Command::CHARGE_COMMAND:
			handleChargeCommand((ChargeCommand&) command);
			break;
		case Command::KICK_COMMAND:
			handleKickCommand((KickCommand&) command);
			break;
	}
	return 0x42;
}

void handleChargeCommand(ChargeCommand &command)
{
	if(command.discharge)
	{
		capCharger.stopCharge();
		capCharger.discharge();
		bbKickPending = false;
	}
	else
	{
		// TODO: Check if this needs scaling
		capCharger.startCharge(command.voltage);
		bbKickPending = false;
	}
}

void handleKickCommand(KickCommand &command)
{
	if(command.breakbeam)
	{
		bbKickPending = true;
	}
	else
	{
		kicker.kick();
	}
}