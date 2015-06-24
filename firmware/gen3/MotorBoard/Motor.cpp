/* 
* Motor.cpp
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/

#include "Motor.h"
#include <avr/io.h>

// default constructor
Motor::Motor(PWM output, pin_def tempPin, pin_def currentPin) :
	wheel(output),
	monitor(HealthMonitor(tempPin, currentPin, pin_def(&PORTG, (int)wheel))),
	qei(QEI_Handler(wheel)),
	pid(PID_Handler())
{}

// returns the duty cycle from the pid controller based on the speed
void Motor::update() {
	monitor.update();
}

bool Motor::setSpeed(double speed) {
	pid.setSetPoint(speed);
	return monitor.getStatus() == STATUS_OK;
}

double Motor::getSpeed() {
	return qei.getSpeed();
}

double Motor::getDutyCycle(double dt) {
	double duty = pid.getDutyCycle(qei.getSpeed(), dt);
	qei.clearCount();
	return duty;
}

HealthStatus Motor::getStatus() {
	return monitor.getStatus();
}

void Motor::handleQEI() {
	qei.update();
}
