#include <p18f4431.h>
#include <string.h>
#include "bemixnet.h"

// *** set configuration word ***
#pragma	config OSC      = IRCIO		// internal oscillator
#pragma	config LVP 	    = OFF		// low voltage programming
#pragma	config WDTEN    = OFF   	// watchdog timer
#pragma	config WDPS     = 256   	// watchdog timer prescaler
#pragma config BOREN    = ON    	// brown out reset on
#pragma config BORV     = 42    	// brown out voltage 4.2
#pragma config FCMEN    = ON  		// fail-safe clock monitor off
#pragma config IESO     = ON    	// int/ext switchover off
#pragma config PWRTEN   = OFF		// powerup timer off
#pragma	config T1OSCMX  = OFF    	// timer1 osc mux
#pragma	config HPOL	    = HIGH		// high side transsitor polarity
#pragma	config LPOL	    = HIGH		// low side transistor polarity
#pragma	config PWMPIN   = OFF    	// PWM output pins Reset state control
#pragma	config MCLRE    = OFF       // MCLR enable
#pragma	config EXCLKMX  = RC3    	// External clock MUX bit
#pragma	config PWM4MX   = RB5		// PWM MUX
#pragma	config SSPMX    = RC7
#pragma	config FLTAMX   = RC1
#pragma	config STVREN   = ON		// stack overflow reset
#pragma config DEBUG    = OFF		// backgroud degugger
#pragma	config CP0      = OFF		// code protection
#pragma	config CP1      = OFF		// code protection
#pragma	config CP2      = OFF		// code protection
#pragma	config CP3	    = OFF		// code protection
#pragma	config CPB      = OFF		// boot protection
#pragma	config CPD      = OFF		// eeprom protection
#pragma	config WRT0     = OFF		// write protection
#pragma	config WRT1     = OFF		// write protection
#pragma	config WRT2     = OFF		// write protection
#pragma	config WRT3     = OFF		// write protection
#pragma	config WRTB     = OFF		// write protection
#pragma	config WRTC     = OFF		// write protection
#pragma	config WRTD     = OFF		// write protection
#pragma	config EBTR0    = OFF		// table protection
#pragma	config EBTR1    = OFF		// table protection
#pragma	config EBTR2    = OFF		// table protection
#pragma	config EBTR3    = OFF		// table protection

// *** pin definitions ***
#define LED1			LATEbits.LATE2		// Power
#define LED2			LATEbits.LATE1		// Rx
#define LED3			LATEbits.LATE0		// Hall error
#define LED4			LATAbits.LATA5		// Mosfet driver error

#define min(a,b)        (a<b) ? a : b
#define HALL            (PORTC & 0x07)

#define SPEW_ENCODER      1
#define DONT_SPEW_ENCODER 0

// initial value of timer0
// increase for shorter period
#define TIMER0INIT        32

PacketBuffer RxPacket;
PacketBuffer TxPacket;

unsigned char encoderCount;
unsigned char encoderFlags;

signed int Pconst, Iconst, Dconst;
signed int previous_error = 0;
signed int Iterm = 0;
signed char command = 0;
unsigned char direction = 0;

void commutateMotor();
void high_ISR();	 //Interrupt Service Routine
void handleQEI(PacketBuffer * TxPacket);

void main()
{
	unsigned char timer, timer2;
	
	TRISE = 0xf8;

	// *** 8 MHz clock ***
	OSCCON = 0b01110000;

	// *** Initialize PWM ***
	PTCON0 = 0x00;
	PTCON1 = 0x80;						// PTMR enabled, counts up
	PWMCON0 = 0b01001111;				// PWM0-5 enabled, independent mode. 
	PWMCON1 = 0x00;
	PTPERH = 0x00;						// 10 bit duty cycle, 7.7KHz @ 8MHz
	PTPERL = 0xff;
	
	// *** Configure IO ***
	ANSEL0 = 0x00;//ANSEL0 = 0x01;						// AN0 analog, all others digital
	ANSEL1 = 0x00;
	TRISA = 0xdf;
	TRISB = 0xff;
	TRISC = 0xff;
	TRISD = 0xff; 
	TRISE = 0x00;

	// *** initialize timer0 ***
	// 8 bit mode
	// prescaler   period
	// 110         16.4ms
	// 101          8.2ms
	// 100          4.1ms

	T0CON = 0b11000101;
	INTCON = 0b11100000;

	// *** Initialize encoder ***
	QEICON = 0b00011000;

	// *** Blink LEDs ***
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	for (timer2=0; timer2<16; timer2++)
		for (timer=0; timer<255; timer++);
	LED1 = 0;
	LED2 = 0;
	LED3 = 0;
	for (timer2=0; timer2<16; timer2++)
		for (timer=0; timer<255; timer++);
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;

	// *** Configure serial ***
	// (this needs to be last)
	initRx(&RxPacket);
	initTx(&TxPacket);

	encoderFlags = DONT_SPEW_ENCODER;
	encoderCount = 0;

	// defaults for testing
	Pconst = 12;
	Dconst = 3;
	Iconst = 3;
	command = 0;
	Iterm = 0;
	previous_error = 0;

	INTCONbits.TMR0IE = 1;

	while(1) {
		// Check for mosfet driver fault
		if (!PORTDbits.RD7) {
			LED4 = 0;
			OVDCOND = 0x00;
			OVDCONS = 0xff;
		} else {
			LED4 = 1;
			commutateMotor();
		}

		// Check for dead hall
		LED3 = 1;
		if (HALL == 0 || HALL == 7)
			LED3 = 0;

		if (encoderFlags==SPEW_ENCODER && encoderCount == MAX_PACKET_SIZE) {
			TxPacket.length = MAX_PACKET_SIZE;
			transmit(&TxPacket);
			encoderCount = 0;
		}
		
		if (RxPacket.done) {
			ClrWdt();
			RxPacket.done = 0;
			switch(RxPacket.port) {
				case 'r':
					Reset();
				case 'w':
					// update wheel speed			
					command = RxPacket.data[PORTAbits.AN0 + 2*PORTAbits.AN1];//RxPacket.data[0];							
					break;
				case 'f':
					Pconst = (signed int) RxPacket.data[0];
					Iconst = (signed int) RxPacket.data[1];
					Dconst = (signed int) RxPacket.data[2];
					break;
				case 'e':
					if (RxPacket.data[0]=='1')
						encoderFlags = SPEW_ENCODER;
					else
						encoderFlags = DONT_SPEW_ENCODER;
				default:
					break;	
			}
		}		
	} //closing while(1)
} //closing main()

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

	if (direction==0) {
		// PWM high side
		_OVDCOND = fordrive[hall] & 0b00111000;
		// turn on low side
		_OVDCONS = ~(fordrive[hall] & 0b00000111);
	} else if (direction == 1){
		_OVDCOND = backdrive[hall] & 0b00111000;
		_OVDCONS = ~(backdrive[hall] & 0b00000111);
	}

	OVDCOND = _OVDCOND;
	OVDCONS = _OVDCONS;
}



