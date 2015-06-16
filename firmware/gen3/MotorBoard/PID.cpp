
#include "PID.h"	
// constructor, called once when first created
PID_Handler::PID_Handler() {
	k_d = 1;
	k_i = 1;
	k_p = 1;
	set_point = 0;
	last_e = 0;
	last_i = 0;
	// TODO (what is actual frequency?)
	dt = .1;
}
		
double PID_Handler::get_duty_cycle(double speed) {
	// calculate difference between desired and actual speeds
	double error = set_point - speed;
	// calculate rate of change of error
	double deriv = (error - last_e)/dt; 
	// calculate current integral 
	double integrl = last_i + error * dt; 
	// calculate control signal
	double duty_cycle = k_p*error + k_i*integrl + k_d*deriv; 
		
	// set last error and last integral values
	last_e = error;
	last_i = last_i + integrl;
		
	return duty_cycle;
}