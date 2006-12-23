// === BemixNet ===

#ifndef __BEMIXNET_H
#define __BEMIXNET_H

#define MAX_PACKET_SIZE 20

#define ESCAPE_CODE '\\'
#define HEADER_CODE 'H'
#define END_CODE    'E'

#define MY_ADDRESS  'v'

//#define TX_ENABLE PORTAbits.RA0

typedef struct {
	unsigned char address;							// source for rx, destination for tx
	unsigned char port;
	unsigned char data[MAX_PACKET_SIZE];
	unsigned length:7;
	unsigned done:1;
} PacketBuffer;

enum RecieveState {ESCAPE, HEADER, SOURCE, PORT, DATA, DATAESC, IGNORE};

void handleRx(PacketBuffer * RxPacket);

void handleTx(PacketBuffer * TxPacket);
void transmit(PacketBuffer * TxPacket);

void initRx(PacketBuffer * RxPacket);
void initTx(PacketBuffer * TxPacket);

void delay();

#endif
