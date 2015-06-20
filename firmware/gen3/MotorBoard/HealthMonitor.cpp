/* 
* HealthMonitor.cpp
*
* Created: 6/15/2015 4:17:41 PM
* Author: Ezra
*/


#include "HealthMonitor.h"
#include "EELib.h"

HealthMonitor::HealthMonitor(pin_def tempPin, pin_def currentPin, pin_def faultPin) :
	temp(FilteredPin(tempPin)),
	current(FilteredPin(currentPin)),
	faultPin(pin_def(faultPin.port, faultPin.pin)),
	status(STATUS_OK)
{}

// Update the filtered variables and the current status
void HealthMonitor::update() {
	if (temp.update() > MAXTEMP) {
		status = STATUS_OVERHEAT;
	}
	// The value stored in the current FilteredVariable will be the voltage
	// read in from the ADC. By Ohm's law, the current will be I = V/R
	// (dear Erik: please double check I didn't mess this up this so that the robots don't catch on fire)
	else if (current.update() / RSENSE > MAXCURRENT) {
		status = STATUS_OVERCURRENT;
	} else if (getFault()) {
		status = STATUS_FAULT;
	} else {
		status = STATUS_OK;
	}
}

HealthStatus HealthMonitor::getStatus() {
	return status;
}

double HealthMonitor::getTemp() {
	return temp.getValue();
}
double HealthMonitor::getCurrent() {
	return current.getValue();
}
bool HealthMonitor::getFault() {
	return getBit(faultPin);
}
