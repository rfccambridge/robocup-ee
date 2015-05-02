/*
 * CommsBoardC.c
 *
 * Created: 4/4/2015 2:23:13 AM
 *  Author: Karl
 */ 

#include <avr/io.h>
#include <string.h>
#include <stdbool.h>
#include "serial.h"
#include "spi.h"

#define FOSC 1843200
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
	int counter = 0;
	// Initialize serial, move this to serial lib
	unsigned int ubrr = MYUBRR;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3<< UCSZ00);
	UCSR0B |= (1 << UDRIE0);
	UCSR0B |= (1 << TXCIE0);
	UCSR0B |= (1 << UDRIE0) | (1 << TXCIE0);
	
	DDRC = 0xFF;
	message recvMsg;
	unsigned char last = 0;
	PORTC = 0x00;
    while(1)
    {
		if(!(counter++ % 1000)){
			PORTC ^= 0x01;
		}
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
		recvMsg.slaveID = 0;
		recvMsg.message[0] = last++;
		serialPushOutbox(&recvMsg);
    }
}