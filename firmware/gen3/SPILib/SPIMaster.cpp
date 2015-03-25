#include "SPIMaster.h"
#include <avr/io.h>
#include "Constants.h"

const char WAIT_FOR_REPLY = 3; // the number of times to try to get a reply from slave (since getting a reply requires sending something)

SPIMaster::SPIMaster() {
	// low 5 bits of port f are slave selects; set them to outputs
	DDRF = 0b00011111;
	
	// set MOSI, SCK, and SS as outputs
	DDRB |= 0b00000111;
	
	// enable SPI, master mode, clock f_ck/64
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

void waitForTransmit() {
	while(!(SPSR & (1<<SPIF))) ;
}

bool SPIMaster::SendCommand(char slave, Command c, char* reply) {
	bool success = true;
	if(slave < 0 || slave > 4)
		return false; // invalid slave number
	
	// pull slave select low
	DDRF &= ~(1 << slave);
	
	// set outgoing data
	SPDR = START_BYTE;
	waitForTransmit();
	SPDR = c.m_commandType;
	waitForTransmit();
	SPDR = c.m_arg1;
	waitForTransmit();
	SPDR = c.m_arg2;
	waitForTransmit();
	char checksum = c.m_commandType + c.m_arg1 + c.m_arg2;
	SPDR = checksum;
	waitForTransmit();
	
	// wait till slave has reply
	char r = 0;
	int count = 0;
	while (r != START_BYTE) {
		count++;
		if (count > WAIT_FOR_REPLY) {
			success = false;
			break;
		}
		
		SPDR = GET_REPLY;
		waitForTransmit();
		r = SPDR;
	}
	
	SPDR = GET_REPLY;
	waitForTransmit();
	char checksumEcho = SPDR;
	SPDR = GET_REPLY;
	waitForTransmit();
	char replyData = SPDR;
	SPDR = GET_REPLY;
	waitForTransmit();
	char replyChecksum = SPDR;
	
	// pull slave select high
	DDRF |= 0b00011111;
	
	if(replyChecksum == checksumEcho + replyData && checksumEcho == checksum) {
		*reply = replyData;
	}
	else {
		success = false;
	}
	
	return success;
}