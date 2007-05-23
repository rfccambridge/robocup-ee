// kicker.c

#include "kicker.h"
#include "pins.h"
#include <p18f4431.h>

static enum KickerState kickState;

KickerControl kickCon;

void initKicker()
{
	K_CHARGE = 0;
	K_DISCHARGE = 0;
	K_KICK1 = 1;
	K_KICK2 = 1;
	K_KICK3 = 1;
	K_KICK4 = 1;

	kickState = DISCHARGE;

	kickCon.enable = 0;
	kickCon.kick1 = 0;
	kickCon.kick2 = 0;
	kickCon.kick3 = 0;
	kickCon.kick4 = 0;
	kickCon.kick = 0;
	kickCon.charged = 0;
	kickCon.updated = 0;
}


void handleKicker()
{
	kickCon.updated = 1;

	switch (kickState){
		case DISCHARGE:
			K_CHARGE = 0;
			K_DISCHARGE = 1;
			K_KICK1 = 0;
			K_KICK2 = 0;
			K_KICK3 = 0;
			K_KICK4 = 0;
			if (kickCon.enable)
				kickState = CHARGE;
			break;
		case CHARGE:
			K_CHARGE = 1;
			K_DISCHARGE = 0;
			K_KICK1 = 1;
			K_KICK2 = 1;
			K_KICK3 = 1;
			K_KICK4 = 1;
			if (!kickCon.enable)
				kickState = DISCHARGE;
			else if (kickCon.kick)
				kickState = KICK;
			else if (K_OVERVOLTAGE)
				kickState = FULL;
			break;
		case FULL:
			K_CHARGE = 0;
			K_DISCHARGE = 0;
			K_KICK1 = 1;
			K_KICK2 = 1;
			K_KICK3 = 1;
			K_KICK4 = 1;
			if (!kickCon.enable)
				kickState = DISCHARGE;
			else if (kickCon.kick)
				kickState = KICK;
			else if (!K_OVERVOLTAGE)
				kickState = CHARGE;
			break;
		case KICK:
			K_CHARGE = 0;
			K_DISCHARGE = 0;
			K_KICK1 = kickCon.kick1;
			K_KICK2 = kickCon.kick1;
			K_KICK3 = kickCon.kick1;
			K_KICK4 = kickCon.kick1;
			kickCon.kick = 0;
			if (kickCon.enable)
				kickState = CHARGE;
			else
				kickState = DISCHARGE;
			break;
		default:
			// error
			kickState = DISCHARGE;
			break;
	}
}
