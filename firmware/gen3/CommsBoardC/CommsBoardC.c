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

//#define FOSC 1843200
#define F_CPU 16000000
#define BAUD 19200
//#define MYUBRR F_CPU/16/BAUD-1

int main(void)
{
	cli();
	
	// Set the overall clock scaling
	CLKPR = (1 << CLKPCE);
	CLKPR = (0 << CLKPCE) | (0 << CLKPS0);
	
	// Set up a few variables
	int counter = 0;
	
	// Initialize serial, move this to serial lib
	//unsigned int ubrr = MYUBRR;
	#include <util/setbaud.h>
	UBRR0H = UBRRH_VALUE;//(unsigned char)(ubrr>>8);
	UBRR0L = UBRRL_VALUE; //(unsigned char)ubrr;
	UCSR0C = (0 << UMSEL0) | (0 << UPM00) | (0 << UPM01) | (1 << USBS0) | (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B = (1 << TXCIE0) | (1 << RXCIE0) | (1 << UDRIE0) | (1 << RXEN0) | (1 << TXEN0);
	
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
		//int inboxSize = serialGetInboxSize();
		if(serialPopInbox(&recvMsg)){
			PORTC = 0xFF;
		}
		/*for(int i = 0; i < inboxSize; i++){
			PORTC ^= 0xFF;
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
				PORTC = 0xFF;
			}
			else
			{
				// Turn off the LED
				PORTC = 0x00;
			}
		}*/
		if(!(counter++ % 10000)){
			recvMsg.slaveID = 'd';
			recvMsg.message[0] = 'a';
			recvMsg.message[1] = 'b';
			recvMsg.message[2] = 'c';
			serialPushOutbox(&recvMsg);
		}
    }
}