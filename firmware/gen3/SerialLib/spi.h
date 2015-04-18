#ifndef SPI_H_
#define SPI_H_

#include "commcore.h"

bool spiPushInbox(const message* msg);
bool spiPopInbox(message* msg);
int spiGetInboxSize();
bool spiPushOutbox(const message* msg);
bool spiPopOutbox(message* msg);
int spiGetOutboxSize();

#endif /* SPI_H_ */