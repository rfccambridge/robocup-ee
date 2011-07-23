#include <string.h>
#include "bemixnet_v2.h"
#include "pins_v2.h"
#include <p33FJ32MC304.h>

// Configuration flags
#define CFG_SPEW_ENCODER      0b00000001
#define CFG_SPEW_PKT_STATS    0b00000010
#define CFG_FEEDBACK          0b00000100
// Each tx pkt is made up of several sub-packets to minimize transmission overhead 
// NOTE: total packet size must not exceed MAX_PACKET_SIZE defined in bemixnet.h
// TODO: doesn't work with more than one sub-packet!!!
#define NUM_TX_SUBPKTS 1

/*Power-on-reset Configuration*/
//POR timer off, low side active-low, high side active-high, PWM pins configured as digital I/O on POR
_FPOR(FPWRT_PWR1 & LPOL_OFF & HPOL_ON & PWMPIN_ON) 
_FOSCSEL(FNOSC_FRCPLL) //fast RC clock with PLL
//no clock output, no clock switching, no clock failsafe, allow multiple peripheral reconfigurations
_FOSC(OSCIOFNC_ON & POSCMD_NONE & FCKSM_CSDCMD & IOL1WAY_OFF) 
_FWDT(FWDTEN_OFF) //no watchdog timer
_FICD(JTAGEN_OFF & ICS_PGD1); //no JTAG, program through PGD1 and PGE1
_FGS(GWRP_OFF & GCP_OFF); //no code protection

/* Global Variables and Functions */
int main (void);
void Interrupt_Init(void);
void IO_Init(void);
void PWM_Init(void);
void Comparator_Init(void);
void Encoder_Init(void);
void __attribute__((__interrupt__)) _T1Interrupt(void);
void __attribute__((__interrupt__)) _U1RXInterrupt(void);
void __attribute__((__interrupt__)) _U1TXInterrupt(void);
void handleQEI(PacketBuffer * TxPacket);
static void blinkLEDs(void);
static void commutateMotor(void);

/*Variables for communication*/
PacketBuffer RxPacket;
PacketBuffer TxPacket;
unsigned char cfgFlags = 0;
unsigned char subPkt = 0; // iterator over the sub-packets
unsigned int wheel;   // board id

/*Variables for control*/
unsigned char hall;
/*
signed int Pconst, Iconst, Dconst;
signed int previous_error = 0;
signed int Iterm = 0;
*/
signed char command = 0;
unsigned char direction = 0;
// Ben's minor loop velocity controller
signed long int m = 0;
signed long int m_n1 = 0; //from from the last iteration
signed long int e2 = 0;
signed long int e2_n1 = 0; //e2 from the last iteration

/*Encoder frequency*/
//frequency of encoder sampling
const unsigned int encoder_freq_dividend = 61891; //do not change
int encoder_freq = 160; //in Hz, may be changed

