/*
 * PID.h
 *
 * Created: 6/15/2015 5:50:47 PM
 *  Author: Ezra
 */ 


#ifndef PID_H_
#define PID_H_


class PID_Handler {
	private:
	double k_p;
	double k_i;
	double k_d;
	
	double last_e;
	double last_i;
	
	// frequency at which PID will be called
	double dt;
	
	public:
	PID_Handler();
	double set_point;
	double get_duty_cycle(double);
};

#endif /* PID_H_ */