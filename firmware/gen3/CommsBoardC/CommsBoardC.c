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


int main(void)
{
	message recvMsg;
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
			// Have a message ready. Forward it over SPI.
		}
		// Get client data from SPI and queue it up for serial.
    }
}