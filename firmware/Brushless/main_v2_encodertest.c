#include <string.h>
#include "bemixnet_v2.h"
#include "pins_v2.h"
#include <p30F4011.h>

// Configuration flags
#define CFG_SPEW_ENCODER      0b00000001
#define CFG_SPEW_PKT_STATS    0b00000010
#define CFG_FEEDBACK          0b00000100
// Each tx pkt is made up of several sub-packets to minimize transmission overhead 
// NOTE: total packet size must not exceed MAX_PACKET_SIZE defined in bemixnet.h
// TODO: doesn't work with more than one sub-packet!!!
#define NUM_TX_SUBPKTS 1

/*Power-on-reset Configuration*/
//POR timer off, brown-out reset off, low side active-low, high side active-high, PWM pins configured as digital I/O on POR
_FBORPOR(PWRT_OFF & PBOR_OFF & PWMxL_ACT_LO & PWMxH_ACT_HI & RST_IOPIN);
_FOSC(FRC_PLL16 & CSW_FSCM_OFF); //fast RC clock with 16x PLL, no clock switching and no clock monitor
_FWDT(WDT_OFF); //no watchdog timer
_FGS(GWRP_OFF & CODE_PROT_OFF); //no code protection
_FICD(PGD); //communicate through PGC and PGD pins

/* Global Variables and Functions */
int main (void);
void Interrupt_Init(void);
void IO_Init(void);
void PWM_Init(void);
void ADC_Init(void);
void Encoder_Init(void);
void __attribute__((__interrupt__, auto_psv)) _T1Interrupt(void);
void __attribute__((__interrupt__, auto_psv)) _U2RXInterrupt(void);
void __attribute__((__interrupt__, auto_psv)) _U2TXInterrupt(void);
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void);
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
const unsigned int encoder_freq_dividend = 46062; //do not change
int encoder_freq = 160; //in Hz, may be changed
int encoder_loop_count = 0;
int encoder_running_count = 0;

int num_overcurrent = 0; //number of consecutive overcurrent trips by the ADC
unsigned int adc_value; //current ADC value
//on overcurrent, wait 20 iterations of consecutive current-ok readings
int off_timer = 20; //counts up to 20

int main (void)
{
	//setup internal clock for 120MHz/30MIPS
	//7.37*16=117.92MHz
	//F_CY=117.92MHz/4=29.48MHz/MIPS
	OSCCONbits.COSC = 0b01; //FRC oscillator
	OSCCONbits.POST = 0b00; //no postscaler
        while(!OSCCONbits.LOCK); //wait for PLL ready

	//set up I/O
	IO_Init();

	blinkLEDs();

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
	}
	return 0;
}

void handleQEI(PacketBuffer * txPkt)
{
	unsigned int encoderCentered = 0;
        signed int encoder = 0;
	signed long int error = 0;
	signed int duty = 0;			// modifies speed based on PID feedback
	signed long int command2;
	
	//TMR1 = 0x0000; //reset timer 1 register

	// read and reset position accumulator
	encoderCentered = POSCNT;

        /*
	POSCNT = 0x8000;
		
        if (encoderCentered >=0x8000)
		encoder = (signed int)(encoderCentered - 0x8000);
	else									
		encoder = -(signed int)(0x8000-encoderCentered);

	encoder = - encoder;
        */

        encoder_loop_count++;
        if (encoder_loop_count > 500) {
            encoder_loop_count = 0;
            LED1_O = 1;
        }
}

