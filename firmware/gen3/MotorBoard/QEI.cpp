#include "QEI.h"

QEI_Handler::QEI_Handler(){
	// initialize everything to 0
	for (int i = 0; i < 4; i++) {
		counts[i] = 0;
		enc_val[i] = 0;
		directions[i] = 0;
	}
}

void QEI_Handler::handleQEI(Wheel wheel)
{
	enc_val[wheel] = enc_val[wheel] << 2;
	//enc_val[wheel] = enc_val[wheel] | ((PIND & (0b11 << wheel)) >> wheel);
		
	counts[wheel] = counts[wheel] + lookuptable[enc_val[wheel] & 0b1111];
}