/* 
* FilteredPin.cpp
*
* Created: 6/20/2015 6:58:32 AM
* Author: Ezra
*/


#include "FilteredPin.h"

FilteredPin::FilteredPin(pin_def inputPin) :
	inputPin(inputPin.port, inputPin.pin),
	filtered(readADC(inputPin.pin))
{} //FilteredPin

double FilteredPin::update() {
	return filtered.update(readADC(inputPin.pin));
}

double FilteredPin::getValue() {
	return filtered.getValue();
}
