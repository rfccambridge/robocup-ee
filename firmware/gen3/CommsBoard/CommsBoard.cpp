#include <string.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include <util/delay.h>
#include "SPIMaster.h"
#include "EELib.h"
#include "CommsBoard.h"
#include "SerialLib.h"

int main(void)
{
	
	DDRC = 0xFF;
	message recvMsg;
	//SPIMaster spi = SPIMaster();
	//Command c = Command();
	char replyArr[5];
	char* reply = &(replyArr[0]);
	memset(&recvMsg, 0, sizeof(message));
	PORTC = 0x00;
	
	initSerial();
	
	//sei();
	while(true){
		int bytes = serialPopInbox(&recvMsg);
		if(bytes != 0){
			// Use the received message.
			char id = recvMsg.message[0];
			
			// todo filter on bot ID
			if (true) {
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