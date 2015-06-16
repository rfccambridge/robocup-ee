/* 
* Motor.cpp
*
* Created: 6/15/2015 5:26:20 PM
* Author: Ezra
*/


#include "Motor.h"

// default constructor
Motor::Motor()
{
}

void Motor::setSpeed(double) {
}

double Motor::getSpeed() {
	
}

void Motor::getStatus() {
	return monitor->getStatus();
}
