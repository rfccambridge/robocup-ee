/* Protocol \H<destination><address>
This code is for the auxillery kicker board
*/
#include <p18f4431.h>
#include <ADC.h>
#include "Bemixnet.h"
#include "pins.h"

// *** set configuration word ***
#pragma	config OSC      = IRCIO		// internal oscillator
#pragma	config LVP 	    = OFF		// low voltage programming
#pragma	config WDTEN    = OFF   	// watchdog timer
#pragma	config WDPS     = 256   	// watchdog timer prescaler
#pragma config BOREN    = ON    	// brown out reset oned
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

void blink();
void blink2();

void high_ISR();	 //Interrupt Service Routine
void handleTimer0();

PacketBuffer RxPacket;
//extern PacketBuffer TxPacket;
//extern KickerControl kickCon;

unsigned char led;
unsigned int capV = 0;
unsigned int battV = 0;
int adcTemp;
int adcVH;
int adcVL;
#define LED_LINK	0x02
#define LED_POWER	0x01

void main(){

	unsigned char j;//for a wait loop when kicking
	unsigned int kick_counter = 0;
//	double adc_result = 10;
	int test_adc = 0;
	int test_old = 0;
	int k=0;
	int i=0;
//	int bb = 0;
//	int ii = 0;
//	int iii = 0;

	//int breakbeam_count = 0;


	//stuff for hardcoded simple PWM
	//int fakePWM_T = 30;	//pwm PERIOD
	//int fakePWM_High = 0;//# of counts period is high. Controls the duty cycle, 0 is off.
	//int fakePWM_count = 0;	//count for keeping track of thing
//	int dribblerState = 0;					// 0 is inactive. 1 is active

	//real dribbler PWM duty cycle (0 to 0xff)
	unsigned int dribbler_duty = 0;
	//received dribbler speed (0x30 + (0 to 9))
	char dribbler_speed = 0; 

	//if true then it kicks as soon as it sees the ball
	int breakBeam = 0;

	//if true then it is in the state when it kicks if Full charged and breakbeam is broken
	int fullKick=0;

	//if true then charge to some target voltage RxPacket.data[0] but kick as long as cap voltage is greater than RxPacket.data[1]
	int minimumKick=0;
	int thresholdV=0;
	
	//maintain charge on capacitors (true when most recent command is charge, 
	//false when most recent command is discharge, kick, or stop charge)
	int k_maintain = 0;

	int maintainV = 0;
	//int confirmCharge = 0;
	//unsigned int lastV = 0;

	//TRISA = 0x20;
	//LATA = 0xff;

	// === Initialization ===
	initRx(&RxPacket);

	

	// *** 8 MHz clock ***
	OSCCON = 0b01110000;

	// *** Initialize PWM ***
	PTCON0 = 0x00;
	PTCON1 = 0x80;						// PTMR enabled, counts up
	PWMCON0 = 0b01001111;				// PWM0-5 enabled, independent mode. Only PWM0 (old breakbeam LED), PWM4 (dribbler) are connected
	PWMCON1 = 0x00;
	PTPERH = 0x00;						// 8 bit duty cycle, 31.25KHz (PWM freq) @ 8MHz (Fosc)
	PTPERL = 0x3f;
	
	// *** Configure IO ***

	ANSEL0 = 0xff;
	ANSEL1 = 0x00;
	TRISA = 0b11110000;
	TRISB = 0b11001010;							//2,4,7,8 inputs rest outputs
	TRISC = 0b11110001;
	TRISD = 0x1F;
	TRISE = 0b111;

	//A/D
	ADCON1 = 0b00000000;
	ADCHS = 0b00010000;
	ADCON0bits.ACMOD0 = 1;
	ADCON0bits.ACSCH = 0;
	ADCON0bits.ACONV = 1;
	ADCON2 = 0b00111000;
	ADCON0bits.ADON = 1;
	PIR1bits.ADIF = 0;	
	ADCON0bits.GO = 1;
	

	// *** initialize timer0 ***
	// 8 bit mode
	// prescaler   period
	// 110         16.4ms
	// 101          8.2ms
	// 100          4.1ms

	T0CON = 0b11000101; //enabled, 8bit, internal clock, low->high transition, Use of prescaler, 1:64
	INTCON = 0b11100000; 



	//Setting up the analog input for the battery voltage
	/*ADCON0 = 0b00100111;//coninuous, single channel, simultaneous group A and group B, start cycle, a/d on
	ADCON1 = ADCON1&&0b00111111;//00 =VREF+ = AVDD, VREF- = AVSS, (AN2 and AN3 are Analog inputs or Digital I/O)
	ADCON2 = 0b0100 ;//left justified highbit = data low bit = data0000*/

	MBLED1 = 1;
	//MBLED2 = 1; only 1 LED on motherboard
	//OpenADC(ADC_FOSC_RC & ADC_RIGHT_JUST & ADC_0_TAD,BattV & ADC_INT_ON, 0);
	//ADCON1 =0x00;

	
	// it's PNP!!!
	K_KICK1 = 1;
	//K_KICK2 = 1; 2nd power of kicking not used currently
	K_CHIP1 = 1;
	//K_CHIP2 = 1; 2nd power of chipping is not used currently
	K_DISCHARGE = 0;
	K_CHARGE = 0;
	DRIBBLER = 0;
	
	// all LEDs off
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	//Mother board LEDs on
	blink();

	LED1 = 0;


		OVDCOND = 0xff;
		OVDCONS = 0xff;
		// set duty cycle (8 bits)
		//PDC0H = 0x00;
		//PDC0L = 0x59;
		//PDC1H = 0x00;
		//PDC1L = 0x00;
		PDC2H = 0x00; //for dribbler
		PDC2L = 0x00; //for dribbler
	// === Main Loop ==	
	while(1){

		unsigned short i;

		adcVL = ADRESL;
		adcVH = ADRESH;
		capV = adcVH << 8;
		capV += adcVL;
		capV = 1100 - (capV >> 6); //300 more than actual capV to prevent rolling over

		//OVDCOND = 0xff; //only pin not PWMing is one to dribbler controller
				

		/* Monitoring battery voltage - does not work in conjunction with cap voltage
		if (battT == 0)
		{
			ADCON0bits.GO = 0;
			ADCHS = 0b01000000;
			ADCON0bits.ACONV = 0;
			ADCON0bits.ACMOD = 3;

			PIR1bits.ADIF = 0;
    		ADCON0bits.GO = 1;
			for (i=0; i<0xFF; i++);

			adcVL = ADRESL;
			adcVH = ADRESH;
			battV = adcVH << 8;
			battV += adcVL;

			ADCON0 = 0b00100100;
			ADCHS = 0b00010000;
			ADCON1 = 0b00000000;
			ADCON2 = 0b00111000;
			ADCON0bits.ADON = 1;
			for (i=0; i<0xFF; i++);
		
			PIR1bits.ADIF = 0;
		    ADCON0bits.GO = 1;
		}
		battT += 1;
		*/

		LED3 = BBEAM;  // Breakbeam Check - If broken, then LED3 turns on - adw
		LED1 = !LED1;
		/*For old breakbeam
		if (breakbeam_count <=30){
			OVDCOND = 0xff;
			breakbeam_count++;
		}
		else if (breakbeam_count <= 100){
			OVDCOND = 0xfe;
			breakbeam_count++;
		} else
			breakbeam_count = 0;

 		if (fakePWM_count <= fakePWM_High){
			OVDCONS = 0xff;//DRIBBLER = 1;
			MBLED1 = 0;
		}
		else{
			OVDCONS = 0x00;//DRIBBLER = 0;
			//MBLED2 = 0; only 1 LED on motherboard
		}
		if (fakePWM_count >= fakePWM_T){
			//start a new period
			fakePWM_count = 0;
		}
		fakePWM_count++;
		*/

		if (RxPacket.done){
			// clear done flag so that don't keep looping though
			RxPacket.done = 0;

			ClrWdt();
			//led = LED_LINK;

			switch (RxPacket.port){
			// === DRIBBLER ===
				// dribbler
				
				case 'd':
					dribbler_speed = RxPacket.data[0] - 0x30;
					switch( dribbler_speed ){//set one of a number of duty cycles
						case 0:
							//fakePWM_High = 0;//fakePWM_T;
							dribbler_duty = 0;
							break;
						case 1:
							//fakePWM_High = 3;//fakePWM_T/10;
							dribbler_duty = 25;
							break;
						case 2:
							//fakePWM_High = 6;//fakePWM_T/5;
							dribbler_duty = 51;
							break; 
						case 3:
							//fakePWM_High = 9;//fakePWM_T*3
							dribbler_duty = 77;
							break;
						case 4:
							//fakePWM_High = 12;//fakePWM_T*2/5;
							dribbler_duty = 102;
							break;
						case 5:
							//fakePWM_High = 15;//fakePWM_T/2;
							dribbler_duty = 128;
							break;
						case 6:
							//fakePWM_High = 18;//fakePWM_T*6/10;
							dribbler_duty = 153;
							break;
						case 7:
							//fakePWM_High = 21;//fakePWM_T*7/10;
							dribbler_duty = 179;
							break;
						case 8:
							//fakePWM_High = 24;//fakePWM_T*8/10;
							dribbler_duty = 204;
							break;
						case 9:
							//fakePWM_High = 27;//fakePWM_T*9/10;
							dribbler_duty = 230;
							break;
						case 10:
							//fakePWM_High = 27;//fakePWM_T*9/10;
							dribbler_duty = 255;
							break;
						default:
							break;					
					}
					PDC2L = dribbler_duty & 0xfc; //Q-clock = 0b00
					break;

				case 'k': //Kick
					K_CHARGE = 0;//stop charging while kicking.	
					K_DISCHARGE = 0;
					for (i=0; i<0xFF; i++);
					K_KICK1 = 0;
					//K_KICK2 = 0; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					breakBeam = 0; //just in case a kick was forced.
					k_maintain = 0; //do not maintain full charge on capacitors
					
					
					//OVDCOND = 0xfe; //reset breakbeam LED
					for (k=0; k<1000; k++)
					{
						for (i=0; i<0xFF; i++)
						{
							LED1 ^= 1;
						}
					}
					K_KICK1 = 1;
					//OVDCOND = 0xff;
					

					break;

				case 'c': //Charge
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;
					k_maintain = 1; //do maintain full charge on capacitors
					maintainV = 250;
					break;

				case 'p': //Discharge
					K_CHARGE = 0;//stop charging while kicking.	
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_DISCHARGE = 1;
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					K_DISCHARGE = 0;
					k_maintain = 0; //do not maintain full charge on capacitors
					break;
				case 's': //Stop Charging
					K_CHARGE = 0;//stop charging while kicking.	
					K_DISCHARGE = 0;
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					breakBeam = 0; //don't want to kick anymore.
					k_maintain = 0; //do not maintain full charge on capacitors
					break;

				case 'b': //Starts charging the kicker and sets the breakbeam flag, so it will kick as soon as it sees the ball.
				
					maintainV = 250;
					//OVDCOND = 0xef;
					//Start Charging
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;

					//set the flag
					breakBeam = 1;
                    
                    k_maintain = 1; //do maintain full charge on capacitors
					
					break;
				
				//Breakbeam kick with full charge restriction
				case 'f': //It waits until the capacitor is charged and the breakbeam is broken to kick
					
					maintainV = (int)RxPacket.data[0] * 10;
					if (maintainV > 250)
						maintainV = 250;

					//OVDCOND = 0xef;
					//Start Charging
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;
					
					//set the flag
					fullKick = 1;
                    
                    k_maintain = 1; //do maintain full charge on capacitors
					
					break;

				//variable charge (supply voltage 1<=V<=25 where the robot charges and maintains
				//the caps at 10*V volts)
				case 'v':
					maintainV = (int)RxPacket.data[0] * 10;
					if (maintainV > 250)
						maintainV = 250;

					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;
					k_maintain = 1; //do maintain full charge on capacitors
					break;

				//minimum charge kick
				//charge to some target voltage (RxPacket.data[0]) and kick above some minimum voltage (RxPacket.data[1])
				case 'm':
					minimumKick = 1;
					maintainV = (int)RxPacket.data[0] * 10;
					if (maintainV > 250)
						maintainV = 250;
					thresholdV = (int)RxPacket.data[1] * 10;
					if (thresholdV > 250)
						thresholdV = 250;
					K_KICK1 = 1;
					//K_KICK2 = 1; 2nd power of kicking not used currently
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;
					k_maintain = 1; //do maintain full charge on capacitors
					break;


				// some other port
				default:
					//LED3 = !LED3;
					//LED3 = PORTBbits.RB2;
					break;
			}
		}

		//tests to see if cap voltage is above threshold voltage
		//if so, enables break beam kicking while continuing to charge
		if (minimumKick == 1 && capV > thresholdV + 20 + 300){
			breakBeam = 1;
			minimumKick = 0;
		}
		
		//tests to see if charging cycle is complete in order to
		//turn off charging
		if (K_CHARGE == 1 && capV > maintainV + 20 + 300){
			K_CHARGE = 0;
			//if we set a breakbeam kick when fully charged, set the breakbeam flag
			if (fullKick == 1)
			{
				breakBeam = 1;
				fullKick = 0;
			}
			else if (minimumKick == 1)
			{
				breakBeam = 1;
				minimumKick = 0;
			}
		}
		
		/*
		//try to turn charging on again if we don't see an increase in cap voltage
		//test every 10 cycles
		if (confirmCharge == 10 && k_maintain == 1){
			if (capV <= lastV + 10){
				K_CHARGE = 0;
				K_KICK1 = 1;
				//K_KICK2 = 1; 2nd power of kicking not used currently
				for (i=0; i<0xFF; i++);
				K_CHARGE = 1;
				K_DISCHARGE = 0;
				lastV = capV;
			} else {
				confirmCharge = 0;
			}
		} else if (confirmCharge > 0) {
			confirmCharge += 1;
		}
		*/

        //tests to see if voltage has fallen below maintain value to
        //restart charging, if necessary
        if (k_maintain == 1 && K_CHARGE == 0 && capV < maintainV - 20 + 300){
            K_CHARGE = 0;
			K_KICK1 = 1;
			//K_KICK2 = 1; 2nd power of kicking not used currently
			for (i=0; i<0xFF; i++);
			K_CHARGE = 1;
			K_DISCHARGE = 0;

			//used to confirm that charging was actually turned on
			//lastV = capV;
			//confirmCharge = 1;
        }	

		//Check if we need to kick
		if(BBEAM == 1 && breakBeam){
			//LED3= 0;
			breakBeam = 0;
			K_CHARGE = 0;	//stop charging while kicking
			K_DISCHARGE = 0;
			for (i=0; i<0xFF; i++);
			K_KICK1 = 0;
			//K_KICK2 = 0; 2nd power of kicking not used currently
			for (i=0; i<0xFF; i++);
			K_KICK1 = 1;
			k_maintain = 0; //do not maintain full charge on capacitors
			//K_KICK2 = 1; 2nd power of kicking not used currently
			
			
			//OVDCOND = 0xfe; //reset breakbeam LED
			for (k=0; k<1000; k++)
			{
				for (i=0; i<0xFF; i++)
				{
					LED1 ^= 1;
				}
			}
			K_KICK1 = 1;
			//OVDCOND = 0xff;
			
		}

	}
}


