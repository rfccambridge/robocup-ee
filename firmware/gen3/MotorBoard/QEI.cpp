#include "QEI.h"
#include <avr/io.h>

QEI_Handler::QEI_Handler(PWM output){
		wheel = output;
		count = 0;
		enc_val = 0;
		direction = 0;
		speed = 0;
		
		// TODO: set up interrupts 
}

// this will actually go inside of a special function, just putting it here for now
void QEI_Handler::update(void)
{
	// TODO: figure out what I was thinking here...
	enc_val = enc_val << 2;
	enc_val = enc_val | ((PIND & (0b11 << wheel)) >> wheel);
	count = count + lookuptable[enc_val & 0b1111];
}

double QEI_Handler::getSpeed() {
	return speed;
}