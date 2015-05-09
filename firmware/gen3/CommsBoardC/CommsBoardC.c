/*
 * CommsBoardC.c
 *
 * Created: 4/4/2015 2:23:13 AM
 *  Author: Karl
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include "serial.h"
#include "spi.h"

#define FOSC 1843200
#define F_CPU FOSC
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

int main(void)
{
	cli();
	
	// Set the overall clock scaling
	CLKPR = (1 << CLKPCE);
	CLKPR = (0 << CLKPCE) | (1 << CLKPS0);
	
	// Set up a few variables
	int counter = 0;
	
	// Initialize serial, move this to serial lib
	unsigned int ubrr = MYUBRR;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0C = (0 << UMSEL0) | (0 << UPM00) | (0 << UPM01) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B = 0x00;
	UCSR0B |= (1 << UDRIE0);
	UCSR0B |= (1 << TXCIE0);
	UCSR0B |= (1 << UDRIE0) | (1 << TXCIE0);
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	DDRC = 0xFF;
	message recvMsg;
	memset(&recvMsg, 0, sizeof(message));
	unsigned char last = 0;
	PORTC = 0x00;
	
	sei();
	
    while(1)
    {
		// Figure out how many message we might want to fetch
		// This way, even if new message come as we're looping
		// The loop will still end
		int inboxSize = serialGetInboxSize();
		for(int i = 0; i < inboxSize; i++){
			// Empty out the inbox.
			if(!serialPopInbox(&recvMsg)){
				// Failed to get a message for some reason
				// Break out.
				break;
			}
			PORTC ^= 0b00000100;
			// Process the message
			if(recvMsg.message[0])
			{
				// Turn on the LED
				PORTC |= 0x01;
			}
			else
			{
				// Turn off the LED
				PORTC &= ~(0x01);
			}
		}
			PORTC ^= 0b00001000;
			recvMsg.slaveID = 0xFF;
			recvMsg.message[0] =  0xFF;
			recvMsg.message[1] = 0xFF;
			recvMsg.message[2] = 0xFF;
			serialPushOutbox(&recvMsg);
    }
}