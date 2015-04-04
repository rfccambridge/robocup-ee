#include <avr/io.h>
#include "Serial.h"
#include <stdbool.h>
#include <util/atomic.h>
#include <stdlib.h>
#include <string.h>

#define BOX_SIZE 10

unsigned int inboxSize = 0;
message inbox[BOX_SIZE];

unsigned int outboxSize = 0;
message outbox[BOX_SIZE];

bool pushMessage(message* msg, message* box, int* size){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(*size >= BOX_SIZE){
			return false;
		}
		memcpy(&box[*size], msg, sizeof(message))
		(*size)++;
		return true;
	}
}

bool popMessage(message* dest, message* box, int* size){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(*size <= 0){
			return false;
		}
		memcpy(dest, &box[*size - 1], sizeof(message));
		(*size)--;
		return true;
	}
}

bool pushInbox(message* msg){
	return pushMessage(msg, &inbox[0], &inboxSize);
}

bool popInbox(message* dest){
	return popMessage(dest, &inbox[0], &inboxSize);
}

bool pushOutbox(message* msg){
	return pushMessage(msg, &outbox[0], &outboxSize);
}

bool popOutbox(message* msg){
	return popMessage(msg, &outbox[0], &outboxSize);
}

/*
Serial::Serial() {
}*/