int main (void)
{
	//setup internal clock for 80MHz/40MIPS
	//7.37/2=3.685*43=158.455/2=79.2275
	//F_CY=39.61MHz
	CLKDIVbits.PLLPRE = 0; // PLLPRE (N2) 0=/2 
	PLLFBD = 41; //pll multiplier (M) = +2
	CLKDIVbits.PLLPOST = 0; // PLLPOST (N1) 0=/2
    while(!OSCCONbits.LOCK); //wait for PLL ready

	//set up I/O
	IO_Init();

	//set up PWM
	PWM_Init();

	//set up comparator
	Comparator_Init();

	cfgFlags = CFG_FEEDBACK; // | CFG_SPEW_ENCODER;

	blinkLEDs();
	
	/* Figure out which wheel this is
	 0 -- Front right
	 1 -- Front left
   	 2 -- Rear left
	 3 -- Rear right
	*/
	wheel = BBID1_I + 2*BBID0_I; //notice the inversion!

	//set up encoder
	Encoder_Init();

	//set up interrupts
	Interrupt_Init();

	//initial values for control
	/*
	Pconst = 50;
	Dconst = 3;
	Iconst = 1;
	Iterm = 0;
	previous_error = 0;
	*/

	//begin operation
	LED1_O =0;
	
	while (1)
	{
		//check for overcurrent condition
		if (CMCONbits.C1OUT == 1)
		{
			LED4_O = 0;
			P1OVDCON = 0x003F;
		}
		else
		{
			LED4_O = 1;
			commutateMotor();
		}

		//check for dead hall
		//read the hall sensors
		hall = 4*HALL1_I + 2*HALL2_I + HALL3_I; //notice the inversion!
		if (hall == 0 || hall == 7)
			LED3_O = 0;

		//TxPacket.done is not set while the packet is in transmission
		//transmit if necessary
		if ((cfgFlags & CFG_SPEW_ENCODER) && TxPacket.done && subPkt == NUM_TX_SUBPKTS) 
		{
			transmit(&TxPacket);
			subPkt = 0;
		}
		
		if (RxPacket.done && RxPacket.address == 'w') 
		{
			ClrWdt();
			RxPacket.done = 0;
			switch(RxPacket.port) 
			{
				/*
				case 'r':
					//Reset(); //not a defined function
				*/
				case 'w':
					// Get the transmitted wheel speed			
					command = RxPacket.data[wheel];
					break;
				/*
				case 'f':
					Pconst = (signed int) RxPacket.data[0];
					Iconst = (signed int) RxPacket.data[1];
					Dconst = (signed int) RxPacket.data[2];
					break;
				*/
				case 'c': // set config flags
					cfgFlags &= ~CFG_SPEW_ENCODER; // special: make spewing flag exclusive to one board
					if (RxPacket.data[0] == wheel)
						cfgFlags = RxPacket.data[1];
					break;
				/*
				case 's': // temporary value - make this work
					// TODO: estimate wheel speed
					break;
				*/
				default:
					break;	
			}
		}
	}
	return 0;
}

static void commutateMotor(void)
{
	/* Brushless.c tables
	const unsigned char backdrive[8] = { 0b00000000, 	// 0 error
										 0b00010001,	//these are new commutation order, didn't fix direction biase problem :(
										 0b00100010,//2
										 0b00100001,//3
										 0b00001100,//4
										 0b00010100,//5
										 0b00001010,//6
									 	 0b00000000}; 	// 7 error

	const unsigned char fordrive[8] = {0b00000000, 	// 0 error
										0b00001010,		// 1
										0b00010100,		// 2
										0b00001100,		// 3
										0b00100001,		// 4
										0b00100010,		// 5
										0b00010001,		// 6
										0b00000000};	// 7 error
	*/
	const unsigned int backdrive[8] = {  0b0000000000111111, 	// 0 error
										 0b0000100000101111,	//1
										 0b0000001000111011,    //2
										 0b0000001000101111,    //3
										 0b0010000000111110,    //4
										 0b0000100000111110,    //5
										 0b0010000000111011,    //6
									 	 0b0000000000111111}; 	// 7 error

	const unsigned int fordrive[8] = {  0b0000000000111111, 	// 0 error
										0b0010000000111011,		// 1
										0b0000100000111110,		// 2
										0b0010000000111110,		// 3
										0b0000001000101111,		// 4
										0b0000001000111011,		// 5
										0b0000100000101111,		// 6
										0b0000000000111111};	// 7 error


	//				I	II	III	IV	V	VI
	//U12 high low 	h			l
	//U23 high low			h			l
	//U31 high low 		l			h

	//RC0 high low 	h			l
	//RC2 high low			h			l
	//Rc1 high low 		l			h

/*
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

*/
	// read the hall sensors
	hall = 4*HALL1_I + 2*HALL2_I + HALL3_I; //notice the inversion!

	if (direction==0) {
		P1OVDCON = fordrive[hall];
	} else if (direction == 1){
		P1OVDCON = backdrive[hall];
	}
}

