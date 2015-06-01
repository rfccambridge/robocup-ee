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
	if((PINB0 & 1) == 1) { // slave select not selected
		m_state = 0; // reset state to waiting
	}
	
	if(SPSR & (1<<SPIF)) { // new data
		char data = SPDR;
		
		// state: 0 waiting; 1-5 number of bytes received (start, command, arg1, arg2, checksum); 6 given data to GetCommand; 7 reply ready; 8-11 sending reply bytes (start, checksumEcho, reply, checksum)
		switch(m_state) {
		case 0:
			if(data == START_BYTE)
				m_state = 1;
 			break;
		case 1:
			m_command = data;
			m_state = 2;
			break;
		case 2:
			m_arg1 = data;
			m_state = 3;
			break;
		case 3:
			m_arg2 = data;
			m_state = 4;
			break;
		case 4:
			if(data == m_command + m_arg1 + m_arg2) {
				m_checksum = data;
				m_state = 5;
			}
			else {
				m_state = 0; // bad checksum; just ignore it
			}
			break;
		case 5:
		case 6:
			// nothing to do here
			break;
		case 7:
			SPDR = m_checksum;
			m_state = 8;
			break;
		case 8:
			SPDR = m_reply;
			m_state = 9;
			break;
		case 9:
			SPDR = (m_checksum + m_reply);
			m_state = 10;
			break;
		case 10:
			m_state = 0;
			break;
		default:
			m_state = 0;
			break;
		}
	}
}

bool SPISlave::GetCommand(Command* command) {
	if(m_state == 5) {
		command->m_commandType = m_command;
		command->m_arg1 = m_arg1;
		command->m_arg2 = m_arg2;
		m_state = 6;
		return true;
	}
	else {
		return false;
	}
}

char SPISlave::getChar() {
	waitForTransmit();
	return SPDR;
}

void SPISlave::SetReply(char reply) {
	if(m_state == 6) {
		m_reply = reply;
		m_state = 7;
		SPDR = START_BYTE;
	}
}
