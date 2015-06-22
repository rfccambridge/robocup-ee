/*
 * PID.h
 *
 * Created: 6/15/2015 5:50:47 PM
 *  Author: Ezra
 */ 


#ifndef PID_H_
#define PID_H_

#include "EELib.h"

// duty cycle is a percentage between 0 and 1
// (the EELib takes care of turning this percentage into an 8bit integer) 
const double MAX_DUTY = 1.0;
const double MIN_DUTY = 0.0;

class PID_Handler {
	private:
	double k_p;
	double k_i;
	double k_d;
	
	// keep these as integers because handling overflow is much nicer than with floats
	long last_e;
	long last_i;

	double set_point; // m/s
	
	public:
	PID_Handler();
	void setSetPoint(double set);
	void setConstants(double error, double integral, double derivative);
	double getDutyCycle(double speed, double dt);
};

#endif /* PID_H_ */