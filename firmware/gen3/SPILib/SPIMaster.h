#ifndef __SPIMASTER_H__
#define __SPIMASTER_H__

#include "Command.h"

class SPIMaster {
	public:
	static const char MOTOR_BOARD_SLAVE = 0;
	static const char KICKER_BOARD_SLAVE = 1;
	
	SPIMaster();
	
	// sends command
	// synchronous, waits for reply
	// returns true if successful
	// slave is the bit number of port f that is the slave select to enable
	// does not guarantee no duplicates are sent, so commands should be written with this in mind
	bool SendCommand(char slave, Command c, char* reply);
	
	// sends simple char for debugging, sends to all
	void sendChar(char c);
};

#endif /* __SPIMASTER_H__ */