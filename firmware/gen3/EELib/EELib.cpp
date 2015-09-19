#include "EELib.h"
#include <avr/io.h>
#include <math.h>
//#include <interrupt.h>

//pin_def::pin_def(volatile uint8_t* port_, uint8_t pin_) : port(port_), pin(pin_) {
//}

int abs(int num) {
	return (num > 0) ? (num) : (-num);
}

// from stack overflow
unsigned char reverse(unsigned char b) {
	b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
	b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
	b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
	return b;
}

// convenience function to set a single bit cleanly
void setBit(volatile uint8_t* port, uint8_t pin, bool val) {
	// Ezra, what witch magic is this?
	*port ^= (-val ^ *port) & (1 << pin);
}
void setBit(pin_def pin, bool val) {
	setBit(pin.port, pin.pin, val);
}

// convenience function to read a single bit cleanly
bool getBit(volatile uint8_t* port, uint8_t pin) {
	return ((*port & (1 << pin)) == (1 << pin));
}
bool getBit(pin_def pin) {
	return getBit(pin.port, pin.pin);
}

void enablePWM(PWM PWMnum)
{
	switch(PWMnum)
	{
		// Set timer to fast PWM mode, with no prescaling, clear on compare match,

		case OUTPUT1 :
			TCCR0A |= (1 << WGM00) | (1 << WGM01) | (1 << CS00) | (1 << COM0A1);
			// Enable B4 as an output
			DDRB |= (1 << PINB4);
			// Set duty cycle to 0
			OCR0A = 0;
			break;
		case OUTPUT2 :
			TCCR1A |= (1 << WGM10) | (1 << COM1A1);
			TCCR1B |= (1 << WGM12) | (1 << CS10);
			TCCR1C &= (0 << FOC1A) | (0 << FOC1B);
			// Enable B5 as an output
			DDRB |= (1 << PINB5);
			// Set duty cycle to 0
			OCR1A = 0;
			break;
		case OUTPUT3 :
			TCCR1A |= (1 << WGM10) | (1 << COM1B1);
			TCCR1B |= (1 << WGM12) | (1 << CS10);
			TCCR1C &= (0 << FOC1A) | (0 << FOC1B);
			// Enable B6 as an output
			DDRB |= (1 << PINB6);
			// Set duty cycle to 0
			OCR1B = 0;
			break;
		case OUTPUT4 :
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
		case OUTPUT1:
			OCR0A = scaledDuty;
			break;
		case OUTPUT2:
			OCR1A = scaledDuty;
			break;
		case OUTPUT3:
			OCR1B = scaledDuty;
			break;
		case OUTPUT4:
			OCR2A = scaledDuty;
			break;
	}
}

void setUpADC(void)
{
	// Set ADC prescale 128. If the system clock is @ 16 MHz,
	// This will results in the ADC sampling rate to 125KHz,
	// Which is within the recommended 50-200 KHz range
	// See page 206 of the data sheet for prescaler settings
	ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	
	// Use AVCC as the reference voltage
	// See page 201 of the data sheet for Voltage Reference settings table
	ADMUX |= (1 << REFS0);
	
	// Enable ADC
	ADCSRA |= (1 << ADEN);
}

double readADC(int pin)
{
	// Set the ADC multiplexer to read in the correct pin
	// (without disrupting the other bits on the register)
	// See page 202 of the data sheet for input channel selection table
	// TODO: Find a cleaner way to do this sort of thing (maybe write a library function)
	// First, clear the first 5 bits (the nMUX bits)
	ADMUX &= 0xE0;
	// Then set them
	ADMUX |= pin;
	
	// Start conversion
	ADCSRA |= (1 << ADSC);
	
	// In single conversion mode, the ADSC bit of the ADCSRA automatically
	// clears when the conversion is complete, so we can just wait
	// until the bit is zero
	while (ADCSRA & (1 << ADSC)) {}
		
	// The ADC register will contain an int between 0 and 1023
	// (Reference on ADCL and ADCH registers is on page 204)
	// which we want to scale to a voltage between 0 and the reference voltage
	return ((ADC / 1024.0) * REF_VOLTAGE);
}