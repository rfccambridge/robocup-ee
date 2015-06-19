/* 
* FilteredVariable.cpp
*
* Created: 6/15/2015 3:51:00 PM
* Author: Ezra
*/


#include "FilteredVariable.h"

FilteredVariable::FilteredVariable(double init_val)
{
	// useful link on filter design:
	//http://www-users.cs.york.ac.uk/~fisher/mkfilter/trad.html
	
	// for now a 2nd order low pass butterworth filter
	// 10 Hz cutoff, for 1000Hz sample rate
	gamma_x[0] = 1.0;
	gamma_x[1] = 2.0;
	gamma_x[2] = 1.0;
	gamma_y[0] = 0; // just here for show
	gamma_y[1] = 1.911197;
	gamma_y[2] = -0.91497;
	
	for(int i = 0; i < 3; ++i)
		x[i] = init_val;
	for(int i = 0; i < 3; ++i)
		y[i] = init_val;
}

// This will actually handle running the ADC and other filtering
double FilteredVariable::update(double input)
{
	// updating X
	x[2] = x[1];
	x[1] = x[0];
	x[0] = input;
	
	//updating y
	y[2] = y[1];
	y[1] = y[0];
	
	// getting new output
	y[0] = gamma_x[0]*x[0] + gamma_x[1]*x[1] + gamma_x[2]*x[2] +
			gamma_y[1]*y[1] + gamma_y[2]*y[2];
	return y[0];
}

double FilteredVariable::getValue() {
	return y[0];
}
