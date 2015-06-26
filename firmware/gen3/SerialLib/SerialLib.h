/*
 * serial.h
 *
 * Created: 4/4/2015 2:04:10 AM
 *  Author: Karl
 */ 
#include "commcore.h"
#include <stdbool.h>

#ifndef SERIALLIB_H_
#define SERIALLIB_H_

void initSerial();
//bool serialPushInbox(const message* msg);
int serialPopInbox(message* msg);
//int serialGetInboxSize();
bool serialPushOutbox(const message* msg);
bool serialPopOutbox(message* msg);
int serialGetOutboxSize();

#endif /* SERIALLIB_H_ */