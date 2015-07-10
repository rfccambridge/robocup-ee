#include <avr/io.h>
#include <util/delay.h>

void sweep(void);
void follow_switches(void);

int main (void)
{
	sweep();
}

// LEDs = dip switches
void follow_switches() {
	// input direction
	DDRA = 0x00;
	// tristate
	PORTA = 0x00;
	
	// output LEDs on port C
	DDRC = 0xFF;
	
	while(1) {
		PORTC = PINA;
	}
}

// sweep the LEDs back and forth
void sweep() {
	// change direction of pins with DDRC
	DDRC = 0xFF;
	
	PORTC = 0x01;
	// change levels with PORTx
	while(1) {
		for (int i = 0; i < 7; ++i) {
			_delay_ms(100);
			PORTC = PORTC << 1;
		}
		for (int i = 0; i < 7; ++i) {
			_delay_ms(100);
			PORTC = PORTC >> 1;
		}
	}
}