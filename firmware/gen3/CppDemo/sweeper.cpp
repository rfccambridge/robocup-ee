/*
 * sweeper.cpp
 *
 * Created: 5/25/2015 11:11:45 AM
 *  Author: Erik
 */ 

#include <avr/io.h>
#include <util/delay.h>

class Sweeper {
	public:
	Sweeper() {
		// change direction of pins with DDRC
		DDRC = 0xFF;
		// initialize
		PORTC = 0x01;
	}
	
	void sweep(int ms) {
		for (int i = 0; i < 7; ++i) {
			_delay_ms(ms);
			PORTC = PORTC << 1;
		}
		for (int i = 0; i < 7; ++i) {
			_delay_ms(ms);
			PORTC = PORTC >> 1;
		}
	}
	
	
	};