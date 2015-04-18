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
	/* Initialize serial, move this to serial lib */
	unsigned int ubrr = MYUBRR;
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	UCSR0C = (1 << USBS0) | (3<< UCSZ00);
	
	DDRA = 0xFF;
	message recvMsg;
	unsigned char last = 0;
    while(true)
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
			// Process the message
			if(recvMsg.message[0])
			{
				// Turn on the LED
				PORTA = 0xFF;
			}
			else
			{
				// Turn off the LED
				PORTA = 0x00;
			}
		}
		recvMsg.slaveID = 0;
		recvMsg.message[0] = last++;
    }
}