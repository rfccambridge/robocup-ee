#ifndef SERIALMESSAGE_H_
#define SERIALMESSAGE_H_

#include <stdbool.h>

#define SERIAL_MSG_CHARS 3
#define BOX_SIZE 10

typedef struct message
{
	/* The ID of the destination slave. */
	char slaveID;
	/* The actual bytes of this message.
	 * Command, and arguments. */
	char message[SERIAL_MSG_CHARS];
}message;

typedef struct messageQueue {
	unsigned int size;
	unsigned int first;
	message box[BOX_SIZE];
} messageQueue;

bool mqPushMessage(const message* message, messageQueue* mq);
bool mqPopMessage(message* dest, messageQueue* mq);
int mqGetSize(const messageQueue* mq);
int mqGetCapacity(const messageQueue* mq);

#endif /* SERIALMESSAGE_H_ */