#include "spi.h"

messageQueue inbox;
messageQueue outbox;

bool spiPushInbox(const message* msg){
	return mqPushMessage(msg, &inbox);
}

bool spiPopInbox(message* dest){
	return mqPopMessage(dest, &inbox);
}

int spiGetInboxSize(){
	return mqGetSize(&inbox);
}

bool spiPushOutbox(const message* msg){
	return mqPushMessage(msg, &outbox);
}

bool spiPopOutbox(message* msg){
	return mqPopMessage(msg, &outbox);
}

int spiGetOutboxSize(){
	return mqGetSize(&outbox);
}