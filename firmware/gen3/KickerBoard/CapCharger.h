#ifndef CAPCHARGER_H_
#define CAPCHARGER_H_

#include "EELib.h"

#define CAP_DISCHARGE_MAX 0.05

class CapCharger {
	private:
		pin_def chargePin;
		pin_def donePin;
		pin_def dischargePin;
		int chargeAdcPin;
		double setpoint;
		double maxCharge;
	
	public:
		CapCharger(pin_def chargeControl, pin_def doneRead,
				   pin_def dischargeControl, pin_def chargeScale,
				   double chargeLimit);
		void startCharge(double targetCharge);
		void stopCharge();
		bool isCharging();
		bool chargeDone();
		void discharge();
		void update();
		double getCharge();
};

#endif /* CAPCHARGER_H_ */