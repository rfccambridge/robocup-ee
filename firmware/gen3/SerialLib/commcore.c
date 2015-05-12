#include <util/atomic.h>
#include <string.h>
#include "commcore.h"

bool mqPopMessage(message* dest, messageQueue* mq){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(mq->size <= 0){
			return false;
		}
		memcpy(dest, &(mq->box[mq->first]), sizeof(message));
		mq->first = (mq->first + 1) % BOX_SIZE;
		(mq->size)--;
	}
	return true;
}

bool mqPushMessage(const message* msg, messageQueue* mq){
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
		if(mq->size >= BOX_SIZE){
			return false;
		}
		unsigned int idx = (mq->first + mq->size) % BOX_SIZE;
		memcpy(&(mq->box[idx]), msg, sizeof(message));
		(mq->size)++;
	}
	return true;
}

int mqGetSize(const messageQueue* mq){
	return mq->size;
}

int mqGetCapacity(const messageQueue* mq){
	return BOX_SIZE - mq->size;
}