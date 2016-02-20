/* 
* FilteredPin.cpp
*
* Created: 12/5/2015 5:13:51 PM
* Author: Ezra Zigmond
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