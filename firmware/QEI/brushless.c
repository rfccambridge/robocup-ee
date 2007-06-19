#include	<p18f4431.h>

// *** set configuration word ***
#pragma config OSC = IRCIO
#pragma config WDTEN = OFF
#pragma config LVP = OFF

// *** pin definitions ***
#define LED1		LATEbits.LATE2
#define LED2		LATEbits.LATE1
#define LED3		LATEbits.LATE0
#define DIRECTION	PORTDbits.RD1
#define HALL		(PORTC & 0x07)


unsigned char commutate(unsigned char hall);

void main(){
	unsigned char i=0;
	unsigned char dutyCycle;

	// *** 8 MHz clock ***
	OSCCON = 0b01110000;

	// *** Configure IO ***
	ANSEL0 = 0x01;						// AN0 analog, all others digital
	ANSEL1 = 0x00;
	TRISA = 0xff;
	TRISB = 0xff;
	TRISC = 0xff;
	TRISD = 0xff;
	TRISE = 0x00;

	// *** Initialize PWM ***
	PTCON0 = 0x00;
	PTCON1 = 0x80;						// PTMR enabled, counts up
	PWMCON0 = 0b01001111;				// PWM0-5 enabled, independent mode. 
	PWMCON1 = 0x00;
	PTPERH = 0x00;						// 10 bit duty cycle, 7.7KHz @ 8MHz
	PTPERL = 0xff;
	OVDCONS = 0xff;						// outputs high when disabled
	
	// *** Initialize ADC ***
	ADCON0 = 0b00000000;				// single mode, single channel, sequential
	ADCON1 = 0b00000000;				// int ref, no FIFO
	ADCON2 = 0b10001010;				// right justified, 2 TAD delay, FOSC/32  -> Tacq on the order of 10 uS.
	ADCON3 = 0b00000000;				// all triggers disabled.	
	ADCHS = 0x00;
	ADCON0bits.ADON = 1;				// ADC on

	// *** Main Loop ***
	do{
		i++;

		// led 1 = direction
		LED1 = DIRECTION;
		if (i < 20)
			LED1 = 0;

		// led 2 = speed
		if (i > dutyCycle)
			LED2 = 0;
		else
			LED2 = 1;

		// led 3 = broken hall sensor
		if (HALL == 0x07 || HALL == 0x00)
			LED3 = 0;
		else
			LED3 = 1;

		// commutate motor
		OVDCOND = commutate(HALL);

		// read ADC
		if (ADCON0bits.GO == 0) {
			PDC0H = 0x03-ADRESH;
			PDC0L = 0xff-ADRESL;
			PDC1H = 0x03-ADRESH;
			PDC1L = 0xff-ADRESL;
			PDC2H = 0x03-ADRESH;
			PDC2L = 0xff-ADRESL;
			dutyCycle = PDC0H<<6;
			ADCON0bits.GO = 1;
		}
	} while(1);
}


unsigned char commutate(unsigned char hall)
{
	const unsigned char fordrive[8] = { 0b00000000, 	// 0 error
										0b00100001, 	// 4
										0b00001010, 	// 2										
										0b00100010, 	// 6										0b00001010, 	// 2
										0b00010100, 	// 1
										0b00010001, 	// 5
										0b00001100, 	// 3
										0b00000000}; 	// 7 error

	const unsigned char backdrive[8] = {0b00000000, 	// 0 error
										0b00001010,		// 4
										0b00010100,		// 2
										0b00001100,		// 6
										0b00100001,		// 1
										0b00100010,		// 5
										0b00010001,		// 3
										0b00000000};	// 7 error

	if (DIRECTION)
		return fordrive[hall];
	else
		return backdrive[hall];
}
