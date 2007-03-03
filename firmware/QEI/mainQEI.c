//coded by Minjae Kim
//Jan 2006
//Note
//Motor control through ADC works fine. (Finalized)
//Direction Implemented

// to do:
// only PWM high side
// implement encoder


#include	<p18f4431.h>
//==========Speed Calculation=================
#define		OSCILLATOR					8000000		//internal 8MHz
#define		ENCODER_PPR 				256 		//PPR of Encoder on the motor
#define 	TIMER5_PRESCALE 			8 			//Timer5 prescaler
#define 	QEI_UPDATE 					4 			//Define the QEI mode of operation.
#define 	VELOCITY_PULSE_DECIMATION 	16			//ratio
#define		MAX_RPM						5000		//assumed value of maximum rpm of the motor

//==========PI control=======================
#define		Kp							2			//Proportional Constant
#define		Ki							10			//Integral Constant




#define LED1	PORTDbits.RD4
#define LED2	PORTDbits.RD5


//Used for measured RPM caculation and ADC
unsigned char	i;	//a counter for ADC
char Errsign;

unsigned int 	VELREAD;
unsigned int 	INST_CYCLE;  
unsigned int	RPM_CONST;


unsigned int 	SPEED_BYTE;  		//measured speed in byte

//"signed", but it really doesn't matter because the code use hex and binary
unsigned int 		Error_Spd;			//desired speed - measured speed (unitless in bytes).  Must be signed
signed int 			IntComp;			//Integral Component 		
signed int			ProComp;			//Proportional Component 
signed int 			DuCyValue;			//Duty Cycle value
//========PI formula=========
// The formula:  output = Kp(Error + 1/Ki * Integral(Error))

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
	


//==================testing
	DuCyValue = -0x6000;
	if (DuCyValue>0x03FF) DuCyValue=0x03FF; 					//maximum PID value allowed.
	if (DuCyValue<0x0000) DuCyValue=0x0000;






	IntComp = 0;
	ProComp = 0;
	
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
	
	//Timer 5 intialization
	T5CON = T5CON | 0b00011000;			//Prescaler of 8
	CAP1CONbits.CAP1REN = 1;			//TMR5 reset at every capture event
	T5CONbits.TMR5ON = 1;				//TMR 5 enabled
		
	//QEI ini'n.  inefficient, but readable
	QEICONbits.VELM = 0;					//Velocity Mode enabled
	QEICONbits.QEIM2 = 1;
	QEICONbits.QEIM1 = 1;
	QEICONbits.QEIM0 = 0;					//4x update mode, reset when POSCNT=MAXCNT
	QEICONbits.PDEC1 = 1;
	QEICONbits.PDEC0 = 0;					//Velocity Pulse reduction 1:16	

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
	int beforeInt;


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

	/*
	//=======================QEI needs to be worked on majorly========================================
	//Encoder velocity update interrupt
	if (PIR3bits.IC1IF = 1){											//if the interrupt source is IC1 (VELR update)
		PIR3bits.IC1IF=0;												//re-clearing the Interrupt Flag
		
		
		VELREAD = VELRH;
		VELREAD <<= 8;
		VELREAD +=VELRL;											
		
	

		//PID feedback.  For regular motor control, D component=0.
		//Full ADRES (0x03FF: right justified) should give full Duty Cycle (PDCn=PTPER, which is set 03FF), hence full speed.
		//Since full ADRES matches full Duty Cycle, ADRES can be set directly to PDCn.  This is the desired speed
	
		//Measured speed is dealt differently.  MAX_RPM is the speed at full Duty Cycle.  Let us assume that Duty Cycle varies linearly with actual RPM.  
		//(This assumption will be valid since PID feedback *makes it* linear or whatever model we take.)
		//Hence, SPEED_BYTE = (SPEED)(0x03FF)/MAX_RPM.  The difference between ADRES and SPEED_BYTE is the error in measured and desired speeds in binary.
		
		
		SPEED_BYTE = RPM_CONST/VELREAD*0x03FF/MAX_RPM;						//RPM_CONST/VELREAD gives the RPM of the motor.  SPEED_BYTE max value is 0x03FF
		
		//Error_Spd is the absolute value of the error.  The sign of the error will be handled by Errsign
		if (ADRES>SPEED_BYTE){
		Errsign = 1;
		Error_Spd = ADRES-SPEED_BYTE;
		}
		else if (ADRES<SPEED_BYTE){
		Errsign = 0;
		Error_Spd = SPEED_BYTE-ADRES; 
		}
												
			

		if (Error_Spd>0x000F){												//maximum allowed error 0x000F
			
			beforeInt = IntComp;											//saving the previous value of int											
			if	(Errsign = 1) IntComp += Error_Spd*VELREAD/Ki;				//adding or subtracting depending on the sign
			else if (Errsign =0) IntComp -= Error_Spd*VELREAD/Ki;
					


			if ((IntComp - beforeInt)>((beforeInt>>2)+0x00FF)) IntComp = 0xFFFF;
																			//some fudge formula to detect overflow: if overflow does occur for IntComp, 
																			//IntComp - beforeInt will be 2's complement negative (meaning it will be a large value)
																			

			DuCyValue = Kp*(Error_Spd + IntComp);
			
			//if ((DuCyValue>0x03FF)&&(DuCyValue<0x7fff)) DuCyValue=0x03FF; 				
			//if (DuCyValue>0x7fff) DuCyValue=0x0000;							//greater than 0x7fff means that DuCy is negative.
																			//Theoretically, this should never happen.
			
			DuCyValue=(0x03FF-DuCyValue)<<2;								//Duty Cycle inversion.
			PDC1L=DuCyValue;									
			PDC1H=DuCyValue>>8;									
			PDC2L=DuCyValue;								
			PDC2H=DuCyValue>>8;
			PDC3L=DuCyValue;								
			PDC3H=DuCyValue>>8;
		}
										
	}

	*/
	
										
}

