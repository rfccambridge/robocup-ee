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


// *** Commutation sequences ***

const unsigned char forhall[8] =   {0x00,
									0x03,
									0x06,
									0x02,
									0x05,
									0x01,
									0x04,
									0x00};
const unsigned char backhall[8] =  {0x00,
									0x05,
									0x03,
									0x01,
									0x06,
									0x04,
									0x02,
									0x00};
void commutateMotor();
void breakMotor();
void txHex(unsigned char hex);
void interrupt_high_vector();
void high_ISR();

unsigned char hallCount;
unsigned char direction;

void main(){
	unsigned char i=0;
	unsigned char dutyCycle;
	unsigned char dutyHigh;
	unsigned char dutyLow;
	unsigned char oldHall;
	unsigned char newHall;
	unsigned char temp;

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
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;

	// *** Initialize serial ***
	// 57.6k at 8MHz
	BAUDCTL = 0b00001000;
	SPBRGH = 0;
	SPBRG = 34;
	TXSTA = 0b00100100;
	RCSTA = 0b10010000;

	// initialize timer0
	T0CON = 0b11000110;
	INTCON = 0b11100000;


	// *** Initialize PWM ***
	PTCON0 = 0x00;
	PTCON1 = 0x80;						// PTMR enabled, counts up
	PWMCON0 = 0b01001111;				// PWM0-5 enabled, independent mode. 
	PWMCON1 = 0x00;
	PTPERH = 0x00;						// 10 bit duty cycle, 7.7KHz @ 8MHz
	PTPERL = 0xff;
	
	// *** Initialize ADC ***
	ADCON0 = 0b00000000;				// single mode, single channel, sequential
	ADCON1 = 0b00000000;				// int ref, no FIFO
	ADCON2 = 0b10001010;				// right justified, 2 TAD delay, FOSC/32  -> Tacq on the order of 10 uS.
	ADCON3 = 0b00000000;				// all triggers disabled.	
	ADCHS = 0x00;
	ADCON0bits.ADON = 1;				// ADC on

	// *** Initialize encoder ***
	QEICON = 0b00001000;

	// *** Main Loop ***
	do{
		i++;

		// led 1 = direction
		LED1 = direction;
		if (i < 20)
			LED1 = 0;
/*
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
*/
		// break for low speeds, commutate for high speeds
		//if (dutyHigh==0x03 && dutyLow>0xA0)
//			breakMotor();
		//else
			commutateMotor();

		LED3 = QEICONbits.UP_DOWN;

/*

		// read ADC
		if (ADCON0bits.GO == 0) {
			dutyHigh = 0x03-ADRESH;
			dutyLow = 0xff-ADRESL;
			// create a deadband on the high side
			if (dutyHigh==0x00 && dutyLow<0x60) dutyLow = 0x00;
			// assign duty cycle registers
			PDC0H = dutyHigh;
			PDC0L = dutyLow;
			PDC1H = dutyHigh;
			PDC1L = dutyLow;
			PDC2H = dutyHigh;
			PDC2L = dutyLow;
			dutyCycle = dutyHigh<<6;
			ADCON0bits.GO = 1;
		}
*/

	} while(1);
}


// OVCOND = mask
// OVCONS = value when masked

void commutateMotor()
{
	const unsigned char backdrive[8] = { 0b00000000, 	// 0 error
										0b00100001, 	// 4
										0b00001010, 	// 2										
										0b00100010, 	// 6
										0b00010100, 	// 1
										0b00010001, 	// 5
										0b00001100, 	// 3
										0b00000000}; 	// 7 error
	const unsigned char fordrive[8] = {0b00000000, 	// 0 error
										0b00001010,		// 4
										0b00010100,		// 2
										0b00001100,		// 6
										0b00100001,		// 1
										0b00100010,		// 5
										0b00010001,		// 3
										0b00000000};	// 7 error
	// read the hall sensors
	unsigned char hall = HALL;

	// to prevent glitching
	unsigned char _OVDCOND;
	unsigned char _OVDCONS;

	if (!direction) {
		// PWM high side
		_OVDCOND = fordrive[hall] & 0b00111000;
		// turn on low side
		_OVDCONS = ~(fordrive[hall] & 0b00000111);
	} else {
		_OVDCOND = backdrive[hall] & 0b00111000;
		_OVDCONS = ~(backdrive[hall] & 0b00000111);
	}

	OVDCOND = _OVDCOND;
	OVDCONS = _OVDCONS;
}

void breakMotor()
{
	// All PWMs masked
	OVDCOND = 0x00;
	// low side mosfets on, high side off
	OVDCONS = 0x38;
}

void txHex(unsigned char hex)
{
	while(!PIR1bits.TXIF);
	if ((hex>>4) < 10)
		TXREG = '0' + (hex >> 4);
	else
		TXREG = 'A' + (hex >> 4) - 10;
	Nop();
	Nop();
	while(!PIR1bits.TXIF);
	if ((hex & 0x0f) < 10)
		TXREG = '0' + (hex & 0x0f);
	else
		TXREG = 'A' + (hex & 0x0f) - 10;
	Nop();
	Nop();
	while(!PIR1bits.TXIF);
	TXREG = ' ';
}



#pragma code high_vector=0x08				//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm				//branching to the actual ISR
}
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR()
{
	unsigned int velocity;
	unsigned char velh, vell;
	unsigned char dutyHigh, dutyLow;

	if (INTCONbits.TMR0IF) {
		INTCONbits.TMR0IF = 0;

		// read and reset position accumulator
		velocity = POSCNTH;
		velocity = velocity << 8;
		velocity += POSCNTL;//16 bit "velocity"
		POSCNTH = 0x80;
		POSCNTL = 0x00;
		
		// change to sign-magnitude
		if (velocity > 0x8000) {
			velocity = velocity - 0x8000;
			direction = 1;
		} else {
			velocity = 0x8000 - velocity;
			direction = 0;
		}

		vell = velocity;
		velh = velocity >> 8;

		// transmit speed
		if (direction)
			TXREG = '+';
		else
			TXREG = '-';
		Nop();
		Nop();
		while(!PIR1bits.TXIF);		
		txHex(velh);
		txHex(vell);

		velocity = velocity * 25;
		vell = velocity;
		velh = velocity >> 8;
		if (velh > 0x03) velh = 0x03;
		

		//Sett
		dutyHigh = 0x03 - velh;
		dutyLow = 0xff - vell;

		while(!PIR1bits.TXIF);
		TXREG = 13;
		Nop();
		Nop();
		if (direction)
			TXREG = '+';
		else
			TXREG = '-';
		Nop();
		Nop();
		while(!PIR1bits.TXIF);		
		txHex(dutyHigh);
		txHex(dutyLow);
		while(!PIR1bits.TXIF);
		TXREG = 13;
		Nop();
		Nop();
		while(!PIR1bits.TXIF);
		TXREG = 10;

		
//Setting outputs
		PDC0H = dutyHigh;
		PDC0L = dutyLow;
		PDC1H = dutyHigh;
		PDC1L = dutyLow;
		PDC2H = dutyHigh;
		PDC2L = dutyLow;


		LED2 = !LED2;
	}
}
#pragma

