#include	<p18f4431.h>
#define		ENCODER_PPR 		d'1024' 		;PPR of Encoder on the motor
#define 	TIMER5_PRESCALE 	d'1' 			;Timer5 prescaler
#define 	QEI_X_UPDATE 		d'2' 			;Define the QEI mode of operation.
#define 	VELOCITY_PULSE_DECIMATION d'16'
INSTRUCTION_CYCLE = (OSCILLATOR)/d'4';
RPM_CONSTANT_QEI = ((INSTRUCTION_CYCLE)/(ENCODER_PPR*QEI_X_UPDATE*VELOCITY_PULSE_DECIMATION*TIMER5_PRESCALE)) * 60;
