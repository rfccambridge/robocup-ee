#include "EELib.h"
#include <avr/io.h>
#include <math.h>

void setBit(volatile uint8_t* port, uint8_t pin, bool val)
{
	*port ^= (-val ^ *port) & (1 << pin);
}

void enablePWM(PWM PWMnum)
{
	switch(PWMnum)
	{
		// Set timer to fast PWM mode, with no prescaling, clear on compare match,

		case PWM1 :
			TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << CS00) | (1 << COM0A1);
			// Enable B4 as an output
			DDRB |= (1 << PINB4);
			// Set duty cycle to 0
			OCR0A = 0;
			break;
		case PWM2 :
			TCCR1A |= (1 << WGM10) | (1 << COM1A1);
			TCCR1B |= (1 << WGM12) | (1 << CS10);
			TCCR1C &= (0 << FOC1A) | (0 << FOC1B);
			// Enable B5 as an output
			DDRB |= (1 << PINB5);
			// Set duty cycle to 0
			OCR1A = 0;
			break;
		case PWM3 :
			TCCR1A |= (1 << WGM10) | (1 << COM1B1);
			TCCR1B |= (1 << WGM12) | (1 << CS10);
			TCCR1C &= (0 << FOC1A) | (0 << FOC1B);
			// Enable B6 as an output
			DDRB |= (1 << PINB6);
			// Set duty cycle to 0
			OCR1B = 0;
			break;
		case PWM4 :
			TCCR2A |= (1 << WGM20) | (1 << WGM21) | (1 << CS20) | (1 << COM2A1);
			// Enable B7 as an output
			DDRB |= (1 << PINB7);
			// Set duty cycle to 0
			OCR2A = 0;
			break;
	}
}

void setDutyCycle(PWM PWMnum, float dutyCycle)
{
	// Take the float between 0.0 and 1.0 and scales it to a number between 0 and 255
	float scaledDuty = round(255 * dutyCycle);
	
	switch(PWMnum)
	{
		case PWM1:
			OCR0A = scaledDuty;
			break;
		case PWM2:
			OCR1A = scaledDuty;
			break;
		case PWM3:
			OCR1B = scaledDuty;
			break;
		case PWM4:
			OCR2A = scaledDuty;
			break;
	}
}
