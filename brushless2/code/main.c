#include <p18f4431.h>

/* ===== pin out =====
 * 01 - MCLR
 * 02 - AN0 = speed
 * 03 - AN1 = high side temp
 * 04 - INDX = N/C
 * 05 - QEA = encoder A
 * 06 - QEB = encoder B
 * 07 - AN5 = low side temp
 * 08 - AN6 = P
 * 09 - AN7 = I
 * 10 - AN8 = D
 * 11 - Vdd = +5
 * 12 - Vss = gnd
 * 13 - OSC1 = 40 MHz crystal
 * 14 - OSC2 = 40 MHz crystal
 * 15 - RC0 = hall 1
 * 16 - RC1 = hall 2
 * 17 - RC2 = hall 3
 * 18 - INT0 = hall 1+2+3
 * 19 - RD0 = direction
 * 20 - RD1 = break
 * 21 - RD2
 * 22 - RD3
 * 23 - RC4
 * 24 - RC5
 * 25 - RC6
 * 26 - RC7
 * 27 - RD4
 * 28 - RD5
 * 29 - RD6
 * 30 - RD7
 * 31 - Vss = gnd
 * 32 - Vdd = +5
 * 33 - PWM0
 * 34 - PWM1
 * 35 - PWM2
 * 36 - PWM3
 * 37 - PWM5
 * 38 - PWM4
 * 39 - RB6/PGC
 * 40 - RB7/PGD
*/

void main()
{
	const unsigned char forward[8] = {	0b00000000, 	// 0 - error
										0b00100001,		// 1
										0b00001010,		// 2
										0b00100010,		// 3
										0b00010100,		// 4
										0b00010001,		// 5
										0b00001100,		// 6
										0b00000000};	// 7 - error

	const unsigned char hold[8] = {		0b00000000,		// 0 - error
										0b00100010,		// 1
										0b00001100,		// 2
										0b00001010,		// 3
										0b00010001,		// 4
										0b00100001,		// 5
										0b00010100,		// 6
										0b00000000};	// 7 - error

	const unsigned char reverse[8] = {	0b00000000,		// 0 - error
										0b00001010,		// 1
										0b00010100,		// 2
										0b00001100,		// 3
										0b00100001,		// 4
										0b00100010,		// 5
										0b00010001,		// 6
										0b00000000};	// 7 - error

	// === set up GPIO ===
	TRISD = 0x00;
	TRISB = 0xff;
	TRISC = 0xff;

	// === initalize ADC ===
	ADCON0bits.ACONV = 1; //continuous mode
	ADCON0bits.ACSCH = 0; //single-channel mode
	ADCON0bits.ACMOD1 = 0;
	ADCON0bits.ACMOD0 = 0; //using group A

	ADCON1bits.VCFG1 = 0;
	ADCON1bits.VCFG0 = 0;
	ADCON1bits.FIFOEN = 0; // don't need multiple level addressin

	ADCON2=0b00000000;
	ADCON3=0b11100000;
	ADCHS = 0b00000000;
	ANSEL0 = 0b00000001; // set all pins to analog
	ADCON0bits.ADON = 1; // turn on adc

	// === initialize QEI === 
	QEICON = 0b00011000;
	CAP1CONbits.CAP1REN = 1;

	// === initialize PWM ===
	PWMCON0 = 0b01001111;		// PWM0-5 enabled, independent mode
	PTCON1 = 0x80;
	OVDCONS = 0x00;

	PDC0L = 0xff;
	PDC1L = 0xff;
	PDC2L = 0xff;
	PDC3L = 0xff;

	do {
		ADCON0bits.GO = 1;	// start the conversion loop
    	PDC0H = ADRESH;		// set the PWM duty cycle to AN0
    	PDC1H = ADRESH;
    	PDC2H = ADRESH;
    	PDC3H = ADRESH;

		// commutate motor
		OVDCOND = forward[PORTC & 0b00000111];

	//	PORTDbits.RD7 = QEICONbits.UP;
		PORTD = VELRH;
	} while(1);
}
