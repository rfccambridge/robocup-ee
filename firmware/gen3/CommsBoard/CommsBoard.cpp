#include <avr/io.h>
#include <string.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include <util/delay.h>
#include "SPIMaster.h"

extern "C"{
	#include "serial.h"
};

#define F_CPU 16000000
#define BAUD 19200

int main(void)
{
	cli();
	
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
	
	DDRC = 0xFF;
	message recvMsg;
	//SPIMaster spi = SPIMaster();
	//Command c = Command();
	char replyArr[5];
	char* reply = &(replyArr[0]);
	memset(&recvMsg, 0, sizeof(message));
	PORTC = 0x00;
	
	sei();
	while(true){
		int bytes = serialPopInbox(&recvMsg);
		if(bytes != 0){
			// Use the received message.
			char id = recvMsg.message[0];
			
			// todo filter on bot ID
			if (id == get_robot_id()) {
				char source = recvMsg.message[1];
				char port = recvMsg.message[2];
				// get other data
				for (int i = 0; i < SERIAL_MSG_MAX_CHARS; i++) {
					PORTC = recvMsg.message[i];
					_delay_ms(2000);
				}
			}

		}
		else {
			PORTC = 0x00;
		}
	}
}