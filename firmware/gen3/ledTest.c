/* ledTest.c
 * Last modified 2/6/2015 by Ezra Zigmond
 * 
 * Test program to blink an LED connected to PD0 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

int main(void)
{
	// disable interrupts
	cli();
	// Set up division by 64 for clock (see page 116 of datesheet)
	TCCR1B |= 1 << CS11 | 1 << CS10;

	// Set number of cycles for interrupt (see page 104)
	OCR1A = 15624;

	// Set timer to CTC mode (page 115) with OCR1A as top
	TCCR1B |= 1 << WGM12;

	// Enable interrupt for output compare a match (page 118)
	TIMSK1 |= 1 << OCIE1A;

	// reenable interrupts
	sei();

	// Setup I/O pins (see page 56 for a discussion)
	// Set PortD Pin0 as output
	DDRD |= (1 << 0);

	// Set PortD Pin0 as high
	PORTD |= (1 << 0);

	// loop forever and blink
	while(1) {}
}

ISR(TIMER1_COMPA_vect)
{
	// Toggle PortD Pin0 using xor
	PORTD ^= (1 << 0); 
}