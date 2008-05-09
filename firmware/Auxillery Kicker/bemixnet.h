// === BemixNet ===

#ifndef __BEMIXNET_H
#define __BEMIXNET_H

#define MAX_PACKET_SIZE 32

#define ESCAPE_CODE '\\'
#define HEADER_CODE 'H'
#define END_CODE    'E'

typedef struct {
	unsigned char destination;
	unsigned char address;				// source for rx, destination for tx
	unsigned char port;					//'w' = wheels
	unsigned char data[MAX_PACKET_SIZE];
	unsigned length:7;
	unsigned done:1;
} PacketBuffer;

enum ReceiveState {ESCAPE, HEADER, SOURCE, PORT, DATA, DATAESC, IGNORE};

void handleRx(PacketBuffer * RxPacket);

void handleTx(PacketBuffer * TxPacket);
void transmit(PacketBuffer * TxPacket);

void initRx(PacketBuffer * RxPacket);
void initTx(PacketBuffer * TxPacket);

void delay();

unsigned char getAddress();

#endif
