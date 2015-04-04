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
		if(popInbox(&recvMsg)){
			// Got a new message. Forward it over SPI.
		}
		// Get client data from SPI and queue it up for serial.
    }
}