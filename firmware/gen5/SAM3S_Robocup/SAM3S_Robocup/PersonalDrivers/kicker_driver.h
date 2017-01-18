#ifndef KICK_REF
#define KICK_REF

#include "board.h"
#include <asf.h>

// set up kicker
void configure_kicker(void);

// set the reference voltage to set kick speed
void set_kick_ref(uint32_t speed); 

// enable kicker
void kick_enable(void);

// enable chipper
void chip_enable (void);

#endif /* KICK_REF */