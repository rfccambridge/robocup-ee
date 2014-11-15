#include "bemixnet.h"
#include <p18f4431.h>

static signed char txPtr;

#define ROBOT_NUMBER	'0'

unsigned char getAddress()
{
	return '0'+ 8*PORTDbits.RD3 + 4*PORTDbits.RD2 + 2*PORTDbits.RD1 + PORTDbits.RD0;
}


// global variable into which the each received packet is placed.
// The contents are only valid when RxPacket.done = 1.

void initRx(PacketBuffer * RxPacket)
{
	INTCON = 0b11000000;					//GIE and PEIE set.	
	PIE1bits.RCIE = 1;						//Serial Receive Interrupt enabled.
	RxPacket->done=0;						//initializing Packet flag
	RCSTAbits.SPEN = 1;						//Serial Port Enabled

	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	TXSTAbits.BRGH = 1;						//high baud rate mode
	SPBRG = 12;								//This would make approx 38461 baud rate @ 8 Mhz
	RCSTAbits.CREN = 1;						//Receiving enabled (asynchronous mode)
}

void initTx(PacketBuffer * TxPacket)
{
	INTCON = 0b11000000;					//GIE and PEIE set.	
	
	PIE1bits.TXIE = 1;						//Serial Receive Interrupt enabled.
	TxPacket->done=1;						//initializing Packet flag
	
	RCSTAbits.SPEN = 1;						//Serial Port Enabled

	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;

	TXSTAbits.BRGH = 1;						//high baud rate mode
	SPBRG = 12;								//This would make approx 38461 baud rate @ 8 Mhz
	RCSTAbits.CREN = 1;						//Receiving enabled (asynchronous mode)
	TXSTAbits.TXEN = 1;
}


// handleRx() grabs the byte from the USART, parses it, and, if appropriate,  
// adds it to RxPacket. 
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
		// expecting escape to start packet
		case IGNORE:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			break;
		// expecting the header code
		case ESCAPE:
			if (newByte == HEADER_CODE)
				receiveState = HEADER;
			else	// must have been a framing error, ignore rest of packet
				receiveState = IGNORE;
			break;
		// expecting destination address, if it matches continue to next state
		// otherwise go back to IGNORE
		case HEADER:
			if (newByte == getAddress())
				receiveState = SOURCE;
			else if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			else
				receiveState = IGNORE;
			break;
		// at this point, packet is addressed to MY_ADDRESS, go ahead recieving
		// reset length counter and clear done flag to let program know that
		// RxPacket is currently invalid
		case SOURCE:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
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
				// if Rx buffer is full then stop recieving
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


// begins transmitting TxPacket
void transmit(PacketBuffer * TxPacket)
{
	unsigned char intStat;

	// switch to supervisor mode
	intStat = INTCON;
	INTCONbits.GIEH = 0;
	INTCONbits.GIEL = 0;

	// start transmission
	TxPacket->done = 0;
	txPtr = MAX_PACKET_SIZE+1;
	PIE1bits.TXIE = 1;
	TXREG = 0x0a;	//CR

	// switch back to user mode
	INTCON = intStat;
}

void handleTx(PacketBuffer * TxPacket)
{
	switch (txPtr) {
		case MAX_PACKET_SIZE+1:
			TXREG = 0x0d;	//LF
			txPtr++;
			break;
		case MAX_PACKET_SIZE+2:
			TXREG = ESCAPE_CODE;
			txPtr++;
			break;
		case MAX_PACKET_SIZE+3:
			TXREG = HEADER_CODE;
			txPtr++;
			break;
		case MAX_PACKET_SIZE+4:
			TXREG = TxPacket->destination;
			txPtr++;
			break;
		case MAX_PACKET_SIZE+5:
			TXREG = ' ';
			txPtr++;
			break;
		case MAX_PACKET_SIZE+6:
			TXREG = TxPacket->port;
			txPtr=0;
			break;
		case MAX_PACKET_SIZE+10:
			TXREG = END_CODE;
			txPtr++;
			break;
		case MAX_PACKET_SIZE+11:
			// padding
			TXREG = ' ';
			txPtr++;
			break;
		case MAX_PACKET_SIZE+12:
			TxPacket->done = 1;
			PIE1bits.TXIE = 0;
			RCSTAbits.CREN = 1;
			break;
		default:
			if (txPtr < TxPacket->length) {
				TXREG = TxPacket->data[txPtr];
				txPtr++;
			} else {
				txPtr = MAX_PACKET_SIZE+10;
				TXREG = ESCAPE_CODE;
			}
			break;
	}
}
