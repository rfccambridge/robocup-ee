/*
 * QEI.h
 *
 * Created: 6/15/2015 5:50:23 PM
 *  Author: Ezra
 */ 


#ifndef QEI_H_
#define QEI_H_

const int lookuptable[16] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};

class QEI_Handler 
{
private:
	int directions[4];
	int counts[4];
	int enc_val[4];	
	
public:
	enum Wheel {
		WHEEL_LB,
		WHEEL_RB,
		WHEEL_LF,
		WHEEL_RF
	};
	QEI_Handler();
	void handleQEI(Wheel wheel);
};


#endif /* QEI_H_ */