/*
Functions:
Interrupt_Init() sets up the Timer 1, U2RX, and U2TX interrupts.
Priority: U2RX highest, then Timer 1, then U2TX lowest
*/
void Interrupt_Init(void)
{
	//set up UART
	//F_CY = 29.48MHz
	U2MODE = 0; //clear mode register
    U2BRG = 47; //38385 baud rate = 29.48E6/16/(U2BRG+1)
	
	initRx(&RxPacket);
	initTx(&TxPacket);
	subPkt = 0;

	//set up Timer 1
	T1CONbits.TON = 0; // disable timer
	T1CONbits.TCS = 0; // internal instruction cycle clock
	T1CONbits.TGATE = 0; // disable gated timer mode
	T1CONbits.TCKPS = 0b10; // prescale value 1:64
	TMR1 = 0x00; // clear timer register
	// frequency of timer interrupts is 160Hz
	PR1 = (encoder_freq_dividend/encoder_freq)*10; 

	__asm__ volatile ("DISI #0x1FFF"); //disable interrupts

	INTCON1bits.NSTDIS = 0; //interrupts can interrupt each other
	
	IPC6bits.U2TXIP = 0b100; //U2TX has priority 4
	IPC0bits.T1IP = 0b101; //Timer 1 has priority 5
	IPC6bits.U2RXIP = 0b110; //U2RX has priority 6
	
	//clear U2RX flag
	IFS1bits.U2RXIF = 0;

	//clear U2TX flag
	IFS1bits.U2TXIF = 0;

	//clear T1 flag
	IFS0bits.T1IF = 0;

	//enable T1 interrupt
	IEC0bits.T1IE = 1;

	//enable U2RX interrupt
	IEC1bits.U2RXIE = 1;

	//U2TX interrupt is not enabled because that is done by transmit()

	DISICNT = 0; //enable interrupts

	U2MODEbits.UARTEN = 1; //enable the UART
	U2STAbits.UTXEN = 1; //enable the transmitter

	//turn T1 on
	T1CONbits.TON = 1;
}

/*
Functions:
IO_Init() sets up all digital and analog pins.
*/
void IO_Init(void)
{
	ADPCFG = 0xFFFF;
	ADPCFGbits.PCFG6 = 0; //only analog input in analog mode
	TRISB = 0x01F0; //B4,5,6,7,8 are inputs, rest are outputs
	TRISC = 0x4000; //C14 is an input, rest are outputs
	TRISD = 0x000F; //D1,2,3,4 are inputs, rest are outputs
	TRISE = 0x0100; //E8 is an input, rest are outputs
	TRISF = 0x0050; //F4,6 are inputs, rest are outputs
	LATCbits.LATC13 = 0; //unused pin
	LATCbits.LATC15 = 0; //unused pin
	PWMDIS_O = 0; //PWMDIS pin, always pulled low to enable PWM
	TXEN_O = 1; //TXEN pin, always high to enable TX
}

/*
Functions:
Encoder_Init() sets up the QEI.
*/
void Encoder_Init(void)
{
	//assign encoder pins
	MAXCNT = 0xFFFF; //maximum range for encoder counts
	POSCNT = 0x8000; //start out encoder at middle value
	QEICONbits.QEIM = 0b111; //x4 mode with position counter reset by match
	//a digital filter may be included by setting register DFLTCON
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
	//clear T1 interrupt flag -- disable interrupts when performing this action
	__asm__ volatile ("DISI #0x1FFF"); //disable interrupts
	IFS0bits.T1IF = 0;
	DISICNT = 0; //enable interrupts
	handleQEI(&TxPacket); // read/process encoder value
}

void __attribute__((__interrupt__, auto_psv)) _U2RXInterrupt(void)
{
	LED2_O = 0;
	//clear U2RX interrupt flag -- disable interrupts when performing this action
	__asm__ volatile ("DISI #0x1FFF"); //disable interrupts
	IFS1bits.U2RXIF = 0;
	DISICNT = 0; //enable interrupts
	handleRx(&RxPacket);
	LED2_O = 1;
}

void __attribute__((__interrupt__, auto_psv)) _U2TXInterrupt(void)
{
	//clear U2TX interrupt flag -- disable interrupts when performing this action
	__asm__ volatile ("DISI #0x1FFF"); //disable interrupts
	IFS1bits.U2TXIF = 0; 
	DISICNT = 0; //enable interrupts
	handleTx(&TxPacket);
}

//this handler is to resolve an issue in the silicon in which the 
//oscillator fail interrupt is triggered but the oscillator has not failed
void __attribute__((__interrupt__, auto_psv)) _OscillatorFail(void)
{
	INTCON1bits.OSCFAIL = 0;
}