void blink(){
	unsigned short i;
	LED1 = 0; 
	LED2 = 0; 
	LED3 = 0;
	for (i=0; i<0xFE; i++)ClrWdt();
	LED1 = 1; 
	LED2 = 1; 
	LED3 = 1;
	for (i=0; i<0xFE; i++)ClrWdt();
}

/*void blink2(){
	unsigned short i;
	MBLED1 = 0;
	MBLED2 = 0;
	for (i=0; i<0xFF; i++)ClrWdt();
	MBLED1 = 1;
	MBLED2 = 1;
	for (i=0; i<0xFF; i++)ClrWdt();
}*/
	



#pragma code high_vector=0x08				//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm				//branching to the actual ISR
}
#pragma code
//Interrupt Service Routine (the real one)
#pragma interrupt high_ISR			 
void high_ISR()
{
	if (INTCONbits.TMR0IE && INTCONbits.TMR0IF) {
	//	LED1 = 0;
		INTCONbits.TMR0IF = 0;
		//handleQEI(&TxPacket);
	//	LED1 = 1;
	} else if (PIE1bits.RCIE && PIR1bits.RCIF) {
		LED2 = !LED2;
		PIR1bits.RCIF = 0;
		handleRx(&RxPacket);
		
	} else if (PIE1bits.TXIE && PIR1bits.TXIF) {
	
		PIR1bits.TXIF = 0;
		//handleTx(&TxPacket);
	}
}
#pragma
