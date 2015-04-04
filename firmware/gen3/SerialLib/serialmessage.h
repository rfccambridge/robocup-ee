/*
 * serialmessage.h
 *
 * Created: 4/4/2015 2:03:24 AM
 *  Author: Karl
 */ 


#ifndef SERIALMESSAGE_H_
#define SERIALMESSAGE_H_

#define SERIAL_MSG_CHARS 3

typedef struct message
{
	/* The ID of the destination slave. */
	char slaveID;
	/* The actual bytes of this message.
	 * Command, and arguments. */
	char message[SERIAL_MSG_CHARS];
}message;

#endif /* SERIALMESSAGE_H_ */