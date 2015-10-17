#include "SerialLib.h"
#include <stdbool.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <avr/io.h>

#define XBEE_RTS PORTD
#define XBEE_RTS_BIT 1
#define XBEE_CTS PORTD
#define XBEE_CTS_BIT 2
#define SEND_QUEUE_SIZE SERIAL_MSG_MAX_CHARS

#define F_CPU 16000000
#define BAUD 19200

//messageQueue inbox;
messageQueue outbox;

unsigned int icount = 0;

unsigned int charsSent = SEND_QUEUE_SIZE;
char sendQueue[SEND_QUEUE_SIZE];
unsigned int charsRead = 0;
message readBuf;

/*bool serialPushInbox(const message* msg){
	return mqPushMessage(msg, &inbox);
}*/

void initSerial() {
	// Set the overall clock scaling
	CLKPR = (1 << CLKPCE);
	CLKPR = (0 << CLKPCE) | (0 << CLKPS0);
	
	// Initialize serial, move this to serial lib
	//unsigned int ubrr = MYUBRR;
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;//(unsigned char)(ubrr>>8);
	UBRR0L = UBRRL_VALUE; //(unsigned char)ubrr;
	UCSR0C = (0 << UMSEL0) | (0 << UPM00) | (0 << UPM01) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B = (1 << TXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0);
}

// pulls a message off the serial lines. returns # of bytes
int serialPopInbox(message* dest){
	int state = 0;
	int data_byte = 0;
	bool done = false;
	while(!done) {
		while (!(UCSR0A & (1 << RXC0))) {
			// Busy wait for message.
		}
		char datum = UDR0;
		switch(state) {
		case 0:
			if (datum == '\\')
				state = 1;
			else
				return 0;
			break;
		case 1:
			if (datum == 'H')
				state = 2;
			else
				return 0;
			break;
		case 2:
			// getting data
			if (datum == '\\') {
				// escape sequence
				state = 3;
			} 
			else {
				// more data
				readBuf.message[data_byte++] = datum;
			}
			break;
		case 3:
			if (datum == 'E') {
				// end of message
				state = 4;
				done = true;
			}
			else if (datum == '\\')
			{
				// escaped backslash
				state = 2;
				readBuf.message[data_byte++] = datum;
			}
			else
				return 0;
			break;
		default:
			return 0;
		}
	}
	// if a full ID, SOURCE, PORT was not sent
	if (data_byte < 3)
		return 0;
	
	// all good
	memcpy(dest, &readBuf, sizeof(message));
	charsRead = 0;
	return data_byte;
	//return mqPopMessage(dest, &inbox);
}

/*int serialGetInboxSize(){
	return mqGetSize(&inbox);
}*/

bool serialPushOutbox(const message* msg){
	
	// Since we have a message in the outbox,
	// Enable the interrupt handler that sends data
	// Worst case, the data is already sent and the interrupt
	// Will just disable itself.
	// Busy wait for messages
	for(int i = 0; i < SERIAL_MSG_MAX_CHARS; i++){
		while( !((UCSR0A) & (1 << UDRE0))){
			// Wait
		}
		UDR0 = msg->message[i];
	}
	return true;
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

// Below are unused ISRs
// They were supposed to handle serial.
// Kept commented because they will live again!
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
/*ISR(USART0_RX_vect){
	PORTC = 0xFF; // Debug, turn all LEDs on
	char data = UDR0;
	if (charsRead > 0){
		// Data is part of the message body
		readBuf.message[(charsRead - 1) % SERIAL_MSG_CHARS] = data;
	}
	else{
		// Data is the slave ID
		readBuf.slaveID = data;
	}
	if(++charsRead > (1 + SERIAL_MSG_CHARS)){
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
			memcpy(&sendQueue, &(msg.message), SEND_QUEUE_SIZE);
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
};*/