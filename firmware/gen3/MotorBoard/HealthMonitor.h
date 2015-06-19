/* 
* HealthMonitor.h
*
* Created: 6/15/2015 4:17:41 PM
* Author: Ezra
*/


#ifndef __HEALTHMONITOR_H__
#define __HEALTHMONITOR_H__

#include "FilteredVariable.h"
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
	FilteredVariable temp;
	FilteredVariable current; 
	pin_def faultPin;
	int tempPin;
	int currentPin;
	HealthStatus status;
	

//functions
private:
	double updateTemp();
	double updateCurrent();
	
public:
	HealthMonitor(pin_def tempPin, pin_def currentPin, pin_def faultPin);
	void update();
	HealthStatus getStatus();
	double getTemp();
	double getCurrent();
	bool getFault();
};

#endif //__HEALTHMONITOR_H__
