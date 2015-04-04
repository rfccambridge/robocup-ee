/*
 * serial.h
 *
 * Created: 4/4/2015 2:04:10 AM
 *  Author: Karl
 */ 

#include "serialmessage.h"
#include <stdbool.h>

#ifndef SERIAL_H_
#define SERIAL_H_

bool pushInbox(const message* msg);
bool popInbox(message* msg);
int getInboxSize();
bool pushOutbox(const message* msg);
bool popOutbox(message* msg);
int getOutboxSize();

#endif /* SERIAL_H_ */