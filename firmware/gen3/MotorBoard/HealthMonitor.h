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

// TODO: Set these to real values
const double MAXTEMP = 1085.0; // melting point of copper
const double MAXCURRENT = 20.0; 

typedef enum status {
	STATUS_OK,
	STATUS_OVERHEAT,
	STATUS_OVERCURRENT,
	STATUS_FAULT,
	STATUS_UNKNOWNERROR	
} HealthStatus;

class HealthMonitor
{
//variables
private:
	FilteredVariable* temp;
	FilteredVariable* current; 
	pin_def* fault;

//functions
public:
	HealthMonitor(pin_def tempPin, pin_def currentPin, pin_def faultPin);
	HealthStatus getStatus();
	double getTemp();
	double getCurrent();
	bool getFault();
};

#endif //__HEALTHMONITOR_H__
