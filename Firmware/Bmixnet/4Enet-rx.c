#include "4Enet.h"
#include "..\logiccode\pins.h"
#include <p18f4431.h>

static signed char txPtr;


unsigned char getAddress()
{
	return '0' + (PORTDbits.RD4 ? 0 : 1) + (PORTDbits.RD1 ? 0 : 2) + (PORTDbits.RD0 ? 0 : 4);
}


// global variable into which the each received packet is placed.
// The contents are only valid when RxPacket.done = 1.
//PacketBuffer RxPacket;

void initRx(PacketBuffer * RxPacket)//Needs to be worked on --Minjae
{
	INTCON = 0b11000000;					//GIE and PEIE set.	
	PIE1bits.RCIE = 1;						//Serial Receive Interrupt enabled.
	RxPacket->done=0;						//initializing Packet flag
	RCSTAbits.SPEN = 1;						//Serial Port Enabled
	TRISC = 0b11000000;						//Pins initialized as inputs.
	PORTC = 0b00000000;
	SPBRG = 12;								//This would make approx 9600 baud rate @ 8MHz
	RCSTAbits.CREN = 1;						//Receiving enabled (asynchronous mode)
	TXSTAbits.TXEN = 1;

}

// handleRx() grabs the byte from the USART, parses it, and, if appropriate,  
// adds it to RxPacket. 

/* We need to figure out what passes the PacketBuffer to this function. I 
   suspect there is some main routine in a file somewhere. -- John Bestoso */
void handleRx(PacketBuffer * RxPacket) {
	static enum ReceiveState receiveState;
	unsigned char newByte;

	// error checking
	if (RCSTAbits.FERR) {			// framing error
		newByte = RCREG;
		receiveState = IGNORE;
		return;
	} else if (RCSTAbits.OERR) {	// overrun error
		RCSTAbits.CREN = 0;
		receiveState = IGNORE;
		RCSTAbits.CREN = 1;
		return;
	}

	// read data from USART
	newByte = RCREG;

	switch (receiveState) {
		// If we're ignoring, and we see an escape sequence, that could be the start
		// of a packet
		case IGNORE:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			break;
		// Having seen an escape sequence, we now expect a header. If not, go back
		// to ignoring
		case ESCAPE:
			if (newByte == HEADER_CODE)
				receiveState = HEADER;
			else	// must have been a framing error, ignore rest of packet
				receiveState = IGNORE;
			break;
		// Next should be the robot ID (address). If it matches ours, we go on to get data.
		// Otherwise, go back to ignoring or looking for a header if we see an escape
		case HEADER:
			if (newByte == getAddress())
				receiveState = SOURCE;
			else if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			else
				receiveState = IGNORE;
			break;
		// At this point, packet is addressed to MY_ADDRESS, go ahead recieving
		// Reset length counter and clear done flag to let program know that
		// RxPacket is currently invalid
		case SOURCE:
			// An escape? Go back to expecting a header
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			// Otherwise, store the address
			else {
				receiveState = PORT;
				RxPacket->address = newByte;
				RxPacket->done = 0;
				RxPacket->length = 0;
			}
			break;
		case PORT:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			else {
				receiveState = DATA;
				RxPacket->port = newByte;
			}
			break;
		case DATA:
			if (RxPacket->length < MAX_PACKET_SIZE) {
				RxPacket->data[RxPacket->length] = newByte;
				RxPacket->length++;
			} else {
				// If Rx buffer is full then stop recieving (avoid buffer 
				// overflow)
				RxPacket->length--;
				receiveState = IGNORE;
				RxPacket->done = 1;
			}
			if (newByte == ESCAPE_CODE)
				receiveState = DATAESC;
			break;
		// special state to handle escape codes in the data.
		case DATAESC:
			if (newByte == ESCAPE_CODE)
				receiveState = DATA;
			else if (newByte == END_CODE) {
				RxPacket->done = 1;
				RxPacket->length--;
				receiveState = IGNORE;
			} else			
				receiveState = IGNORE;
			break;
		// in case there was an error somewhere and revieceState became invalid
		default:
			receiveState = IGNORE;
			break;
	}

}
