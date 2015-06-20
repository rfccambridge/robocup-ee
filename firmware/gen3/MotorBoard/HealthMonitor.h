/* 
* HealthMonitor.h
*
* Created: 6/15/2015 4:17:41 PM
* Author: Ezra
*/


#ifndef __HEALTHMONITOR_H__
#define __HEALTHMONITOR_H__

#include "FilteredPin.h"
#include "EELib.h"

const double RSENSE = .020; // ohms
const double MAXTEMP = 85.0; // C
const double MAXCURRENT = 20.0; // Amps

typedef enum status {
	STATUS_OK,
	STATUS_OVERHEAT,
	STATUS_OVERCURRENT,
	STATUS_FAULT,
	STATUS_UNKNOWNERROR,
	STATUS_BURNED,	
} HealthStatus;

class HealthMonitor
{
//variables
private:
	FilteredPin temp;
	FilteredPin current; 
	pin_def faultPin;
	HealthStatus status;
	

//functions
public:
	HealthMonitor(pin_def tempPin, pin_def currentPin, pin_def faultPin);
	void update();
	HealthStatus getStatus();
	double getTemp();
	double getCurrent();
	bool getFault();
};

#endif //__HEALTHMONITOR_H__
