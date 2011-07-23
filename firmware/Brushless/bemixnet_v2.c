#include "bemixnet_v2.h"
#include "pins_v2.h"
#include <p33FJ32MC304.h>

static signed char txByte;
unsigned char pktsReceived, pktsAccepted, pktsMismatched; //extern

static void resetPktStats(void)
{
	pktsReceived = pktsAccepted = pktsMismatched = 0;
}

unsigned char getAddress(void)
{
	return '0'+ 8*BOTID3_I + 4*BOTID2_I + 2*BOTID1_I + BOTID0_I;
}

void initRx(PacketBuffer * RxPacket)
{
	resetPktStats();
	RxPacket->done=0;
}

void initTx(PacketBuffer * TxPacket)
{
	TxPacket->done=1;
}

// handleRx() grabs the byte from the USART, parses it, and, if appropriate,  
// adds it to RxPacket. 
void handleRx(PacketBuffer * RxPacket) {
	static enum ReceiveState receiveState;
	unsigned char newByte;

	// error checking
	if (U1STAbits.FERR) {			// framing error
		newByte = U1RXREG;
		receiveState = IGNORE;
		return;
	} else if (U1STAbits.OERR) {	// overrun error
		U1MODEbits.UARTEN = 0;
		receiveState = IGNORE;
		U1MODEbits.UARTEN = 1;
		return;
	}

	// read data from USART
	newByte = U1RXREG;

	switch (receiveState) 
	{
		// expecting escape to start packet
		case IGNORE:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			break;
		// expecting the header code
		case ESCAPE:
			if (newByte == HEADER_CODE) {
				receiveState = CHKSUM;
				pktsReceived++;
				if (pktsReceived == 0) resetPktStats();
			} else{ // must have been a framing error, ignore rest of packet
				receiveState = IGNORE;
			}
			break;
		// expecting checksum word
		case CHKSUM:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			else {
				RxPacket->chksum = ~newByte; // NOT is to detect corruption to all 0s (data and checksum)
				receiveState = HEADER;
			}
			break;
		// expecting destination address, if it matches continue to next state
		// otherwise go back to IGNORE
		case HEADER:
			if (newByte == getAddress()) {
				RxPacket->chksum ^= newByte;
				receiveState = SOURCE;
			} else if (newByte == ESCAPE_CODE)
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
				RxPacket->chksum ^= newByte;
				RxPacket->address = newByte;
				RxPacket->done = 0;
				RxPacket->length = 0;
				receiveState = PORT;
			}
			break;
		case PORT:
			if (newByte == ESCAPE_CODE)
				receiveState = ESCAPE;
			else {
				RxPacket->chksum ^= newByte;
				RxPacket->port = newByte;
				receiveState = DATA;
			}
			break;
		case DATA:
			if (RxPacket->length < MAX_PACKET_SIZE) {
				RxPacket->data[RxPacket->length] = newByte;
				RxPacket->length++;
				if (newByte == ESCAPE_CODE) {
					receiveState = DATAESC;
				} else { // we don't count the escape: it's either first of duplicated esc (count one)
						 // or part of the end sequence (don't count it)
					RxPacket->chksum ^= newByte;
				}
			} else {
				// if Rx buffer is full then stop recieving -- NO!
				// we never seen the end of the packet! We might have collected garbage, throw it away.				
				receiveState = IGNORE;
			}
			break;
		// special state to handle escape codes in the data.
		case DATAESC:
			if (newByte == ESCAPE_CODE) { // escaped escape code
				RxPacket->chksum ^= newByte; // take into account only one escapes (escapes in data are repeated)
				receiveState = DATA;				
			} else if (newByte == END_CODE) {
				if (!RxPacket->chksum) {
					RxPacket->done = 1;
					pktsAccepted++;
					RxPacket->length--;
					if (pktsAccepted == 0) resetPktStats(); // when one counter overflows, reset all	
				} else {
					pktsMismatched++;					
					if (pktsMismatched == 0) resetPktStats(); // when one counter overflows, reset all
				}
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
void transmit(PacketBuffer * txPkt)
{
	unsigned int intState;
	unsigned char i;

	// compute checksum
	txPkt->chksum = 0;
	for (i = 0; i < txPkt->length; i++)
		txPkt->chksum ^= txPkt->data[i];
	txPkt->chksum = ~txPkt->chksum; // NOTed to allow detection of corruption to all 0s

	// switch to supervisor mode
	intState = SR;
	SRbits.IPL = 0b111;

	// start transmission
	txPkt->done = 0;
	IEC0bits.U1TXIE = 1;

	U1TXREG = ESCAPE_CODE;  // first byte of packet, has to be sent from here, as bootstrap
	txByte = 1;

	// switch back to user mode
	SR = intState;
}

// transmitts tx packet byte by byte, called by an interrupt when a byte transfer finishes
void handleTx(PacketBuffer * TxPacket)
{
	const int OVERHEAD = 3; // ESCAPE_CODE, HEADER_CODE, CHKSUM
	switch (txByte) 
	{
		case 1: U1TXREG = HEADER_CODE; break;      // second byte of pkt, first had to be sent in transmit()
		case 2: U1TXREG = TxPacket->chksum; break;
		default:
			if (txByte < TxPacket->length + OVERHEAD) {
				U1TXREG = TxPacket->data[txByte - OVERHEAD];
			} else {
				switch (txByte - (TxPacket->length + OVERHEAD)) {
				case 0: U1TXREG = ESCAPE_CODE; break;
				case 1: U1TXREG = END_CODE; break;     // last byte of pkt
				default:
					TxPacket->length = 0;
					TxPacket->done = 1;
					IEC0bits.U1TXIE = 0;
					//U1MODEbits.UARTEN = 1; do we need this? enables uart when it is already enabled
				}
			}
	}
	txByte++;
}


