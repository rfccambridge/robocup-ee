/* 
* FilteredVariable.h
*
* Created: 6/15/2015 3:51:00 PM
* Author: Ezra
*/


#ifndef __FILTEREDVARIABLE_H__
#define __FILTEREDVARIABLE_H__

#include "EELib.h"

class FilteredVariable
{
private:
	pin_def inputPin;

//functions
public:
	FilteredVariable(pin_def inputPin);
	double getValue();
}; //FilteredVariable

#endif //__FILTEREDVARIABLE_H__
