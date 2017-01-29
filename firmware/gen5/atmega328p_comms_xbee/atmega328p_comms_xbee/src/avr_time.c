#include "avr_time.h"
#include <avr/io.h>
#include <avr/interrupt.h>

#define CLOCKS_PER_MS F_CPU / 1000UL
// Timer is 8 bits and prescaled by 64
#define CLOCKS_PER_TIMER_OFLOW 64UL * 256UL
#define _BV(bit) (1 << (bit))

volatile static uint32_t timer0_ticks = 0;
volatile static uint32_t oflow_ms = 0;

ISR(TIMER0_OVF_vect) {
	// overflow worth of clock ticks
	timer0_ticks += CLOCKS_PER_TIMER_OFLOW;
	for (; timer0_ticks > CLOCKS_PER_MS; timer0_ticks -= CLOCKS_PER_MS) {
		oflow_ms++;
	}
}

// Initialize timer 0.
void avr_time_init(void) {
	// Prescale timer 0 by 64
	TCCR0B |= _BV(CS01) | _BV(CS00);
	// Enable overflow interrupt on timer 0
	TIMSK0 |= _BV(TOIE0);
}

// Return current time in ms.
uint32_t avr_time_now(void) {
	uint32_t now;
	
	// Disable interrupts when reading value
	cli();
	now = oflow_ms;
	sei();
	
	return now;
}