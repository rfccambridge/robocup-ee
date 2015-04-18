#include "serial.h"
#include <stdbool.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#define XBEE_RTS PORTD
#define XBEE_RTS_BIT 1
#define XBEE_CTS PORTD
#define XBEE_CTS_BIT 2
#define SEND_QUEUE_SIZE SERIAL_MSG_CHARS

messageQueue inbox;
messageQueue outbox;

unsigned int charsRead = 0;
message readBuf;

unsigned int charsSent = SEND_QUEUE_SIZE;
char sendQueue[SEND_QUEUE_SIZE];

bool serialPushInbox(const message* msg){
	return mqPushMessage(msg, &inbox);
}

bool serialPopInbox(message* dest){
	return mqPopMessage(dest, &inbox);
}

int serialGetInboxSize(){
	return mqGetSize(&inbox);
}

bool serialPushOutbox(const message* msg){
	return mqPushMessage(msg, &outbox);
	// Since we have a message in the outbox,
	// Enable the interrupt handler that sends data
	// Worst case, the data is already sent and the interrupt
	// Will just disable itself.
	UCSR0B |= (1 << UDRIE0);
}

bool serialPopOutbox(message* msg){
	return mqPopMessage(msg, &outbox);
}

int serialGetOutboxSize(){
	return mqGetSize(&outbox);
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
		serialPushInbox(&readBuf);
		charsRead = 0;
	}
};

ISR(USART0_TX_vect){
	// Do nothing, this just clears the tx complete flag for us
};

ISR(USART0_UDRE_vect){
	if(charsSent >= SEND_QUEUE_SIZE){
		// We have nothing to send, check the outbox.
		message msg;
		if(serialPopOutbox(&msg)){
			// There *is* a message waiting to send
			// We'll queue it up for sending
			memcpy(&sendQueue, &(msg.message), sizeof(char) * SERIAL_MSG_CHARS);
			charsSent = 0;
		}
		else{
			// No message waiting, we have nothing to do.
			// Disable the send empty interrupt to avoid looping.
			UCSR0B &= ~(1 << UDRIE0);
			return;
		}
	}
	UDR0 = sendQueue[charsSent++];
};