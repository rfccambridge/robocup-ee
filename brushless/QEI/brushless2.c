//coded by Minjae Kim
//Jan 2006
//Note
//Motor control through ADC works fine. (Finalized)
//Direction Implemented

// to do:
// only PWM high side
// implement encoder


#include	<p18f4431.h>

#define LED1	PORTDbits.RD4
#define LED2	PORTDbits.RD5

//Used for measured RPM caculation and ADC
unsigned char	i;	//a counter for ADC

signed int 			DuCyValue;			//Duty Cycle value

void high_ISR();	 //Interrupt Service Routine


unsigned char commutate(unsigned char hall);


void main(){
	
//==================testing
	DuCyValue = -0x6000;
	if (DuCyValue>0x03FF) DuCyValue=0x03FF; 					//maximum PID value allowed.
	if (DuCyValue<0x0000) DuCyValue=0x0000;

	TRISB = 0x00;
	TRISC = 0xFF;							//TRISC all inputs for hall sensors (RC0-RC2)

	TRISDbits.TRISD0 = 1;					//RD0 is input for direction of speed
	TRISDbits.TRISD4 = 0;					// output for LED1
	TRISDbits.TRISD5 = 0;					// output for LED2
	OSCCON = OSCCON | 0b01110000;			//internal oscillator 8MHz
	
	ADCON3bits.ADRS1 = 0;				
	ADCON3bits.ADRS0 = 0;					//ADC interrupt set when each data buffer word is written
	
	//PWM ini'n
	PWMCON0 = 0b01001111;					// PWM0-5 enabled, independent mode. 
	PTPERH=0x03;
	PTPERL=0xFF;							//Hence the period (12 bit max) is PTPERH:L = 0000 0011 1111 1111 (10-bit used)
											//So, we are only using 10 bit to match 10 bit ADC.
	OVDCONS = 0xFF;							//When OVDCOND=0x00, all pins are high (this is for PWM inversion).

	PTCON1 = 0x80;							//PTMR enabled, counts up
	
	//ADC ini'n
	ADCON2 = 0b10001010;						//right justified, 2 TAD delay, FOSC/32  -> Tacq on the order of 10 uS.
	ADCON3=0b00000000;						//no FIFO. All triggers disabled.	
	ADCON0bits.ADON = 1;					//ADC on
	ANSEL0bits.ANS0 = 1;					//AN0 (RA0) is analog input
	TRISA = 0b00011101;						//RA0 (AN0) is input
	i=0;									//counter initialization

	// init QEI
	QEICON = 0b00001000;
		// velocity mode enabled
		// inc on QEA (2x update)	

	//interrupts init
	INTCONbits.GIE = 1;						//Global Interrupt bit enabled.  Interrupts can be used.
	INTCONbits.PEIE = 1;					//Peripheral Interrupt enabled
	PIE1bits.ADIE = 1;						//ADC interrupt enabled.

	//commutation sequence
	do{
		// flash power light
		LED1 = 0;
		if (i>50) LED1 = 1;
		
//		LED2 = 0;
//		if (((PORTC&0b00000111)==0x00) || ((PORTC&0b00000111)==0x07)) LED2 = 1;

		LED2 = 0;
		if (VELRL > 10) LED2 = 1;

		OVDCOND = commutate(PORTC);

		i++;
		if(i>100){	
			ADCON0bits.GO = 1;  				//Starts ADC.  This bit automatically cleared after conversion.
			i=0;
		}					


	}while(1);

	//default settings included for completeness
	ADCON0bits.ACONV = 0;				//Single shot mode.(Default)
		
	ADCON0bits.ACSCH = 0; 				//single-channel mode(default)
	ADCON0bits.ACMOD1 = 0;				
	ADCON0bits.ACMOD0 = 0; 				//using Group A(default)  Group A: AN0, AN4, AN8  (AN0 selected by default)
										//AN0 is for speed information.

	ADCON1bits.VCFG1 = 0;					
	ADCON1bits.VCFG0 = 0;				//AVDD and AVSS used as reference voltage(default)
	ADCON1bits.FIFOEN = 0; 				// don't need multiple level addressing(default)

}



unsigned char commutate(unsigned char hall)
{
	const unsigned char fordrive[8] = { 0b00000000, 	//	0:error
										0b00010100, 	//	1
										0b00001010, 	//	2
										0b00001100, 	//	3
										0b00100001, 	//	4
										0b00010001, 	//	5
										0b00100010, 	//	6
										0b00000000}; 	//	7
	const unsigned char backdrive[8] = {0b00000000, 	//0: error
										0b00100001,		//1
										0b00010100,		//2
										0b00010001,		//3
										0b00001010,		//4
										0b00100010,		//5
										0b00001100,		//6
										0b00000000};	//7

	if (PORTDbits.RD0)
		return fordrive[PORTC&0x07];
	else
		return backdrive[PORTC&0x07];		
}


#pragma code high_vector=0x08			//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm}				//branching to the actual ISR
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR(){
	if (PIR1bits.ADIF) {
		PIR1bits.ADIF = 0;
		//bit shifting required for PDCn (14 bit).  Actual duty cycle 12 bit.  Lower 2 bits filled with 00, so PWM edge at Q1.
		DuCyValue=(0x03ff-ADRES)<<2;				//bit shifting compensating for last two digits of PWM DC registers
		PDC1L=DuCyValue;								//upper bits discarded
		PDC1H=DuCyValue>>8;							//lower bits discarded
		PDC2L=DuCyValue;								
		PDC2H=DuCyValue>>8;
		PDC3L=DuCyValue;								
		PDC3H=DuCyValue>>8;
	}									
}
