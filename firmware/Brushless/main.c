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

// initial value of timer0, increase for shorter period
#define TIMER0INIT      32

// this is the maximum error
#define MAX_ERROR 200

#define min(a,b)        (((a) < (b)) ? (a) : (b))
#define HALL            (PORTC & 0x07)

// Configuration flags
#define CFG_SPEW_ENCODER      0b00000001
#define CFG_SPEW_PKT_STATS    0b00000010
#define CFG_FEEDBACK          0b00000100

// Each tx pkt is made up of several sub-packets to minimize transmission overhead 
// NOTE: total packet size must not exceed MAX_PACKET_SIZE defined in bemixnet.h
// TODO: doesn't work with more than one sub-packet!!!
#define NUM_TX_SUBPKTS 1

unsigned char cfgFlags = 0;

PacketBuffer RxPacket;
PacketBuffer TxPacket;

unsigned char subPkt = 0; // iterator over the sub-packets
unsigned int wheel;   // board id

signed int Pconst, Iconst, Dconst;
signed int previous_error = 0;
signed int Iterm = 0;
signed char command = 0;
unsigned char direction = 0;

// Ben's minor loop velocity controller
signed long int m = 0;
signed long int m_n1 = 0; //from from the last iteration
signed long int e2 = 0;
signed long int e2_n1 = 0; //e2 from the last iteration

static void blinkLEDs(void);
static void commutateMotor(void);
//Interrupt Service Routines
void high_ISR(void);
void handleQEI(PacketBuffer * TxPacket);

void Fixposition(){
	unsigned char hall = HALL;
	unsigned char _OVDCOND;
	unsigned char _OVDCONS;
	
	_OVDCOND = 0b00100001;
	_OVDCONS = ~0b00100001;
	OVDCOND = _OVDCOND;
	OVDCONS = _OVDCONS;

	if(hall==0){
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
	}
	else if(hall==1){
		LED1 = 0;
		LED2 = 1;
		LED3 = 1;;
	}
	else if(hall==2){
		LED1 = 1;
		LED2 = 0;
		LED3 = 1;
	}
	else if(hall==3){
		LED1 = 0;
		LED2 = 0;
		LED3 = 1;
	}
	else if(hall==4){
		LED1 = 1;
		LED2 = 1;
		LED3 = 0;;
	}
	else if(hall==5){
		LED1 = 0;
		LED2 = 1;
		LED3 = 0;
	}
	else if(hall==6){
		LED1 = 1;
		LED2 = 0;
		LED3 = 0;
	}
	else if(hall==7){
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
	}
}


