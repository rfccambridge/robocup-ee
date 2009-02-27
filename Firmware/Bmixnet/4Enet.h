// === BemixNet ===

#ifndef __BEMIXNET_H
#define __BEMIXNET_H

#define MAX_PACKET_SIZE 20

#define ESCAPE_CODE '\\'
#define HEADER_CODE 'H'
#define END_CODE    'E'

typedef struct {

	// Destination seems to be unused. This should be investigated
	unsigned char destination;

	// The fourth byte of the packet goes into the address. I'm not sure what
	// it's used for
	unsigned char address;	

	// The port seems to identify which component the instructions are for. The
	// only identification I know is that 'w' means that the instruction is for
	// the wheels						
	unsigned char port;	

	// This is the data. In a wheels command, it contains the wheel speeds							
	unsigned char data[MAX_PACKET_SIZE];

	// Length is for making sure that the packet doesn't overflow
	unsigned length:7;

	// Flag for telling the program whether the packet is done. 0 means no
	unsigned done:1;

} PacketBuffer;

enum ReceiveState {ESCAPE, HEADER, SOURCE, PORT, DATA, DATAESC, IGNORE};

void handleRx(PacketBuffer * RxPacket);

void handleTx();
void transmit();

void initRx(PacketBuffer * RxPacket);
void initTx(PacketBuffer TxPacket);

void delay();

unsigned char getAddress();

#endif
