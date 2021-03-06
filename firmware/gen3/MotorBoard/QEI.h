/*
 * QEI.h
 *
 * Created: 6/15/2015 5:50:23 PM
 *  Author: Ezra
 */ 


#ifndef QEI_H_
#define QEI_H_

#include "EELib.h"

const int LOOKUP_TABLE[16] = {0,-1,1,2,1,0,2,-1,-1,0,2,1,2,1,-1,0};

class QEI_Handler 
{
private:
	PWM wheel;
	int direction;
	int count;
	int out;
	int prev_val;
	int new_val; 	
	
public:
	QEI_Handler(PWM output);
	int getSpeed();
	void clearCount();
	int getDirection();
	void update();
};


#endif /* QEI_H_ */