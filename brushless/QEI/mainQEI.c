//coded by Minjae Kim
//Jan 2006
//Note
//Motor control through ADC works fine. (Finalized)
//Direction Implemented
//No encoder implemented
/* ===== pin out =====
 * 01 - MCLR
 * 02 - AN0 = speed
 * 03 - AN1
 * 04 - INDX = N/C
 * 05 - QEA = encoder A
 * 06 - QEB = encoder B
 * 07 - AN5\
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
 * 18 - INT0\
 * 19 - RD0  
 * 20 - RD1 = direction 
 * 21 - RD2
 * 22 - RD3
 * 23 - RC4
 * 24 - RC5
 * 25 - RC6
 * 26 - RC7
 * 27 - RD4 = LED
 * 28 - RD5 = LED
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

#include	<p18f4431.h>
//==========Speed Calculation=================
#define		OSCILLATOR					8000000		//internal 8MHz
#define		ENCODER_PPR 				256 		//PPR of Encoder on the motor
#define 	TIMER5_PRESCALE 			1 			//Timer5 prescaler
#define 	QEI_UPDATE 					4 			//Define the QEI mode of operation.
#define 	VELOCITY_PULSE_DECIMATION 	16			//ratio
#define		MAX_RPM						5000		//assumed value of maximum rpm of the motor

//==========PI control=======================
#define		Kp							2			//Proportional Constant
#define		Ki							1			//Integral Constant




#define LED1	PORTDbits.RD4
#define LED2	PORTDbits.RD5


//Used for measured RPM caculation and ADC
unsigned char	i;	//a counter for ADC


int VELREAD;
int VELREADH;    	//only lower byte occupied
int VELREADL;		//only lower byte occupied
int INST_CYCLE;  
int	RPM_CONST;
int SPEED;

unsigned int SPEED_BYTE;  	//measured speed in byte
unsigned int Error_Spd;		//desired speed - measured speed (unitless in bytes)
unsigned int IntegralC;		//Integral Component 		
unsigned int PropC;			//Proportional Component 
unsigned int DuCyValue;		//Duty Cycle value.


void high_ISR();	 //Interrupt Service Routine


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


void main(){

	TRISB = 0x00;
	TRISC = 0xFF;							//TRISC all inputs for hall sensors (RC0-RC2)

	TRISDbits.TRISD0 = 1;					//RD0 is input for direction of speed
	TRISDbits.TRISD4 = 0;					// output for LED1
	TRISDbits.TRISD5 = 0;					// output for LED2
	OSCCON = OSCCON | 0b01110000;			//internal oscillator 8MHz



	//interrupts ini'n
	INTCONbits.GIE = 1;					//Global Interrupt bit enabled.  Interrupts can be used.
	INTCONbits.PEIE = 1;				//Peripheral Interrupt enabled

	PIE1bits.ADIE = 1;					//ADC interrupt enabled.
	PIE3bits.IC1IE = 1;					//IC1 interrupt enabled.
	
	ADCON3bits.ADRS1 = 0;				
	ADCON3bits.ADRS0 = 0;				//ADC interrupt set when each data buffer word is written
	
	//TMR ini'n
	CAP1CONbits.CAP1REN = 1;			//TMR5 reset at every capture event
	T5CONbits.TMR5ON = 1;				//TMR 5 enabled; other settings are left to default
		
	//QEI ini'n.  inefficient, but readable
	QEICONbits.VELM=0;					//Velocity Mode enabled
	QEICONbits.QEIM2=1;
	QEICONbits.QEIM1=1;
	QEICONbits.QEIM0=0;					//4x update mode, reset when POSCNT=MAXCNT
	QEICONbits.PDEC1=1;
	QEICONbits.PDEC0=0;					//Velocity Pulse reduction 1:16	

	// formula constant calculations (does not need to be calculated by PIC, but included for completeness)
	INST_CYCLE = OSCILLATOR/4;
	RPM_CONST = ((INST_CYCLE)/(ENCODER_PPR*QEI_UPDATE*VELOCITY_PULSE_DECIMATION*TIMER5_PRESCALE)) * 60;

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
	TRISA = 0b00000001;						//RA0 (AN0) is input
	i=0;									//counter initialization
	
/*	
	//==============For PWM testing purpose only=======
	//bit shifting required for PDCn (14 bit).  Actual duty cycle 12 bit.  Lower 2 bits filled with 00, so PWM edge at Q1.
			DuCyValue=0x0000<<2;				//bit shifting compensating for last two digits of PWM DC registers
			PDC1L=DuCyValue;								//upper bits discarded
			PDC1H=DuCyValue>>8;							//lower bits discarded
			PDC2L=DuCyValue;								
			PDC2H=DuCyValue>>8;
			PDC3L=DuCyValue;								
			PDC3H=DuCyValue>>8;

*/

	//commutation sequence
	do{
		
		// flash power light
		LED1 = 0;
		if (i>50)	LED1 = 1;
		LED2 = 0;
		if (((PORTC&0b00000111)==0x00) || ((PORTC&0b00000111)==0x07))LED2 = 1;



	//=================direction control==================
		if (PORTDbits.RD1 == 1)OVDCOND = fordrive[PORTC&0b00000111];
		if (PORTDbits.RD1 == 0)OVDCOND = backdrive[PORTC&0b00000111];
		

	
		//for testing purpose
		//OVDCOND = backdrive[PORTC&0b00000111];

		
	


		

		i++;
		if(i>100){	
			ADCON0bits.GO = 1;  				//Starts ADC.  This bit automatically cleared after conversion.
			i=0;}
		
		
							
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






#pragma code high_vector=0x08			//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
_asm GOTO high_ISR _endasm}				//branching to the actual ISR
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR(){
	//ADC update interrupt
	if (PIR1bits.ADIF=1){
		
		PIR1bits.ADIF=0;
			
			

		//bit shifting required for PDCn (14 bit).  Actual duty cycle 12 bit.  Lower 2 bits filled with 00, so PWM edge at Q1.
		
		DuCyValue=(0x03ff-ADRES)<<2;				//bit shifting compensating for last two digits of PWM DC registers
		PDC1L=DuCyValue;								//upper bits discarded
		PDC1H=DuCyValue>>8;							//lower bits discarded
		PDC2L=DuCyValue;								
		PDC2H=DuCyValue>>8;
		PDC3L=DuCyValue;								
		PDC3H=DuCyValue>>8;






		}
	//=======================QEI needs to be worked on majorly========================================
	//Encoder velocity update interrupt
/*	if (PIR3bits.IC1IF = 1){					//if the interrupt source is IC1 (VELR update)
												//Whenever VELR is updated, velocity is calculated
		VELREADH=VELRH;							//only lower byte occupied
		VELREADL=VELRL;							//only lower byte occupied
		VELREAD=VELREADH*0x0100+VELREADL; 		// lower byte + lower byte concatenation; total time of TMR5
		SPEED=RPM_CONST/VELREAD;				//baby, how fast are you going?  (unit in RPM)
	
*/
		/*PID feedback.  For regular motor control, D component=0.
		(Q: at what voltage will ADRES be saturated?)
		Full ADRES (0x03FF: right justified) should give full Duty Cycle (PDCn=PTPER, which is set 03FF), hence full speed.
		Since full ADRES matches full Duty Cycle, ADRES can be set directly to PDCn.  This is the desired speed
	
		Measured speed is dealt differently.  MAX_RPM is the speed at full Duty Cycle.  Let us assume that Duty Cycle varies linearly with actual RPM.  
		(This assumption will be valid since PID feedback *makes it* linear or whatever model we take.)
		Hence, SPEED_BYTE = (SPEED)(0x03FF)/MAX_RPM.  The difference between ADRES and SPEED_BYTE is the error in measured and desired speeds in binary.
		
		*/
/*		SPEED_BYTE = SPEED*0x03FF/MAX_RPM;				//SPEED_BYTE max value is 0x03FF
		Error_Spd = SPEED_REC-SPEED_BYTE;				//Error_Spd max value is 0x03FF
		if (Error_Spd>0x00F){							//no calculation done if error is negative.  See above explanation.  0x000F is the allowed error.
														//That is 1.5% error in speed.
			PropC = 2*Error_Spd;
			IntegralC = Error_Spd*VELREAD/0x1000;		//0x1000 is a arbitrary constant factor to prevent overflow (16 bit max)
			PIDvalue = PropC+IntegralC;
			if (PIDvalue>0x03FF){
				PIDvalue=0x03FF;} 						//maximum PID value allowed.
			
			PIDvalue=0x03FF-PIDvalue;					//Duty Cycle inversion.
			PIDvalue=PIDvalue<<2;						//bit shifting required for PDCn (14 bit).  Lower 2 bits filled with 00, so PWM edge at Q1.
			PDC1L=PIDvalue;								//upper bits discarded
			PDC1H=PIDvalue/0x0100;						//lower bits discarded
			PDC2L=PIDvalue;								
			PDC2H=PIDvalue/0x0100;
			PDC3L=PIDvalue;								
			PDC3H=PIDvalue/0x0100;
		}
		PIR3bits.IC1IF=0;								//re-clearing the Interrupt Flag
	}
	
*/										
}

