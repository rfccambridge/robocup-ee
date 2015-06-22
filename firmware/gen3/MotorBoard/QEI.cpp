#include "QEI.h"
#include <avr/io.h>

QEI_Handler::QEI_Handler(PWM output){
		wheel = output;
		count = 0;
		prev_val = 0;
		new_val = 0;
		direction = 0;
		speed = 0;
		out = 0;
}

double QEI_Handler::update(double dt)
{
	// read in the two bits corresponding to the quad encoder for the wheel
	new_val = ((PIND & (0b11 << (2 * wheel))) >> (2 * wheel));
	
	// if you think of the lookup table as a 4x4 matrix,
	// then the row is the previous value and the column is the new value
	// (this math is equivalent to that)
	out = LOOKUP_TABLE[4 * prev_val + new_val];
	
	if (out != 2) {
		direction = out;
		count += out;
		prev_val = new_val;
		
		// TODO: how to update the speed...
	} else {
		// ignore the illegal case for now (probably just noise)
	}
	
	return speed;
}

double QEI_Handler::getSpeed() {
	return speed;
}