void handleQEI(PacketBuffer * txPkt)
{
	unsigned int encoderCentered = 0;
	signed int encoder = 0;
	signed long int error = 0;
	signed int duty = 0;			// modifies speed based on PID feedback
	signed long int command2;
	
	TMR1 = 0x0000; //reset timer 1 register

	// read and reset position accumulator
	encoderCentered = POS1CNT;
	POS1CNT = 0x8000;
		
    if (encoderCentered >=0x8000)
		encoder = (signed int)(encoderCentered - 0x8000);
	else									
		encoder = -(signed int)(0x8000-encoderCentered);

	encoder = - encoder;

	//Do the controls math;
		command2 = ((signed long int)command)*4;
		error = command2 - (signed long int)encoder;
	//	error = error/4; //test
		m = error + m_n1;
		e2 = 3*m-encoder;//3*m-encoder;
		duty = 2*(e2-e2_n1)+e2;//2*(e2-e2_n1)+e2;

	//	duty = 12*error;//test
		
		m_n1 = m;
		e2_n1 = e2;

	if(duty > 1023) duty = 1023;
	if(duty < -1023) duty = -1023;	

	// convert to 11 bit sign magnitude
	if (duty >= 0) {
		direction = 1;
	} else {
		duty = -duty;
		direction = 0;
	}
	duty = 1023 - duty;
	duty = duty * 2;
	
	// set duty cycle
	P1DC1 = duty;
	P1DC2 = duty;
	P1DC3 = duty;
	
	// put data in transmit buffer
	if ((cfgFlags & CFG_SPEW_ENCODER) && txPkt->done && subPkt < NUM_TX_SUBPKTS) 
	{
		// assemble one sub-packet
		txPkt->data[txPkt->length++] = encoder >> 8;
		txPkt->data[txPkt->length++] = encoder;
		txPkt->data[txPkt->length++] = duty >> 8;
		txPkt->data[txPkt->length++] = duty;
		txPkt->data[txPkt->length++] = command2 / 4;
		if (cfgFlags & CFG_SPEW_PKT_STATS) 
		{
			txPkt->data[txPkt->length++] = pktsReceived;
			txPkt->data[txPkt->length++] = pktsAccepted;
			txPkt->data[txPkt->length++] = pktsMismatched;
		}
		subPkt++;
	}
}

/*
Functions:
Interrupt_Init() sets up the Timer 1, U1RX, and U1TX interrupts.
Priority: U1RX highest, then Timer 1, then U1TX lowest
*/
void Interrupt_Init(void)
{
	//assign UART pins
	U1RXR_I = 9; //set U1RX to RP9
	RP8_O = U1TX_O; //set U1TX to RP8

	//set up UART
    U1BRG = 256; //38500 baud rate = 39.61E6/4/(U1BRG+1)
    U1MODE = 0; //clear mode register
    U1MODEbits.BRGH = 1; //use high percison baud generator
	
	initRx(&RxPacket);
	initTx(&TxPacket);
	subPkt = 0;

	U1STAbits.UTXEN = 1; //enable the transmitter
	U1MODEbits.UARTEN = 1; //enable the UART

	//set up Timer 1
	T1CONbits.TON = 0; // disable timer
	T1CONbits.TCS = 0; // internal instruction cycle clock
	T1CONbits.TGATE = 0; // disable gated timer mode
	T1CONbits.TCKPS = 0b10; // prescale value 1:64
	TMR1 = 0x00; // clear timer register
	// frequency of timer interrupts is 160Hz
	PR1 = (encoder_freq_dividend/encoder_freq)*10; 

	INTCON1bits.NSTDIS = 0; //interrupts can interrupt each other
	
	IPC3bits.U1TXIP = 0b100; //U1TX has priority 4
	IPC0bits.T1IP = 0b101; //Timer 1 has priority 5
	IPC2bits.U1RXIP = 0b110; //U1RX has priority 6
	
	//clear U1RX flag
	IFS0bits.U1RXIF = 0;

	//clear U1TX flag
	IFS0bits.U1TXIF = 0;

	//clear T1 flag
	IFS0bits.T1IF = 0;

	//enable T1 interrupt
	IEC0bits.T1IE = 1;

	//enable U1RX interrupt
	IEC0bits.U1RXIE = 1;

	//U1TX interrupt is not enabled because that is done by transmit()

	//turn T1 on
	T1CONbits.TON = 1;
}

/*
Functions:
IO_Init() sets up all digital and analog pins.
*/
void IO_Init(void)
{
	AD1PCFGL = 0xFFFF;
	AD1PCFGLbits.PCFG4 = 0; //only AN4 (sense) is analog pin
	TRISA = 0x031C; //A2,3,4,8,9 are inputs, rest are outputs
	LATAbits.LATA7 = 0; //unused pin
	LATAbits.LATA10 = 0; //unused pin
	TRISB = 0x02F7; //B0,1,2,4,5,6,7,9 are inputs, rest are outputs
	TRISC = 0x0018; //C3,4 are inputs, rest are outputs
	LATCbits.LATC1 = 0; //unused pin
	LATCbits.LATC2 = 0; //unused pin
	LATCbits.LATC5 = 0; //unused pin
	LATCbits.LATC7 = 0; //unused pin
	LATCbits.LATC8 = 0; //unused pin
	LATCbits.LATC9 = 0; //PWMDIS pin, always pulled low to enable PWM
	LATCbits.LATC6 = 1; //TXEN pin, always high to enable TX
}

