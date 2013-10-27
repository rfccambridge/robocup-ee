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

signed long int integral_last;
signed long int error_last;

/*Encoder frequency*/
//frequency of encoder sampling
const unsigned int encoder_freq_dividend = 46062; //do not change
int encoder_freq = 160; //in Hz, may be changed

int num_overcurrent = 0; //number of consecutive overcurrent trips by the ADC
unsigned int adc_value; //current ADC value
//on overcurrent, wait 20 iterations of consecutive current-ok readings
int off_timer = 20; //counts up to 20

const int MAX_DUTY = 511;

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

	//set up PWM
	PWM_Init();

	//set up ADC
	ADC_Init();

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
		//OVERCURRENT PROTECTION
		//>10A for 10 consecutive cycles to trip overcurrent
		//on overcurrent trip, <10A for 20 consecutive cycles to resume operation
		while(!ADCON1bits.DONE)
		adc_value = ADCBUF0;
		if (adc_value > 100)
		{
			num_overcurrent++;
			if (num_overcurrent >= 10) //ten consecutive overcurrents
			{
				LED4_O = 0;
				OVDCON = 0x003F;
				off_timer = 0;
			}
			else
			{
				LED4_O = 1;
				commutateMotor();
			}
		}
		else if (off_timer < 20) //wait 20 consecutive cycles on overcurrent
		{
			off_timer++;
			LED4_O = 0;
			OVDCON = 0x003F;
		}
		else
		{
			num_overcurrent = 0;
			LED4_O = 1;
			commutateMotor();
		}

		//DEAD HALL CHECK
		//read the hall sensors
		hall = 4*HALL1_I + 2*HALL2_I + HALL3_I; //notice the inversion!
		if (hall == 0 || hall == 7)
			LED3_O = 0;
		else
			LED3_O = 1;

		//TRANSMIT
		//TxPacket.done is not set while the packet is in transmission
		if ((cfgFlags & CFG_SPEW_ENCODER) && TxPacket.done && subPkt == NUM_TX_SUBPKTS) 
		{
			transmit(&TxPacket);
			subPkt = 0;
		}
		
		//RECEIVE COMMANDS
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
                                        {
						cfgFlags = RxPacket.data[1];
                                        }
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


	// read the hall sensors
	hall = 4*HALL1_I + 2*HALL2_I + HALL3_I; //notice the inversion!

	if (direction==0) {
		OVDCON = fordrive[hall];
	} else if (direction == 1){
		OVDCON = backdrive[hall];
	}
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
	POSCNT = 0x8000;
		
        if (encoderCentered >=0x8000)
		encoder = (signed int)(encoderCentered - 0x8000);
	else									
		encoder = -(signed int)(0x8000-encoderCentered);

	encoder = - encoder;

	//Do the controls math;
		command2 = ((signed long int)command)*4;
		error = command2 - (signed long int)encoder;

                int integral = integral_last + error;
                int derivative = error_last - error;

                // check for overflow of integral term
                if(integral_last > 0 && error > 0 && integral < 0) {
                    integral = 0x7FFF; // max positive
                }
                if (integral_last < 0 && error < 0 && integral > 0) {
                    integral = 0x8000; // max negative
                }

                float error_coef = 10;
                float int_coef = 1;
                float deriv_coef = 0;
                duty = (int)(error_coef * error + int_coef * integral + deriv_coef * derivative);

                integral_last = integral;
                error_last = integral;

	if(duty > MAX_DUTY)
            duty = MAX_DUTY;
	if(duty < -MAX_DUTY)
            duty = -MAX_DUTY;

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
	PDC1 = duty;
	PDC2 = duty;
	PDC3 = duty;
	
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
PWM_Init() sets up the PWM registers and starts the PWM (with duty cycle 0).
*/
void PWM_Init(void)
{
	PTCONbits.PTMOD = 0b00; //time base in free running mode
	/* PWM time base input clock period is TCY (1:1 prescale) */
	/* PWM time base output post scale is 1:1 */
	PTCONbits.PTCKPS = 0b00;
	PTCONbits.PTOPS = 0b00;
	/* 11 bits PWM resolution
	   F_CY = 29.48MHz
	   F_PWM = 2*F_CY/2^11 = 28.79kHz
       P1TPER = F_CY/(F_PWM) - 1 = 1023
	   There are 11 bits of resolution because each unit in the duty cycle
       is half a unit of the period
       Thus, duty cycle can be from 0-2047
	*/
	PTPER = 1023;
	//all PWM pin pairs are in independent mode
	PWMCON1bits.PMOD1 = 1;
	PWMCON1bits.PMOD2 = 1;
	PWMCON1bits.PMOD3 = 1;
	//enable all pins for PWM output
	PWMCON1bits.PEN1H = 1;
	PWMCON1bits.PEN2H = 1;
	PWMCON1bits.PEN3H = 1;
	PWMCON1bits.PEN1L = 1;
	PWMCON1bits.PEN2L = 1;
	PWMCON1bits.PEN3L = 1;
	//allow immediate updates to PWM duty cycle
	PWMCON2bits.IUE = 1;
	//asynchronous updates to duty cycle
	PWMCON2bits.OSYNC = 0;
	//updates to duty cycle are enabled
	PWMCON2bits.UDIS = 0;
	//initialize with all duty cycle registers set to 0
	PDC1 = 0;
	PDC2 = 0;
	PDC3 = 0;
	//start off with override of all PWM outputs to off state
	OVDCON = 0x003F;
	//enable PWM
	PTCONbits.PTEN = 1;
}

/*
Functions:
ADC_Init() sets up the ADC module.
ADC maps sense voltage to AVDD-AVSS=5V in 1024 steps (10 bits)
10A -> V=10(.047)=.47 = 5/1024*96
Trigger over-current when ADC result is over 100 for 10 continuous cycles
*/
void ADC_Init(void)
{
	ADCON1bits.ADON = 0; //turn ADC off
	ADCON2bits.VCFG = 0; //AVDD is Vref+ and AVSS is Vref-
	//F_CY = 29.48MHz
	//frequency of ADC = 2*F_CY/(ADCS+1) = 3.685MHz
	//TAD = 217ns
	ADCON3bits.ADRC = 0; //system clock used for ADC
	ADCON3bits.ADCS = 0b001111; 
	ADCON2bits.CHPS = 0; //Channel 0 sampled only
	ADCON2bits.CSCNA = 0; //do not scan inputs
	ADCHSbits.CH0NA = 0; //negative input of Channel 0 is Vref- = AVSS
	ADCHSbits.CH0SA = 0b0110; //positive input of Channel 0 is AN6
	ADCON1bits.SSRC = 0b111; //auto-conversion
	ADCON1bits.ASAM = 1; //auto-sampling
	ADCON3bits.SAMC = 0b00001; //1 TAD per sample
	ADCON1bits.FORM = 0; //results represented in integer form
	ADCON2bits.SMPI = 0; //interrupts every sample (but don't care)
	ADCON2bits.BUFM = 0; //one 16-word buffer
	ADCON2bits.ALTS = 0; //always use MUX A multiplexer
	ADCON1bits.ADON = 1; //turn ADC on
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




