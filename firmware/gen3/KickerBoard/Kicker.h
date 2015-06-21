#ifndef KICKER_H_
#define KICKER_H_

#include "EELib.h"

class Kicker {
	private:
		pin_def kickPin;
		
	public:
		Kicker(pin_def enablePin);
		void kick();
};

#endif /* KICKER_H_ */