#include "4enet.h"
#include <p18f4431.h>

unsigned char txPtr;

PacketBuffer TxPacket;

void transmit()
{
	unsigned char intStat;

	// switch to supervisor mode
	intStat = INTCON;
	INTCONbits.GIEH = 0;
	INTCONbits.GIEL = 0;

	// start transmission
	TxPacket.done = 0;
	txPtr = MAX_PACKET_SIZE+1;
	PIE1bits.TXIE = 1;
	TXREG = 0x0a;	//CR

	// switch back to user mode
	INTCON = intStat;
}

void handleTx()
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
			TXREG = TxPacket.destination;
			txPtr++;
			break;
		case MAX_PACKET_SIZE+5:
			TXREG = ' ';
			txPtr++;
			break;
		case MAX_PACKET_SIZE+6:
			TXREG = TxPacket.port;
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
			TxPacket.done = 1;
			PIE1bits.TXIE = 0;
			RCSTAbits.CREN = 1;
			break;
		default:
			if (txPtr < TxPacket.length) {
				TXREG = TxPacket.data[txPtr];
				txPtr++;
			} else {
				txPtr = MAX_PACKET_SIZE+10;
				TXREG = ESCAPE_CODE;
			}
			break;
	}
}
