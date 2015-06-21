#include <util/delay.h>
#include "Kicker.h"

Kicker::Kicker(pin_def enablePin) : kickPin(enablePin)
{
	
}

void Kicker::kick()
{
	// Kick and sleep until done
	setBit(kickPin, true);
	_delay_ms(25.0);
	setBit(kickPin, false);
}