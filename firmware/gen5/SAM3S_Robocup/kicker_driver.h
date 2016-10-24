#ifndef KICK_REF
#define KICK_REF

#include "board.h"
#include <asf.h>

// set the reference voltage to set kick speed
void set_kick_ref(int); 

// enable kicker
void kick_enable(void);

// enable chipper
void chip_enable (void);

#endif /* KICK_REF */