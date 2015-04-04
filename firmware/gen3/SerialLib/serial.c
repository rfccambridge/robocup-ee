#include "serial.h"
#include <stdbool.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#define BOX_SIZE 10
#define XBEE_RTS PORTD
#define XBEE_RTS_BIT 1
#define XBEE_CTS PORTD
#define XBEE_CTS_BIT 2

unsigned int inboxSize = 0;
message inbox[BOX_SIZE];

unsigned int outboxSize = 0;
message outbox[BOX_SIZE];

unsigned int charsRead = 0;
message readBuf;

bool pushMessage(const message* msg, message* box, unsigned int* size){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(*size >= BOX_SIZE){
			return false;
		}
		memcpy(&box[*size], msg, sizeof(message));
		(*size)++;
	}
	return true;
}

bool popMessage(message* dest, message* box, unsigned int* size){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(*size <= 0){
			return false;
		}
		memcpy(dest, &box[*size - 1], sizeof(message));
		(*size)--;
	}
	return true;
}

bool pushInbox(const message* msg){
	return pushMessage(msg, &inbox[0], &inboxSize);
}

bool popInbox(message* dest){
	return popMessage(dest, &inbox[0], &inboxSize);
}

int getInboxSize(){
	return inboxSize;
}

bool pushOutbox(const message* msg){
	return pushMessage(msg, &outbox[0], &outboxSize);
}

bool popOutbox(message* msg){
	return popMessage(msg, &outbox[0], &outboxSize);
}

int getOutboxSize(){
	return outboxSize;
}

void setReceiveBlock(bool block){
	if(block){
		// Deassert RTS to stop xbee sending data
		XBEE_RTS &= ~(1 << XBEE_RTS_BIT);
	}
	else{
		// Assert RTS to allow xbee sending data
		XBEE_RTS |= (1 << XBEE_RTS_BIT);
	}
}

bool clearToSend(){
	// Xbee asserts CTS when it is ready to receive
	return XBEE_CTS & (1 << XBEE_CTS_BIT);
}

/*
 * There are several different interrupts that we have to manage
 * to control data transmission using interrupts.
 *
 * Data Register Empty - Fired when more data can be written to
 *     The output data buffer. In the handler you MUST either
 *     write more data OR disable the interrupt. Otherwise, it
 *     will be fired again.
 * TX Complete - Fired once the frame in the USART shift register
 *     has been shifted out. Using this handler, we do not have
 *     to clear the TXC0 flag ourselves.
 * RX Complete - Fired when data is ready to be read from the
 *     receive register. The data MUST be read to clear the flag.
 */

ISR(USART0_RX_vect){
	char data = UDR0;
	if (charsRead > 0){
		// Data is part of the message body
		readBuf.message[charsRead % SERIAL_MSG_CHARS] = data;
	}
	else{
		// Data is the slave ID
		readBuf.slaveID = data;
	}
	if(++charsRead > 1 + SERIAL_MSG_CHARS){
		// Have read a full message
		pushInbox(&readBuf);
		charsRead = 0;
	}
};