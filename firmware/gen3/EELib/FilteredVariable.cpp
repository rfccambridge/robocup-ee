/* 
* FilteredVariable.cpp
*
* Created: 6/15/2015 3:51:00 PM
* Author: Ezra
*/


#include "FilteredVariable.h"
#include "EELib.h"

FilteredVariable::FilteredVariable(pin_def pin)
{
	inputPin = pin;
}

// This will actually handle running the ADC and other filtering
double FilteredVariable::getValue()
{
	return getBit(inputPin);
}
