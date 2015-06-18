/* 
* Motor.cpp
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/


#include "Motor.h"
#include <avr/io.h>

// default constructor
Motor::Motor(PWM output, pin_def tempPin, pin_def currentPin)
{
	wheel = output;
	monitor = new HealthMonitor(tempPin, currentPin, pin_def(&PORTG, (int)wheel));
	qei = new QEI_Handler(wheel);
	pid = new PID_Handler(wheel);
}

void Motor::setSpeed(double speed) {
	pid->setSpeed(speed);
}

double Motor::getSpeed() {
	return qei->getSpeed();
}

HealthStatus Motor::getStatus() {
	return monitor->getStatus();
}
