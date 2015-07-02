/* 
* Motor.cpp
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/

#include "Motor.h"
#include <avr/io.h>
#include "EELib.h"

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

// 127 is not moving
// 0 is full speed backwards
// 255 is full speed forwards
bool Motor::setSpeed(int speed) {
	if (speed < 127) {
		setDirection(false);
	} else {
		setDirection(true);
	}
	
	int magnitude = abs(127 - speed);
	pid.setSetPoint(magnitude);
	
	return monitor.getStatus() == STATUS_OK;
}

void Motor::setDirection(bool dir) {
	// the dir pins are PINS D0, D1, D2, D3
	setBit(&PORTD, (int)wheel, dir);
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
