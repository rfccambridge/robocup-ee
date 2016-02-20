/* 
* FilteredVariable.h
*
* Created: 12/5/2015 5:11:47 PM
* Author: Ezra Zigmond
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
