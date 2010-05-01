/* average-main.c
 *
 * This version of the wheels code keeps a running average of wheels speed.
 * When determining how to respond to a given command, it averages the 
 * given speed with the previous average. There is a special case that 
 * ensures that the speed always advances towards the target by at least 1.
 *
 * As always, 0 is a special case.
 *
 * As of 4/29/09, this version brongs back the halting problem -- the wheels
 * fail to stop properly. This is a deep-rooted problem that warrants 
 * further investigation.
 */

#include <p18f4431.h>
#include <string.h>
#include "bemixnet.h"

// *** set configuration word ***
#pragma	config OSC      = IRCIO		// internal oscillator
#pragma	config LVP 	    = OFF		// low voltage programming
#pragma	config WDTEN    = OFF	   	// watchdog timer
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
// currently set up to transmit five bytes of Data, so we want 6 of those groups 
// in a packets (maximum size is 32), so desired size is 30.

#define DESIRED_PACKET_SIZE 30



// this is the maximum error
#define MAX_ERROR 200


signed int Pconst, Iconst, Dconst;
signed int previous_error = 0;
signed int Iterm = 0;
signed char command = 0;
unsigned char direction = 0;


/* The following is a debugging tool: flag for feedback, 0 for off, 1 for on
 feedback should always be on - only turn off to see what robot does if it 
 thinks there is no error */
unsigned short feedback_on = 0;

// initial value of timer0
// increase for shorter period
#define TIMER0INIT        32

PacketBuffer RxPacket;
PacketBuffer TxPacket;

unsigned char encoderCount;
unsigned char encoderFlags;

unsigned int wheel;

void commutateMotor();
void high_ISR();	 //Interrupt Service Routine
void handleQEI(PacketBuffer * TxPacket);

/* hard-coded, hacky functions for translating between speed & duty cycle
   these are designed for testing dead reckoning for wheel speeds */


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
	ANSEL0 = 0x00;//ANSEL0 = 0x01;		// AN0 analog, all others digital
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

	T0CON = 0b11000101; //enabled, 8bit, internal clock, low->high transition, Use of prescaler, 1:64
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

	/* Figure out which wheel this is 
	 0 -- Front right
	 1 -- Front left
   	 2 -- Rear left
	 3 -- Rear right
	*/
	wheel = PORTAbits.AN0 + 2*PORTAbits.AN1;

	// *** Configure serial ***
	// (this needs to be last)
	initRx(&RxPacket);
	initTx(&TxPacket);

	encoderFlags = DONT_SPEW_ENCODER;
	encoderCount = 0;

	// defaults for testing
	Pconst = 50;
	Dconst = 3;
	Iconst = 1;
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
	//	LED3 = 1;
	//	if (HALL == 0 || HALL == 7)
	//		LED3 = 0;

		
		if (encoderFlags==SPEW_ENCODER && encoderCount == DESIRED_PACKET_SIZE) {

//test
			TxPacket.length = DESIRED_PACKET_SIZE;
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
					// Get the transmitted wheel speed			
					command = RxPacket.data[wheel];
					break;
				case 'f':
					Pconst = (signed int) RxPacket.data[0];
					Iconst = (signed int) RxPacket.data[1];
					Dconst = (signed int) RxPacket.data[2];
					break;
				case 'e':
					if (RxPacket.data[0]==wheel){
						encoderFlags = SPEW_ENCODER;
					}
					else
						encoderFlags = DONT_SPEW_ENCODER;
					break;
				case 's': // temporary value - make this work
					// TODO: estimate wheel speed
					break;
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
										 0b00010001,	//these are new commutation order, didn't fix direction biase problem :(
										 0b00100010,
										 0b00100001,
										 0b00001100,
										 0b00010100,
										 0b00001010,
									 	 0b00000000}; 	// 7 error



										/*0b00100001, 	// 4
										0b00001010, 	// 2		
										0b00100010, 	// 6
										0b00010100, 	// 1
										0b00010001, 	// 5
										0b00001100, 	// 3
										0b00000000}; 	// 7 error*/
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
	if (command == 0 && feedback_on == 0){ // if command is zero we want to coast! (Not for use with feedback)
		_OVDCOND = fordrive[0];
		_OVDCONS = ~fordrive[0];
	} else 
	if (direction==0) {
		// PWM high side
	//	LED4 = 0;
		_OVDCOND = fordrive[hall] & 0b00111000;
		// turn on low side
		_OVDCONS = ~(fordrive[hall] & 0b00000111);
	} else if (direction == 1){
		_OVDCOND = backdrive[hall] & 0b00111000;
		_OVDCONS = ~(backdrive[hall] & 0b00000111);
	//	LED4 = 1;
	}

	OVDCOND = _OVDCOND;
	OVDCONS = _OVDCONS;
}



