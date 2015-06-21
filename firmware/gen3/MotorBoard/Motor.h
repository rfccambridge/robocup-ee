/* 
* Motor.h
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/


#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "HealthMonitor.h"
#include "PID.h"
#include "QEI.h"

class Motor
{
private:
	PWM wheel;
	HealthMonitor monitor;
	QEI_Handler qei;
	PID_Handler pid;

//functions
public:
	Motor(PWM output, pin_def tempPin, pin_def currentPin);
	bool setSpeed(double);
	double getSpeed();
	HealthStatus getStatus();
	double update();
	void handleQEI();
}; //Motor

#endif //__MOTOR_H__
