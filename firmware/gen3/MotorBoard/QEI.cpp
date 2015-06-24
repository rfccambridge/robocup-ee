#include "QEI.h"
#include <avr/io.h>

QEI_Handler::QEI_Handler(PWM output){
		wheel = output;
		count = 0;
		prev_val = 0;
		new_val = 0;
		direction = 0;
		out = 0;
}

void QEI_Handler::update()
{
	// read in the two bits corresponding to the quad encoder for the wheel
	new_val = ((PINE & (0b11 << (2 * wheel))) >> (2 * wheel));
	
	// if you think of the lookup table as a 4x4 matrix,
	// then the row is the previous value and the column is the new value
	// (this math is equivalent to that)
	out = LOOKUP_TABLE[4 * prev_val + new_val];
	
	if (out != 2) {
		direction = out;
		count += out;
		prev_val = new_val;
		
	} else {
		// ignore the illegal case for now (probably just noise)
	}
}

int QEI_Handler::getSpeed() {
	return count;
}

void QEI_Handler::clearCount() {
	count = 0;
}

int QEI_Handler::getDirection() {
	return direction;
}