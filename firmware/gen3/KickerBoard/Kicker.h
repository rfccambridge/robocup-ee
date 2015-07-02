#ifndef KICKER_H_
#define KICKER_H_

#include "EELib.h"

class Kicker {
	private:
		pin_def kickPin;
		pin_def chipEnable;
		
	public:
		Kicker(pin_def kickEnablePin, pin_def chipEnablePin);
		void kick();
};

#endif /* KICKER_H_ */