void handleQEI(PacketBuffer * encoderPacket)
{
	unsigned int encoderCentered = 0;
	signed int encoder = 0;
	signed int error = 0;
	signed int duty = 0;			// modifies speed based on PID feedback
	unsigned char dutyHigh, dutyLow;// high and low bits for duty cycle
	signed int Dterm;

	signed char encHigh;
	signed char encLow;

	// read and reset position accumulator
	encoderCentered = POSCNTH;
	encoderCentered = encoderCentered << 8;
	encoderCentered += POSCNTL;
	POSCNTH = 0x80;
	POSCNTL = 0x00;

	//  Set duty to estimated value
	//	duty = rotationsToDuty(speedToRotations(command));
	
	TMR0L = TIMER0INIT;
		
    if (encoderCentered >=0x8000)
		encoder = (signed int)(encoderCentered - 0x8000);
	else									
		encoder = -(signed int)(0x8000-encoderCentered);

	encoder = - encoder; //Because + direction conventions are switched between the encoder and the commutation.
	
	//find size of encoder
/*	if (encoder < 0x75 && -encoder < 0x75){
		LED3 = 0;
		LED4 = 0;
	} else if (encoder < 0x100 && -encoder < 0x100){
		LED3 = 1;
		LED4 = 0;
	} else if (encoder < 0x103 && -encoder < 0x103){
		LED3 = 0;
		LED4 = 1;
	} else if (encoder < 0x200 && -encoder < 0x200){
		LED3 = 1;
		LED4 = 1;
	}*///It appears the max of encoder is about 0x100 or 2^8, when the wheel is full speed and and the robot is in the air.
//max about 120 with divide by 4, with duty = 127*8 its about 486 without naturally

////////////////////


//Top of comment out usually here

	// calculate error, check for rollover 
	error = ((signed int) command) - ((signed int) encoder)/4; 

	// if feedback is off, set error to 0; otherwise, keep it the same
	error *= feedback_on;

	// cap error to prevent a single wheel from drawing too much current
	if(error > MAX_ERROR) error = MAX_ERROR;
	if(error < -MAX_ERROR) error = -MAX_ERROR;


// only the below three commented out still get just 4 spikes in a period while In synch.
//everything else commented out, out of synch at 4 spikes and about 3 other places

//only two spikes in three periods instead of 4 in a period, but out of synch
	duty = error * Pconst / 3;
	Dterm = Dconst * (error - previous_error) / 3;
	Iterm += Iconst * error / 3;
//	Iterm = Iterm/3;
//	Iterm = Iterm/7;// adding these in made it go out of synch with only the three above lines running.
//		Dterm = Dterm/11;

//four spikes per period 50, 54, 48 between the two around a max/min. In Synch

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

//commented out to here out of syncyh for spikes onlythat are 50 or 54 mostly 54.

	if (command == 0 && encoder == 0)
		Iterm = 0;
	if (Iterm > 500){
		Iterm = 500;
	} else if (Iterm < -500){
		Iterm = -500;
	}


	//Negate the feedback calc if necessary
	if (feedback_on == 0){
		duty = command;
		duty = duty*8;
	}
	else{
		//P +   D  +   I  + feed forward term
		 duty += Dterm + Iterm + 8*command;
		//if (duty < 0) duty= duty-80;
		//else if (duty > 0) duty= duty + 80; 
	}
//commented out to here, periodic down to up 50 or 54

	if(duty > 1023) duty = 1023;
	if(duty < -1023) duty = -1023;	

	// convert to 10 bit sign magnitude
	if (duty >= 0) {
		direction = 1;
	} else {
		duty = -duty;
		direction = 0;
	}

	duty = 1023 - duty;

	dutyHigh = duty >> 8;
	dutyLow = duty;
	
	// set duty cycle
	PDC0H = dutyHigh;
	PDC0L = dutyLow;
	PDC1H = dutyHigh;
	PDC1L = dutyLow;
	PDC2H = dutyHigh;
	PDC2L = dutyLow;
	
	
	// put data in transmit buffer
	if (encoderFlags==SPEW_ENCODER && encoderCount < DESIRED_PACKET_SIZE) {
		//CONVERT duty back to big number is faster
		duty = 1023 - duty;
		dutyHigh = duty >> 8;
		dutyLow = duty;

		encHigh = encoder >> 8;
		encLow = encoder;

		encoderPacket->address = '2';
		encoderPacket->destination = '2';
		encoderPacket->port = 'a';

//temp-----------------------------------------------
	//		duty = 0;
//	duty= command;
//	duty = duty*8;
//dutyHigh = duty >> 8;
//		dutyLow = duty;

//temp-----------------------------------------------

		encoderPacket->data[encoderCount++] = encHigh;
		encoderPacket->data[encoderCount++] = encLow;
		encoderPacket->data[encoderCount++] = dutyHigh;//duty high
		encoderPacket->data[encoderCount++] = dutyLow; //duty low
		encoderPacket->data[encoderCount++] = command;

	}
	 else {	LED4= !LED4;}

	previous_error = error;
}

#pragma code high_vector=0x08 	// We are not using Priortized Interrupts: 
								// so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm	//branching to the actual ISR
}
#pragma code

#pragma interrupt high_ISR		// Interrupt Service Routine (the real one)
void high_ISR()
{
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
		LED1 = 0;
		INTCONbits.TMR0IF = 0;
		handleQEI(&TxPacket);
		LED1 = 1;
	}if (PIE1bits.RCIE && PIR1bits.RCIF) {
		LED2 = 0;
		PIR1bits.RCIF = 0;
		handleRx(&RxPacket);
		LED2 = 1;
	}if (PIE1bits.TXIE && PIR1bits.TXIF) {
		PIR1bits.TXIF = 0;
		handleTx(&TxPacket);
	} 
}
#pragma


