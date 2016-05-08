/*
 * GccApplication2.cpp
 *
 * Created: 4/22/2016 21:29:10
 *  Author: Jon
 */ 

// Test LEDs on comms board - ports R and D

//TX = PD7
//RX = PD6
// use USARTD1

#define PD1 1
#define PD2 2
#define PR0 0
#define PR1 1
#define DEL_AMT 1000

#define F_CPU 32000000
//3200000UL
#define BAUD_R 9600

#include <avr/io.h>
#include <util/delay.h>
 
// control LED x either on (1) or off (0)
void led_ctrl(int num, bool mode) {
	switch(num) {
		case 0:
			if (mode)
				PORTD_OUT |= (1 << PD1);	
			else
				PORTD_OUT &= ~(1 << PD1);
			break;
		case 1:
			if (mode)
				PORTD_OUT |= (1 << PD2);
			else
				PORTD_OUT &= ~(1 << PD2);
			break;
		case 2:
			if (mode)
				PORTR_OUT |= (1 << PR0);
			else
				PORTR_OUT &= ~(1 << PR0);
			break;
		case 3:
			if (mode)
				PORTR_OUT |= (1 << PR1);
			else
				PORTR_OUT &= ~(1 << PR1);
			break;
		default:
			PORTD_OUT |= (1 << PD1)^(1 << PD2);
			PORTR_OUT |= (1 << PR0)^(1 << PR1);
			break;
	}
}

char recv_char() {
	while(!(USARTD1_STATUS & (1<<7))) {
			// Wait for data
	}
	return USARTD1_DATA;
}

void send_str(char *str) {
	while(*str) {
		while(!(USARTD1_STATUS & (1 << 5))) {
			// Wait for out register to clear
		}
		USARTD1_DATA = *str++;
	}
}

int main(void)
{
	// IMPORTANT CLOCK CONFIG
	OSC.CTRL |= 0b00000011;
	CLK.PSCTRL = 0b00000000;
	while(OSC.STATUS & (1 << 1) == 0) {
		
	}
	CCP = 0xD8;
	CLK.CTRL = 0b00000001;
	// CLOCK IS NOW 32MHz
	
	// OUTPUT PORT CONFIGS
	PORTD_OUT |= 1 << 7;
	PORTD_DIR |= 1 << 7;
	PORTD_DIR |= (1 << PD1)^(1 << PD2);
	PORTR_DIR |= (1 << PR0)^(1 << PR1);
	// SET UP USART (9600 baud with 32MHz cpu clock)
	// Use this: http://www.avrfreaks.net/forum/xmega-usart-baud-rate-calculator-tool
	// to calculate the baud ctrl values
	USARTD1_BAUDCTRLA = 0b11110101;
	USARTD1_BAUDCTRLB = 0b11001100;
	USARTD1_CTRLC = 0b00000011;
	USARTD1_CTRLB |= 0b00011000;
	// USART READY
	while(true) {
		volatile char c = recv_char();
		if(c == 't')
		{
			PORTD_OUT |= (1 << PD1);
			send_str("LED on");
		}
		else {
			PORTD_OUT &= ~(1 << PD1);
			send_str("LED off");
		}
	}
}