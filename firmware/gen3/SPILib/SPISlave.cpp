#include "SPISlave.h"
#include <avr/io.h>
#include "Constants.h"

SPISlave::SPISlave() {
	// set MISO to output
	DDRB |= (1<<3);
	
	// enable SPI
	SPCR = (1<<SPE);
}

void waitForTransmit() {
	while(!(SPSR & (1<<SPIF))) ;
}

void SPISlave::ReceiveSPI() {
	if((PINB & 0x01) == 1) { // slave select not selected
		m_state = 0; // reset state to waiting
		return;
	}
	
	if(SPSR & (1<<SPIF)) { // SPI data is ready
		char data = SPDR;
		
		/* state: 0 waiting; 
			1-5 number of bytes received (start, command, arg1, arg2, checksum);
			6 given data to GetCommand; 
			7 reply ready; 
			8-11 sending reply bytes (start, checksumEcho, reply, checksum)
		*/
		switch(m_state) {
		case 0: // waiting for start byte
			if(data == START_BYTE)
				m_state = 1;
			SPDR = 0x00;
 			break;
		case 1: // getting command type
			m_command = data;
			m_state = 2;
			SPDR = 0x00;
			break;
		case 2: // getting arg 1
			m_arg1 = data;
			m_state = 3;
			SPDR = 0x00;
			break;
		case 3: // getting arg 2
			m_arg2 = data;
			m_state = 4;
			SPDR = 0x00;
			break;
		case 4: // getting arg 3
			m_arg3 = data;
			m_state = 5;
			SPDR = 0x00;
			break;
		case 5: // getting arg 4
			m_arg4 = data;
			m_state = 6;
			SPDR = 0x00;
			break;
		case 6: // getting checksum
			if(data == m_command + m_arg1 + m_arg2 + m_arg3 + m_arg4) {
				m_checksum = data;
				m_state = 7;
				PORTC |= (1 << 2); // turn on LED 2
			}
			else {
				
				PORTC &= ~(1 << 2); // turn off LED 2
				m_state = 0; // bad checksum; just ignore it
		}
		SPDR = 0x00;
			break;
		case 7: // waiting for data to be used
			/* nothing to do here. have saved the message internally
			and am waiting for GetCommand to be called to pull the data out.
			*/
			SPDR = 0x00;
			break;
		case 8: // waiting to send reply
			/* nothing to do here. message has been read, we need to send 
			a reply */
			SPDR = 0x00;
			break;
		case 9: // reply data has been set, tell master to listen
			SPDR = START_BYTE;
			m_state = 10;
			break;
		case 10: // echo the checksum
			SPDR = 0xff;//m_checksum;
			m_state = 11;
			break;
		case 11: // send our reply
			SPDR = m_reply;
			m_state = 12;
			break;
		case 12: // send reply checksum
			SPDR = (m_checksum + m_reply);
			m_state = 0;
			break;
		default: // error, go to state 0
			m_state = 0;
			SPDR = 0x00;
			break;
		}
	}
}

bool SPISlave::GetCommand(Command* command) {
	if(m_state == 7) {
		command->m_commandType = m_command;
		command->m_arg1 = m_arg1;
		command->m_arg2 = m_arg2;
		command->m_arg3 = m_arg3;
		command->m_arg4 = m_arg4;
		m_state = 8;
		return true;
	}
	else {
		return false;
	}
}

void SPISlave::SetReply(char reply) {
	if(m_state == 8) {
		m_reply = reply;
		m_state = 9;
	}
}

// mostly for debugging
char SPISlave::getChar() {
	waitForTransmit();
	return SPDR;
}

