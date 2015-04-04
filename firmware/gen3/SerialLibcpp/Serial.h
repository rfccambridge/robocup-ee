/*
 * IncFile1.h
 *
 * Created: 3/28/2015 5:44:21 PM
 *  Author: Karl
 */ 


#ifndef __SERIAL_H__
#define __SERIAL_H__

#define MSG_BYTES 3

typedef struct message
{
	/* The ID of the destination XBee. 
	 * Only used for outbound messages. */
	short rfID;
	/* The ID of the destination slave. */
	char slaveID;
	/* The actual bytes of this message.
	 * Command, and arguments. */
	char[MSG_BYTES] message;
} message;

/*

class RFMessage {
	public:
	const unsigned short destId;
	const char[3] message;
	};

class Serial {
	public:
	static const Serial instance = Serial();
	
	int inboxSize();
	char popInbox();
	
	int outboxSize();
	bool pushOutbox(char);
	
	private:
	Serial();
	bool pushInbox(char);
	char popOutbox();
};



#endif /* __SERIAL_H__ */*/