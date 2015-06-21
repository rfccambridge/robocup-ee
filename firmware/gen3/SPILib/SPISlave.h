/* 
* SPISlave.h
*
* Created: 3/24/2015 1:24:46 PM
* Author: David
*/

#ifndef __SPISLAVE_H__
#define __SPISLAVE_H__

#include "Command.h"

class SPISlave {
private:
	// state: 0 waiting; 1-5 number of bytes received (start, command, arg1, arg2, checksum); 6 given data to GetCommand; 7 reply ready (sending start byte); 8-10 sending response bytes (checksumEcho, reply, checksum)
	char m_state;
	char m_command;
	char m_arg1;
	char m_arg2;
	char m_arg3;
	char m_arg4;
	char m_checksum;
	char m_reply;
public:
	SPISlave();
	
	// should be called every iteration of main loop to handle periodic tasks
	void ReceiveSPI();
	
	// get a command if one was sent
	// does not wait for one
	// returns false if no command
	bool GetCommand(Command* command);
	
	// gets a simple byte for debugging
	char getChar();
	
	// after getting a command, this function should be called so that a response is sent acknowledging the command
	// the reply argument can be used to send back info (could be errors, or could be used to make commands that ask for data)
	void SetReply(char reply);
};

#endif //__SPISLAVE_H__
