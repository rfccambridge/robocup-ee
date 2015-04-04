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

typedef struct serial_queue {
	unsigned int size;
	unsigned int first;
	message box[BOX_SIZE];
}serial_queue;

serial_queue inbox;
serial_queue outbox;

unsigned int charsRead = 0;
message readBuf;

bool pushMessage(const message* msg, serial_queue* box){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(box->size >= BOX_SIZE){
			return false;
		}
		unsigned int idx = (box->first + box->size) % BOX_SIZE;
		memcpy(&(box->box[idx]), msg, sizeof(message));
		(box->size)++;
	}
	return true;
}

bool popMessage(message* dest, serial_queue* box){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(box->size <= 0){
			return false;
		}
		memcpy(dest, &box[box->first], sizeof(message));
		box->first = (box->first + 1) % BOX_SIZE;
		(box->size)--;
	}
	return true;
}

bool pushInbox(const message* msg){
	return pushMessage(msg, &inbox);
}

bool popInbox(message* dest){
	return popMessage(dest, &inbox);
}

int getInboxSize(){
	return inbox.size;
}

bool pushOutbox(const message* msg){
	return pushMessage(msg, &outbox);
}

bool popOutbox(message* msg){
	return popMessage(msg, &outbox);
}

int getOutboxSize(){
	return outbox.size;
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