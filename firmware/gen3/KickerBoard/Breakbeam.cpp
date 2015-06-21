#include <limits.h>
#include "Breakbeam.h"

Breakbeam::Breakbeam(pin_def beamOutPin, pin_def beamSensePin) : beamPin(beamOutPin), receivePin(beamSensePin)
{
	
}

void Breakbeam::update()
{
	if(!isBrokenRaw())
	{
		breakCount = 0;
		return;
	}
	// Avoid overflowing the counter
	if(breakCount < UCHAR_MAX)
	{
		breakCount++;
	}
}

bool Breakbeam::isBrokenRaw()
{
	return !getBit(receivePin);
}

bool Breakbeam::isBroken()
{
	// For now just count cycles where the beam was broken
	// Pulsing is more complicated and this should at least be a good start
	return breakCount >= BB_MIN_CYCLES;
}