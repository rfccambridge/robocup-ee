#include <util/delay.h>
#include "Kicker.h"

Kicker::Kicker(pin_def kickEnablePin, pin_def chipEnablePin) : kickPin(kickEnablePin), chipEnable(chipEnablePin)
{
	setBit(chipEnable, true);
}

void Kicker::kick()
{
	// Kick and sleep until done
	setBit(kickPin, true);
	_delay_ms(25.0);
	setBit(kickPin, false);
}