/* 
* HealthMonitor.cpp
*
* Created: 6/15/2015 4:17:41 PM
* Author: Ezra
*/


#include "HealthMonitor.h"
#include "EELib.h"

HealthMonitor::HealthMonitor(pin_def tempPin, pin_def currentPin, pin_def faultPin) :
	temp(FilteredVariable(0.0)),
	current(FilteredVariable(0.0)),
	fault(pin_def(faultPin.port, faultPin.pin))	
{}

HealthStatus HealthMonitor::getStatus() {
	if (getTemp() > MAXTEMP) {
		return STATUS_OVERHEAT;
	} else if (getCurrent() > MAXCURRENT) {
		return STATUS_OVERCURRENT;
	} else if (getFault()) {
		return STATUS_FAULT;
	} else {
		return STATUS_OK;
	}
}
double HealthMonitor::getTemp() {
	return temp.getValue();
}
double HealthMonitor::getCurrent() {
	return current.getValue();
}
bool HealthMonitor::getFault() {
	return getBit(fault);
}
