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
	double gamma_x[3];
	double gamma_y[3];
	double x[3];
	double y[3];
	

//functions
public:
	FilteredVariable(double init_val);
	double update(double input);
	double getValue();
}; //FilteredVariable

#endif //__FILTEREDVARIABLE_H__