void handleQEI(PacketBuffer * encoderPacket)
{
	unsigned int encoderCentered = 0;
	signed char encoder = 0;
	signed int error = 0;
	signed int duty = 0;
	unsigned char dutyHigh, dutyLow;
	signed int Dterm;

	// transmit
	if (encoderFlags==SPEW_ENCODER && encoderCount < MAX_PACKET_SIZE) {
		encoderPacket->data[encoderCount++] = POSCNTH;
		encoderPacket->data[encoderCount++] = POSCNTL;
		encoderPacket->address = '2';
		encoderPacket->port = 'a';
	}

	// read and reset position accumulator
	encoderCentered = POSCNTH;
	encoderCentered = encoderCentered << 8;
	encoderCentered += POSCNTL;
	POSCNTH = 0x80;
	POSCNTL = 0x00;

	TMR0L = TIMER0INIT;

	// convert encoder value to 8 bit 2's comp
	//if (encoderCentered >= 0x8800) encoderCentered = 0x8800-1;
	//if (encoderCentered <= 0x7800) encoderCentered = 0x7800+1;

    if (encoderCentered >= 0x8400) encoderCentered = 0x8400-1;
	if (encoderCentered <= 0x7c00) encoderCentered = 0x7c00+1;
		
    if (encoderCentered >=0x8000)
		encoder = (encoderCentered - 0x8000)/ 4;
	else
		encoder = -(signed char)((0x8000-encoderCentered)/ 4);

	// calculate error, check for rollover
	error = ((signed int) encoder) - ((signed int) command);

	duty = error * Pconst / 3;
	Dterm = Dconst * (error - previous_error) / 3;
	Iterm += Iconst * error / 3;

	//check things are small
	if (duty > 900){
		duty = 900;
	} else if (duty < -900){
		duty = -900;
	}

	if (Dterm > 900){
		Dterm = 900;
	} else if (Dterm < -900){
		Dterm = -900;
	}

	if (command == 0 && encoder == 0)
		Iterm = 0;
	if (Iterm > 500){
		Iterm = 500;
	} else if (Iterm < -500){
		Iterm = -500;
	}

	duty += Dterm + Iterm + command;
	
	if(duty > 1023) duty = 1023;
	if(duty < -1023) duty = -1023;
	
	if (encoderFlags==SPEW_ENCODER && encoderCount < MAX_PACKET_SIZE) {
		encoderPacket->data[encoderCount++] = error>>8;
		encoderPacket->data[encoderCount++] = error;
		encoderPacket->data[encoderCount++] = duty>>8;
		encoderPacket->data[encoderCount++] = duty;
	}

	// convert to 10 bit sign magnitude
	if (duty >= 0) {
		direction = 1;
	} else {
		duty = -duty;
		direction = 0;
	}

	// hacked, weird around 0, don't change
	if (duty >= 1020)
		duty=1020;
	duty = 1020 - duty;

	dutyHigh = duty >> 8;
	dutyLow = duty;
	
	// set duty cycle
	PDC0H = dutyHigh;
	PDC0L = dutyLow;
	PDC1H = dutyHigh;
	PDC1L = dutyLow;
	PDC2H = dutyHigh;
	PDC2L = dutyLow;
	
	if (encoderFlags==SPEW_ENCODER && encoderCount < MAX_PACKET_SIZE) {
		encoderPacket->data[encoderCount++] = 0;
		encoderPacket->data[encoderCount++] = command;
		//encoderPacket->data[encoderCount++] = Dterm >> 8;
		//encoderPacket->data[encoderCount++] = Dterm;
		encoderPacket->data[encoderCount++] = encoder;
	}

	previous_error = error;
}

#pragma code high_vector=0x08				//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm				//branching to the actual ISR
}
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR()
{
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
		LED1 = 0;
		INTCONbits.TMR0IF = 0;
		handleQEI(&TxPacket);
		LED1 = 1;
	} else if (PIE1bits.RCIE && PIR1bits.RCIF) {
		LED2 = 0;
		PIR1bits.RCIF = 0;
		handleRx(&RxPacket);
		LED2 = 1;
	} else if (PIE1bits.TXIE && PIR1bits.TXIF) {
		PIR1bits.TXIF = 0;
		handleTx(&TxPacket);
	} 
}
#pragma


