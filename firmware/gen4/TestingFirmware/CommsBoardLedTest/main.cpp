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

int main(void)
{
	OSC.CTRL |= 0b00000011;
	CLK.PSCTRL = 0b00000000;
	while(OSC.STATUS & (1 << 1) == 0) {
		
	}
	CCP = 0xD8;
	CLK.CTRL = 0b00000001;
	
	PORTD_OUT |= 1 << 7;
	PORTD_DIR |= 1 << 7;
	PORTD_DIR |= (1 << PD1)^(1 << PD2);
	PORTR_DIR |= (1 << PR0)^(1 << PR1);
	USARTD1_BAUDCTRLA = 0b11110101;
	USARTD1_BAUDCTRLB = 0b11001100;
	USARTD1_CTRLC = 0b00000011;
	USARTD1_CTRLB |= 0b00010000;
	while(true) {
		/*//volatile char val = 'f';
		while(!(USARTD1_STATUS & (1<<5))) {
			// Wait for data
		}
		USARTD1_DATA = 'h';*/
		volatile char val = 'f';
		while(!(USARTD1_STATUS & (1<<7))) {
			// Wait for data
		}
		val = USARTD1_DATA;
		if(val == 't')
		{
			PORTD_OUT |= (1 << PD1);
		}
		else {
			PORTD_OUT &= ~(1 << PD1);
		}
	}
	
	// Setup pins as outputs
 	PORTD_DIR |= (1 << PD1)^(1 << PD2);
 	PORTR_DIR |= (1 << PR0)^(1 << PR1);
	
	led_ctrl(1,false);
	led_ctrl(2,false);
	led_ctrl(3,false);
	led_ctrl(4,false);

	// Blink LEDs in sequence
    while(1)
    {
		led_ctrl(0,true);
		
		_delay_ms(DEL_AMT);
		
		led_ctrl(0,false);
		led_ctrl(1,true);
		
		_delay_ms(DEL_AMT);
		
		led_ctrl(1,false);
		led_ctrl(2,true);
		
		_delay_ms(DEL_AMT);
		
		led_ctrl(2,false);
		led_ctrl(3,true);
		
		_delay_ms(DEL_AMT);
		
		led_ctrl(3,false);
		
		_delay_ms(DEL_AMT);
		
		for (int i = 0; i < 4; i++)
			led_ctrl(i,true);
		
		_delay_ms(DEL_AMT);
		
		for (int i = 0; i < 4; i++)
			led_ctrl(i,false);
		
		_delay_ms(DEL_AMT);
		}
}