//coded by Minjae Kim
//December 2006
//Motor control feedback


#include	<p18f4431.h>
#define		OSCILLATOR					40000000
#define		ENCODER_PPR 				256 		//PPR of Encoder on the motor
#define 	TIMER5_PRESCALE 			1 			//Timer5 prescaler
#define 	QEI_UPDATE 					4 			//Define the QEI mode of operation.
#define 	VELOCITY_PULSE_DECIMATION 	16			//ratio
#define		MAX_RPM						5000		//assumed value of maximum rpm of the motor



//Used for measured RPM caculation 
int VELREAD;
int VELREADH;    	//only lower byte occupied
int VELREADL;		//only lower byte occupied
int INST_CYCLE;  
int	RPM_CONST;
int SPEED;

int SPEED_BYTE;  	//measured speed in byte
int SPEED_REC;		//received speed (desired speed) in byte
int Error_Spd;		//desired speed - measured speed (unitless in bytes)
int IntegralC;		//Integral Component 		
int	PropC;			//Proportional Component 
int PIDvalue;		//Finaly PID correction.
void high_ISR();	 //Interrupt Service Routine

const unsigned char fordrive[8] = { 	0b00000000, //	0:error
										0b00010100, //	1
										0b00001010, //	2
										0b00001100, //	3
										0b00100001, //	4
										0b00010001, //	5
										0b00100010, //	6
										0b00000000}; //	7
const unsigned char backdrive[8] = { 	0b00000000, //	0:error
										0b00100001, //	1
										0b00010100, //	2
										0b00010001, //	3
										0b00001010, //	4
										0b00100010, //	5
										0b00001100, //	6
										0b00000000}; //	7

#pragma code high_vector=0x08			//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
_asm GOTO high_ISR _endasm}				//branching to the actual ISR
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR(){
	//ADC update interrupt
	if (PIR1bits.ADIF=1){
	SPEED_REC=ADRESH*0x0100+ADRESL;				//ADC value received as Speed Received.
	PIR1bits.ADIF=0;
	

//for testing purpose
			PIDvalue=SPEED_REC<<2;						//bit shifting required for PDCn (14 bit).  Lower 2 bits filled with 00, so PWM edge at Q1.
			PIDvalue=0x03FF-PIDvalue;
			PDC1L=PIDvalue;								//upper bits discarded
			PDC1H=PIDvalue/0x0100;						//lower bits discarded
			PDC2L=PIDvalue;								
			PDC2H=PIDvalue/0x0100;
			PDC3L=PIDvalue;								
			PDC3H=PIDvalue/0x0100;



	}
	
	//Encoder velocity update interrupt
	if (PIR3bits.IC1IF = 1){				//if the interrupt source is IC1 (VELR update)
											//Whenever VELR is updated, velocity is calculated
		VELREADH=VELRH;							//only lower byte occupied
		VELREADL=VELRL;							//only lower byte occupied
		VELREAD=VELREADH*0x0100+VELREADL; 		// lower byte + lower byte concatenation; total time of TMR5
		SPEED=RPM_CONST/VELREAD;				//baby, how fast are you going?  (unit in RPM)
	

		/*PID feedback.  For regular motor control, D component=0.
		(Q: at what voltage will ADRES be saturated?)
		Full ADRES (0x03FF: right justified) should give full Duty Cycle (PDCn=PTPER, which is set 03FF), hence full speed.
		Since full ADRES matches full Duty Cycle, ADRES can be set directly to PDCn.  This is the desired speed
	
		Measured speed is dealt differently.  MAX_RPM is the speed at full Duty Cycle.  Let us assume that Duty Cycle varies linearly with actual RPM.  
		(This assumption will be valid since PID feedback *makes it* linear or whatever model we take.)
		Hence, SPEED_BYTE = (SPEED)(0x03FF)/MAX_RPM.  The difference between ADRES and SPEED_BYTE is the error in measured and desired speeds in binary.
		Note that overshooting cannot be corrected by software since there is no "negative" duty cycle.  However, the load of the motor quickly corrects it.
		Hence, in software, when there is overshooting, we don't do anything; we let the motor die down and when it goes below desired level, we then correct 
		under-error.
		*/
		SPEED_BYTE = SPEED*0x03FF/MAX_RPM;				//SPEED_BYTE max value is 0x03FF
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
	
										
}
void main(){

	TRISC = 0xFF;						//TRISC all inputs for hall sensors (RC0-RC2).
	TRISD = 0xFF;
	//interrupts ini'n
	INTCONbits.GIE = 1;					//Global Interrupt bit enabled.  Interrupts can be used.
										//No Interrupt Priority is used.
	PIE1bits.ADIE = 0;					//ADC interrupt disabled.
	PIE3bits.IC1IE = 1;					//IC1 interrupt enabled.
	
	ADCON3bits.ADRS1 = 0;				
	ADCON3bits.ADRS0 = 0;				//ADC interrupt set when each data buffer word is written
	//TMR ini'n
	CAP1CONbits.CAP1REN = 1;			//TMR5 reset at every capture event
	T5CONbits.TMR5ON = 1;				//TMR 5 enabled; other settings are left to default
		
	//inefficient, but readable
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
	ADCON2bits.ADFM = 1;					//right justified ADRES value (10 bit)
	ADCON3=0b00000000;						//no FIFO. All triggers disabled.	
	ADCON0bits.ADON = 1;					//ADC on
	ANSEL0bits.ANS0 = 1;					//AN0 (RA0) is analog input
	TRISA = 0b00000001;						//RA0 (AN0) is input
	ADCON0bits.ACONV = 1;					//continuous mode
	ADCON0bits.GO=1;
	//commutation sequence
	do{

		// direction control
		if (PORTDbits.RD1)
			OVDCOND = fordrive[PORTC&0b00000111];		// CCW
		else
			OVDCOND = backdrive[PORTC&0b00000111];		// CW

	SPEED_REC=ADRESH*0x0100+ADRESL;				//ADC value received as Speed Received.
	PIR1bits.ADIF=0;
	

//for testing purpose
			PIDvalue=SPEED_REC<<2;						//bit shifting required for PDCn (14 bit).  Lower 2 bits filled with 00, so PWM edge at Q1.
			//PIDvalue=0x03FF-PIDvalue;
			PDC1L=PIDvalue;								//upper bits discarded
			PDC1H=PIDvalue/0x0100;						//lower bits discarded
			PDC2L=PIDvalue;								
			PDC2H=PIDvalue/0x0100;
			PDC3L=PIDvalue;								
			PDC3H=PIDvalue/0x0100;
	}while(1);

	//default settings included for completeness
	//ADCON0bits.ADCONV = 0;				//Single shot mode.(Default)
		
	//ADCON0bits.ACSCH = 0; 				//single-channel mode(default)
	//ADCON0bits.ACMOD1 = 0;				
	//ADCON0bits.ACMOD0 = 0; 				//using Group A(default)  Group A: AN0, AN4, AN8  (AN0 selected by default)
											//AN0 is for speed information.

	//ADCON1bits.VCFG1 = 0;					
	//ADCON1bits.VCFG0 = 0;					//AVDD and AVSS used as reference voltage(default)
	//ADCON1bits.FIFOEN = 0; 				// don't need multiple level addressing(default)

}
