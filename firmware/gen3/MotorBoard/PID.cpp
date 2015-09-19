
#include "PID.h"
	
// constructor, called once when first created
PID_Handler::PID_Handler() {
	k_d = 0;
	k_i = 0;
	k_p = 1;
	set_point = 0;
	last_e = 0;
	last_i = 0;
}
	
void PID_Handler::setSetPoint(int set) {
	set_point = set;
}

double PID_Handler::getDutyCycle(double speed, double dt) {
	// calculate difference between desired and actual speeds
	double error = set_point - speed;
	// calculate rate of change of error
	double deriv = (error - last_e)/dt; 
	// calculate current integral 
	double integral = last_i + error * dt; 
	
	// check for overflow of integral term
	// (if the error is positive, but the integral suddenly changed
	// from positive to negative)
	if (last_i > 0 && error > 0 && integral < 0) {
		integral = 	0x7FFFFFFF; // max positive (2^31-1)
	}
	// check for underflow
	// (if the error is negative, but the integral suddenly changed
	// from negative to positive)
	if (last_i < 0 && error < 0 && integral > 0) {
		integral = -0x80000000; // max negative (2^31)
	}
	
	// calculate control signal
	double duty = k_p*error + k_i*integral + k_d*deriv; 
		
	// set last error and last integral values
	last_e = error;
	last_i = last_i + integral;
		
	// make sure duty cycle is within limits
	if (duty > MAX_DUTY) {
		duty = MAX_DUTY;
	}
	if (duty < MIN_DUTY) {
		duty = MIN_DUTY;
	}
	
	return duty;
}

void PID_Handler::setConstants(double error, double integral, double derivative) {
	k_p = error;
	k_i = integral;
	k_d = derivative;
}