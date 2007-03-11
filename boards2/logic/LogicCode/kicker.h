// kicker.h

#ifndef __KICKER_H
#define __KICKER_H

typedef struct{
	unsigned enable:1;			// set and the interrupt will maintain the cap voltage
	unsigned kick1:1;
	unsigned kick2:1;
	unsigned kick3:1;
	unsigned kick4:1;
	unsigned kick:1;			// set to kick with with selected caps	
	unsigned charged:1;			// set when at least one cap is charged
	unsigned updated:1;			// set by interrupt, clear in main
} KickerControl;

enum KickerState {CHARGE, FULL, KICK, DISCHARGE};



void initKicker();
void handleKicker();

#endif //__KICKER_H
