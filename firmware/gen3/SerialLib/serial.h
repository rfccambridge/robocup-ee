/*
 * serial.h
 *
 * Created: 4/4/2015 2:04:10 AM
 *  Author: Karl
 */ 

#include "commcore.h"
#include <stdbool.h>

#ifndef SERIAL_H_
#define SERIAL_H_

//bool serialPushInbox(const message* msg);
int serialPopInbox(message* msg);
//int serialGetInboxSize();
bool serialPushOutbox(const message* msg);
bool serialPopOutbox(message* msg);
int serialGetOutboxSize();

#endif /* SERIAL_H_ */