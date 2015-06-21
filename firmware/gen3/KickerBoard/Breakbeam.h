#ifndef BREAKBEAM_H_
#define BREAKBEAM_H_

#include "EELib.h"

// Minimum number of reads to determine beam broken
#define BB_MIN_CYCLES 5

class Breakbeam {
	private:
		pin_def beamPin;
		pin_def receivePin;
		unsigned char breakCount;
		
	public:
		Breakbeam(pin_def beamOutPin, pin_def beamSensePin);
		// Needs manual interrupt setup to handle interrupt firing
		void update();
		// True if beam is currently seen as broken 
		bool isBrokenRaw();
		bool isBroken();
};


#endif /* BREAKBEAM_H_ */