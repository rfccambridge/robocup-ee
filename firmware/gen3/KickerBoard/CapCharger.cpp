#include "CapCharger.h"

CapCharger::CapCharger(pin_def chargeControl, pin_def doneRead,
					   pin_def dischargeControl, pin_def chargeScale,
					   double chargeLimit) :
					   chargePin(chargeControl), donePin(doneRead),
					   dischargePin(dischargeControl), chargeAdcPin(chargeScale.pin),
					   maxCharge(chargeLimit)
{
	setUpADC();
	// Prevent capacitor discharging
	setBit(dischargePin, true);
}

bool CapCharger::isCharging()
{
	return getBit(chargePin);
}

bool CapCharger::chargeDone() {
	return !getBit(donePin);
}

void CapCharger::startCharge(double targetCharge) {
	setpoint = targetCharge;
	setBit(chargePin, true);
}

void CapCharger::stopCharge() {
	setBit(chargePin, false);
}

void CapCharger::discharge() {
	stopCharge();
	setBit(dischargePin, false);
	while(getCharge() > CAP_DISCHARGE_MAX) {};
	setBit(dischargePin, true);
}

double CapCharger::getCharge() {
	return readADC(chargeAdcPin);
}

void CapCharger::update() {
	double curCharge = getCharge();
	if(curCharge >= setpoint || curCharge >= maxCharge){
		stopCharge();
	}
	// TODO: Add safety logic
}