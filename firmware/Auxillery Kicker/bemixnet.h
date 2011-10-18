// === BemixNet ===

#ifndef __BEMIXNET_H
#define __BEMIXNET_H

#define MAX_PACKET_SIZE 32

#define ESCAPE_CODE '\\'
#define HEADER_CODE 'H'
#define END_CODE    'E'
#define THIS_BOARD  'v'

typedef struct {
	unsigned char address;							// source for rx, my identity for tx
	unsigned char chksum;	                        // computed checksum (data only, escape char counted once)
	unsigned char port;								// command: 'w' = wheel speeds, etc.
	unsigned char data[MAX_PACKET_SIZE];
	unsigned length:7;
	unsigned done:1;
} PacketBuffer;

enum ReceiveState {ESCAPE, HEADER, SOURCE, PORT, CHKSUM, DATA, DATAESC, IGNORE};

extern unsigned char pktsReceived, pktsAccepted, pktsMismatched;

void handleRx(PacketBuffer * RxPacket);

void handleTx(PacketBuffer * TxPacket);
void transmit(PacketBuffer * TxPacket);

void initRx(PacketBuffer * RxPacket);
void initTx(PacketBuffer * TxPacket);

void delay(void);

unsigned char getAddress(void);

#endif