void main()
{
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

	cfgFlags = CFG_FEEDBACK; // | CFG_SPEW_ENCODER;

	blinkLEDs();

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
	subPkt = 0;

	// defaults for testing
	Pconst = 50;
	Dconst = 3;
	Iconst = 1;
	command = 0;
	Iterm = 0;
	previous_error = 0;

	INTCONbits.TMR0IE = 1;
	LED1 =0;
	while(1) {
	//	command = -0x08;
		// Check for mosfet driver fault
		if (!PORTDbits.RD7) {
			LED4 = 0;
			OVDCOND = 0x00;
			OVDCONS = 0xff;
			//commutateMotor();
		} else {
			LED4 = 1;
			commutateMotor();
		}
		//Fixposition();

		// Check for dead hall
		LED3 = 1;
		if (HALL == 0 || HALL == 7)
			LED3 = 0;

		// TxPacket.done is not set while the packet is in transmission
		if ((cfgFlags & CFG_SPEW_ENCODER) && TxPacket.done && subPkt == NUM_TX_SUBPKTS) {
			transmit(&TxPacket);
			subPkt = 0;
		}

		if (RxPacket.done && RxPacket.address == 'w') {
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
				case 'c': // set config flags
					cfgFlags &= ~CFG_SPEW_ENCODER; // special: make spewing flag exclusive to one board
					if (RxPacket.data[0] == wheel)
						cfgFlags = RxPacket.data[1];
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
void commutateMotor(void)
{
	const unsigned char backdrive[8] = { 0b00000000, 	// 0 error
										 0b00010001,	//these are new commutation order, didn't fix direction biase problem :(
										 0b00100010,//2
										 0b00100001,//3
										 0b00001100,//4
										 0b00010100,//5
										 0b00001010,//6
									 	 0b00000000}; 	// 7 error



										/*0b00100001, 	// 4
										0b00001010, 	// 2		
										0b00100010, 	// 6
										0b00010100, 	// 1
										0b00010001, 	// 5
										0b00001100, 	// 3
										0b00000000}; 	// 7 error*/
	const unsigned char fordrive[8] = {0b00000000, 	// 0 error
										0b00001010,		// 1
										0b00010100,		// 2
										0b00001100,		// 3
										0b00100001,		// 4
										0b00100010,		// 5
										0b00010001,		// 6
										0b00000000};	// 7 error
	// read the hall sensors
	unsigned char hall = HALL;
	// to prevent glitching
	unsigned char _OVDCOND;
	unsigned char _OVDCONS;


	//				I	II	III	IV	V	VI
	//U12 high low 	h			l
	//U23 high low			h			l
	//U31 high low 		l			h

	//RC0 high low 	h			l
	//RC2 high low			h			l
	//Rc1 high low 		l			h
	







/*	if(hall==0){
		LED1 = 1;
		LED2 = 1;
		LED3 = 1;
	}
	else if(hall==1){
		LED1 = 0;
		LED2 = 1;
		LED3 = 1;;
	}
	else if(hall==2){
		LED1 = 1;
		LED2 = 0;
		LED3 = 1;
	}
	else if(hall==3){
		LED1 = 0;
		LED2 = 0;
		LED3 = 1;
	}
	else if(hall==4){
		LED1 = 1;
		LED2 = 1;
		LED3 = 0;;
	}
	else if(hall==5){
		LED1 = 0;
		LED2 = 1;
		LED3 = 0;
	}
	else if(hall==6){
		LED1 = 1;
		LED2 = 0;
		LED3 = 0;
	}
	else if(hall==7){
		LED1 = 0;
		LED2 = 0;
		LED3 = 0;
	}
*/








	//hall = 0b001;
	//direction = 1;
//	if (command == 0 && !(cfgFlags & CFG_FEEDBACK)){ // if command is zero we want to coast! (Not for use with feedback)
//		_OVDCOND = fordrive[0];
//		_OVDCONS = ~fordrive[0];
//LED4=0;
//	} else 
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



int cycle = 0;
void handleQEI(PacketBuffer * txPkt)
{
	unsigned int encoderCentered = 0;
	signed int encoder = 0;
	signed long int error = 0;
	signed int duty = 0;			// modifies speed based on PID feedback
	unsigned char dutyHigh, dutyLow;// high and low bits for duty cycle
	
	signed char encHigh;
	signed char encLow;
	signed long int command2;
	
	TMR0L = TIMER0INIT;

	// read and reset position accumulator
	encoderCentered = POSCNTH;
	encoderCentered = encoderCentered << 8;
	encoderCentered += POSCNTL;
	POSCNTH = 0x80;
	POSCNTL = 0x00;
		
    if (encoderCentered >=0x8000)
		encoder = (signed int)(encoderCentered - 0x8000);
	else									
		encoder = -(signed int)(0x8000-encoderCentered);

	encoder = - encoder;
	//command = 0x08
	//duty = 0x8f;
	//Do the controls math;

		command2 = ((signed long int)command)*4;
		error = command2 - (signed long int)encoder;
	//	error = error/4; test
		m = error + m_n1;
		e2 = 3*m-encoder;//3*m-encoder;
		duty = 2*(e2-e2_n1)+e2;//2*(e2-e2_n1)+e2;

	//	duty = 2*error;test
	
	//	if (encoder == 0 && command2 == 0) duty = 0; //to help with the nonlinearity;
		
		m_n1 = m;
		e2_n1 = e2;
//	}
//	cycle = cycle + 1;

//	duty = command;
//	duty = 0x8f;//command;
	//duty = duty*8;

//	if(duty > 400) duty = 10;
//	if(duty < -400) duty = -10;	

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
	if ((cfgFlags & CFG_SPEW_ENCODER) && txPkt->done && subPkt < NUM_TX_SUBPKTS) {
		// assemble one sub-packet
		txPkt->data[txPkt->length++] = encoder >> 8;
		txPkt->data[txPkt->length++] = encoder;
		txPkt->data[txPkt->length++] = duty >> 8;
		txPkt->data[txPkt->length++] = duty;
		txPkt->data[txPkt->length++] = command2 / 4;
		if (cfgFlags & CFG_SPEW_PKT_STATS) {
			txPkt->data[txPkt->length++] = pktsReceived;
			txPkt->data[txPkt->length++] = pktsAccepted;
			txPkt->data[txPkt->length++] = pktsMismatched;
		}
		subPkt++;
	}


//	LED3=!LED3;
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
	}
	if (PIE1bits.RCIE && PIR1bits.RCIF) {
		LED2 = 0;
		PIR1bits.RCIF = 0;
		handleRx(&RxPacket);
		LED2 = 1;
	}
	if (PIE1bits.TXIE && PIR1bits.TXIF) {
		PIR1bits.TXIF = 0;
		handleTx(&TxPacket);
	} 
}

void blinkLEDs(void)
{
	unsigned char timer, timer2;

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
}


