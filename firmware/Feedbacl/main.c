#include <p18f4431.h>
#include <string.h>
#include "bemixnet.h"

// *** set configuration word ***
#pragma	config OSC 		= IRCIO
#pragma	config WDTEN 	= OFF
#pragma	config LVP 		= OFF
#pragma	config WDPS 	= 256
#pragma config BOREN	= ON
#pragma config BORV		= 42

// *** pin definitions ***
#define LED1			LATEbits.LATE2		// Power
#define LED2			LATEbits.LATE1		// Rx
#define LED3			LATEbits.LATE0		// Hall error
#define LED4			LATAbits.LATA5		// Mosfet driver error

#define min(a,b) (a<b) ? a : b

#define HALL		(PORTC & 0x07)

#define SPEW_ENCODER 1
#define DONT_SPEW_ENCODER 0

PacketBuffer RxPacket;
PacketBuffer TxPacket;

unsigned char encoderCount;
unsigned char encoderFlags;

unsigned char Pconst, Iconst, Dconst;
signed char previous_error = 0;
signed int Iterm = 0;
signed char command = 0;
unsigned char direction = 0;

void commutateMotor();
void high_ISR();	 //Interrupt Service Routine
void handleQEI(PacketBuffer * TxPacket);

rom const char *rom stringTable[] = { "012345678901234657890123456789011111111",
									"RFC BLDC Driver Rev 0.13",
									"string 3",
									 "string 4"};
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
	Pconst = 25;
	Dconst = 1;
	Iconst = 4;
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
				case 'v':
					// transmit firmware version
					while(!TxPacket.done);
					strncpypgm2ram(&(TxPacket.data), stringTable[1], MAX_PACKET_SIZE);
					TxPacket.length = min(strlen(&(TxPacket.data)), MAX_PACKET_SIZE);
					transmit(&TxPacket);
					break;
				case 'w':
					// update wheel speed			
					command = RxPacket.data[PORTAbits.AN0 + 2*PORTAbits.AN1];//RxPacket.data[0];							
					break;
				case 'f':
					Pconst = RxPacket.data[0];
					Iconst = RxPacket.data[1];
					Dconst = RxPacket.data[2];
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
	signed char error = 0;
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

	// convert encoder value to 8 bit 2's comp
	//if (encoderCentered >= 0x8800) encoderCentered = 0x8800-1;
	//if (encoderCentered <= 0x7800) encoderCentered = 0x7800+1;

    if (encoderCentered >= 0x8400) encoderCentered = 0x8400-1;
	if (encoderCentered <= 0x7c00) encoderCentered = 0x7c00+1;
		

    if (encoderCentered >=0x8000)
		encoder = (encoderCentered - 0x8000)/ 4; //14;
	else
		encoder = -(signed char)((0x8000-encoderCentered)/ 4); //14);

	// calculate error, check for rollover
	error = encoder - command;

	//if ((((encoder>>7)&1)!=(command>>7)) && (((error>>7)&1)==((command>>7)&1))) {
	if ((command>0)!=(encoder>0) && (encoder>0)==(command>0)) {
		if (error > 0)
			error = -119;
		else
			error = 119;
	}
	//set P, I, and D to 100 and its tuned. However it doesn't seem to work well. Motors jitter etc.
	//duty = (signed int)error * (signed int)Pconst / ((signed int)4);
	//Dterm = (signed int)Dconst * ((signed int)error - (signed int)previous_error) / ((signed int)667);
	//Iterm += (signed int)Iconst * (signed int)error / ((signed int)28);

	duty = (signed int)error * (signed int)Pconst / 3;
	Dterm = (signed int)Dconst * ((signed int)error - (signed int)previous_error) / 3;
	Iterm += (signed int)Iconst * (signed int)error / 3;

	//check things are small
	if (duty > 900){
		duty = 900;
	} else if (duty < -900){
		duty = -900;
	}

	if (Dterm > 127){
		Dterm = 127;
	} else if (Dterm < -127){
		Dterm = -127;
	}

	if (command == 0 && encoder == 0)
		Iterm = 0;
	if (Iterm > 500){
		Iterm = 500;
	} else if (Iterm < -500){
		Iterm = -500;
	}

	duty += Dterm + Iterm;

	if (encoderFlags==SPEW_ENCODER && encoderCount < MAX_PACKET_SIZE) {
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


