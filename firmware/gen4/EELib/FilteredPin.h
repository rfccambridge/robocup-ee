/* 
* FilteredPin.h
*
* Created: 12/5/2015 5:13:51 PM
* Author: Ezra Zigmond
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
