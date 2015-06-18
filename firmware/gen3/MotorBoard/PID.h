/*
 * PID.h
 *
 * Created: 6/15/2015 5:50:47 PM
 *  Author: Ezra
 */ 


#ifndef PID_H_
#define PID_H_

#include "EELib.h"

class PID_Handler {
	private:
	// which output we're working with
	PWM wheel;
	double k_p;
	double k_i;
	double k_d;
	
	double last_e;
	double last_i;
	
	// frequency at which PID will be called
	double dt;
	
	double set_point;
	
	public:
	PID_Handler(PWM output);
	void setSpeed(double speed);
	
	private:
	double getDutyCycle(double speed);
};

#endif /* PID_H_ */