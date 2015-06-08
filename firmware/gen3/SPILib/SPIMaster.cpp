#include "SPIMaster.h"
#include <avr/io.h>
#include "Constants.h"

const char WAIT_FOR_REPLY = 3; // the number of times to try to get a reply from slave (since getting a reply requires sending something)

SPIMaster::SPIMaster() {
	// low 5 bits of port f are slave selects; set them to outputs
	DDRF = 0b00011111;
	PORTF = 0b00011111; // deselect all slaves to start
	
	// set MOSI, SCK, and SS as outputs
	DDRB |= 0b00000111;
	
	// enable SPI, master mode, clock f_ck/64
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR1);
}

// call this after sending each piece of data
void waitForTransmit() {
	while(!(SPSR & (1<<SPIF))) ;
}

// mostly for debug purposes. sends a char to all slaves
void SPIMaster::sendChar(char c) {
	PORTF = 0x00; // select all slaves
	SPDR = c; // set data register
	waitForTransmit();
	PORTF = 0b00011111; // deselect all slaves
	
}

/* SendCommand -Primary function to be used to communicate to other boards.
Sends a Command to the specified Slave, and loads it's 1 char reply into the
variable specified by *reply

Uses checksums to determine whether any information was corrupted, and
returns true if the message went through successfully
*/
bool SPIMaster::SendCommand(char slave, Command c, char* reply) {
	if(slave < 0 || slave > 4)
		return false; // invalid slave number
	
	// pull slave select low
	PORTF = ~(1 << slave);
	
	// set outgoing data
	SPDR = START_BYTE;
	waitForTransmit();
	SPDR = c.GetType();
	waitForTransmit();
	SPDR = c.m_arg1;
	waitForTransmit();
	SPDR = c.m_arg2;
	waitForTransmit();
	char checksum = c.GetType() + c.m_arg1 + c.m_arg2;
	SPDR = checksum;
	waitForTransmit();
	
	// wait till slave has reply
	char r = SPDR;
	int count = 0;
	while (r != START_BYTE) {
		count++;
		if (count > WAIT_FOR_REPLY) {
			// pull slave select high
			PORTF |= 0b00011111;
			return false;
		}
		
		SPDR = GET_REPLY;
		waitForTransmit();
		r = SPDR;
	}
	// just got a START_BYTE
	SPDR = GET_REPLY;
	waitForTransmit();
	char checksumEcho = SPDR; // this is coming through only sometimes
	SPDR = GET_REPLY;
	waitForTransmit();
	char replyData = SPDR;
	SPDR = GET_REPLY;
	waitForTransmit();
	char replyChecksum = SPDR;
	
	// pull slave select high
	PORTF |= 0b00011111;
	
	if(replyChecksum == checksumEcho + replyData && checksumEcho == checksum) {
		*reply = replyData;
		return true;
	}
	return false;
}