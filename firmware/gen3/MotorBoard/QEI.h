/*
 * QEI.h
 *
 * Created: 6/15/2015 5:50:23 PM
 *  Author: Ezra
 */ 


#ifndef QEI_H_
#define QEI_H_

#include "EELib.h"

const int lookuptable[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

class QEI_Handler 
{
private:
	PWM wheel;
	int direction;
	int count;
	int enc_val;
	double speed; 	
	
public:
	QEI_Handler(PWM output);
	double getSpeed();
	double update(double);
};


#endif /* QEI_H_ */