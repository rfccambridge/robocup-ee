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
#include "Command.h"

int main(void)
{
	// initialize display
	DDRC = 0xFF;
	PORTC = 0x00;
	
	//initializing serial comms
	initSerial();
	message recvMsg;
	
	while(true){
		int bytes = serialPopInbox(&recvMsg);
		if(bytes != 0){
			// Use the received message.
			char id = recvMsg.message[0];
			
			// todo filter on bot ID
			if (id == getBotID()) {
				char source = recvMsg.message[1];
				char port = recvMsg.message[2];
				
				// switch on message type
				switch(port) {
					case LEDCommand::key:
						// stuff
						break;
					default:
						// stuff
						break;
				}
				// get other data
				for (int i = 0; i < SERIAL_MSG_MAX_CHARS; i++) {
					PORTC = recvMsg.message[i];
					_delay_ms(2000);
				}
			}
		}
	}
}