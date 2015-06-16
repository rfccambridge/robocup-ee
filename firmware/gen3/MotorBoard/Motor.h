/* 
* Motor.h
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/


#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "HealthMonitor.h"

class Motor
{
private:
	HealthMonitor* monitor;
	QEI_Handler* qei;
	PID_Handler* pid;

//functions
public:
	Motor();
	void setSpeed(double);
	double getSpeed(double);
	HealthStatus getStatus();
}; //Motor

#endif //__MOTOR_H__