/*
Functions:
PWM_Init() sets up the PWM registers and starts the PWM (with duty cycle 0).
*/
void PWM_Init(void)
{
	P1TCONbits.PTMOD = 0b00; //time base in free running mode
	/* PWM time base input clock period is TCY (1:1 prescale) */
	/* PWM time base output post scale is 1:1 */
	P1TCONbits.PTCKPS = 0b00;
	P1TCONbits.PTOPS = 0b00;
	/* 11 bits PWM resolution
	   F_PWM = 2*F_CY/2^11 = 38.685kHz
       P1TPER = F_CY/(F_PWM) - 1 = 1023
	   There are 11 bits of resolution because each unit in the duty cycle
       is half a unit of the period
       Thus, duty cycle can be from 0-2047
	*/
	P1TPER = 1023;
	//all PWM pin pairs are in independent mode
	PWM1CON1bits.PMOD1 = 1;
	PWM1CON1bits.PMOD2 = 1;
	PWM1CON1bits.PMOD3 = 1;
	//enable all pins for PWM output
	PWM1CON1bits.PEN1H = 1;
	PWM1CON1bits.PEN2H = 1;
	PWM1CON1bits.PEN3H = 1;
	PWM1CON1bits.PEN1L = 1;
	PWM1CON1bits.PEN2L = 1;
	PWM1CON1bits.PEN3L = 1;
	//allow immediate updates to PWM duty cycle
	PWM1CON2bits.IUE = 1;
	//asynchronous updates to duty cycle
	PWM1CON2bits.OSYNC = 0;
	//initialize with all duty cycle registers set to 0
	P1DC1 = 0;
	P1DC2 = 0;
	P1DC3 = 0;
	//start off with override of all PWM outputs to off state
	P1OVDCON = 0x003F;
	//enable PWM
	P1TCONbits.PTEN = 1;
}

/*
Functions:
Comparator_Init() sets up the comparator module.
*/
void Comparator_Init(void)
{
	//CMCONbits.C1OUT = 1 in overcurrent condition, = 0 otherwise
	CMCONbits.C1INV = 1;
	CVRCONbits.CVRR = 1;
	//reference voltage is .63V, thus comparator trips when current is
	//over .63V/.047 = 13A
	CVRCONbits.CVR = 3; 
	CVRCONbits.CVREN = 1;
	CMCONbits.C1EN = 1;
}

/*
Functions:
Encoder_Init() sets up the QEI.
*/
void Encoder_Init(void)
{
	//assign encoder pins
	QEA1R_I = 20; //set QEA1R to RP20
	QEB1R_I = 19; //set QEB1R to RP19
	MAX1CNT = 0xFFFF; //maximum range for encoder counts
	POS1CNT = 0x8000; //start out encoder at middle value
	QEI1CONbits.QEIM = 0b111; //x4 mode with position counter reset by match
	//a digital filter may be included by setting register DFLT1CON
}

void blinkLEDs(void)
{
	unsigned char timer, timer2;

	LED1_O = 1;
	LED2_O = 1;
	LED3_O = 1;
	for (timer2=0; timer2<16; timer2++)
		for (timer=0; timer<255; timer++);
	LED1_O = 0;
	LED2_O = 0;
	LED3_O = 0;
	for (timer2=0; timer2<16; timer2++)
		for (timer=0; timer<255; timer++);
	LED1_O = 1;
	LED2_O = 1;
	LED3_O = 1;
}

void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void)
{
	IFS0bits.T1IF = 0; // clear T1 interrupt flag
	handleQEI(&TxPacket); // read/process encoder value
}

void __attribute__((__interrupt__, auto_psv)) _U1RXInterrupt(void)
{
	LED2_O = 0;
	IFS0bits.U1RXIF = 0; // clear U1RX interrupt flag
	handleRx(&RxPacket);
	LED2_O = 1;
}

void __attribute__((__interrupt__, auto_psv)) _U1TXInterrupt(void)
{
	IFS0bits.U1RXIF = 0; // clear U1TX interrupt flag
	handleTx(&TxPacket);
}




