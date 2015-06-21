/* 
* FilteredPin.h
*
* Created: 6/20/2015 6:58:32 AM
* Author: Ezra
*/


#ifndef __FILTEREDPIN_H__
#define __FILTEREDPIN_H__

#include "EELib.h"
#include "FilteredVariable.h"

class FilteredPin
{
//variables
public:
protected:
private:
	pin_def inputPin;
	FilteredVariable filtered; 

//functions
public:
	FilteredPin(pin_def inputPin);
	double update();
	double getValue();
};

#endif //__FILTEREDPIN_H__
