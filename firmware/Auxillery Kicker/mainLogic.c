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

void blink();
void blink2();

void high_ISR();	 //Interrupt Service Routine
void handleTimer0();

PacketBuffer RxPacket;
//extern PacketBuffer TxPacket;
//extern KickerControl kickCon;

unsigned char led;
#define LED_LINK	0x02
#define LED_POWER	0x01

void main(){
	unsigned char j;//for a wait loop when kicking
	unsigned int kick_counter = 0;
	double adc_result = 10;
	int test_adc = 0;
	int test_old = 0;
//	int bb = 0;
	int ii = 0;
	int iii = 0;


	//stuff for hardcoded simple PID
	int fakePWM_T = 30;	//pwm PERIOD
	int fakePWM_High = 0;//# of counts period is high. Controls the duty cycle, 0 is off.
	int fakePWM_count = 0;	//count for keeping track of things
//	int dribblerState = 0;					// 0 is inactive. 1 is active

	//if true then it kicks as soon as it sees the ball
	int breakBeam = 0;

	//TRISA = 0x20;
	//LATA = 0xff;

	// === Initialization ===
	initRx(&RxPacket);

	
	//======oscillator configuration: internal used======
	OSCCON = OSCCON | 0b01110000;			//internal oscillator 8MHz
	
	// initialize timer0 for kicker
	T0CON = 0b10001000;
	INTCONbits.TMR0IE = 0;	
	
	//Enable PWM for the dribbler
/*	PWMCON0= 0x00;//0b01001111; 		//enable pwm0-5, because can't just enable 4
										//set all pwm outputs independent of others
	PTCON0 = 0x00;// 00 is default, which is fine
	PTCON1 = 0x80;//maybe need 0x80
	PTPERH = 0x00;
	PTPERL = 0xFF;		*/						//Setting PWM Period to 8 bits
	




	TRISB = 0b11001010;							//2,4,7,8 inputs rest outputs

	ANSEL0 = 0x3f;
	TRISA = 0b11100000;
	//LATA = 0xff;	
	TRISC = 0b11110001;
	TRISD = 0x1F;
	//PORTD = 0x00;	
	TRISE = 0x03;
	//PORTE = 0xFF;

	//Setting up the analog input for the battery voltage
	/*ADCON0 = 0b00100111;//coninuous, single channel, simultaneous group A and group B, start cycle, a/d on
	ADCON1 = ADCON1&&0b00111111;//00 =VREF+ = AVDD, VREF- = AVSS, (AN2 and AN3 are Analog inputs or Digital I/O)
	ADCON2 = 0b0100 ;//left justified highbit = data low bit = data0000*/

	MBLED1 = 1;
	MBLED2 = 1;
	//OpenADC(ADC_FOSC_RC & ADC_RIGHT_JUST & ADC_0_TAD,BattV & ADC_INT_ON, 0);
	//ADCON1 =0x00;

	
	// it's PNP!!!
	K_KICK1 = 1;
	K_KICK2 = 1;
	K_CHIP1 = 1;
	K_CHIP2 = 1;
	K_DISCHARGE = 0;
	K_CHARGE = 0;
	DRIBBLER = 0;
	
	// all LEDs off
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	//Mother board LEDs on
	//MBLED1 = 0;
	//MBLED2 = 0;
	//led = LED_POWER;

	//LED1 = 0;
	//LED1 = 0;

	blink();

	LED1 = 0;
	
	// === Main Loop ===	
	while(1){
		
		unsigned short i;

		LED3 = PORTBbits.RB3;  // Breakbeam Check - If broken, then LED3 turns on - adw

	//	LED2 = PORTDbits.RD0;
	//	LED3 = PORTDbits.RD1;
		//LED1 = PORTDbits.RD1;
//		LED1 = !LED1;//!LED3;

		//Battery Info
/*
		SetChanADC(BattV);    //set ADC input to pin 2
		ConvertADC();           //perform ADC conversion
		while(BusyADC());       //wait for result
*/
		//adc_result = (double)(ReadADC()); //stores ADC result into a predefined integer
		//adc_result = adc_result*10.4*5.0/(2.2*1023.0);
/*
		if(adc_result < 12.0*(.24*.05 + .96)){
			MBLED1 = 0;
			MBLED2 = 0;
		} else if(adc_result < 12.0*(.24*.20 + .96)) {
			MBLED1 = 1;
			MBLED2 = 0;
		} else if(adc_result < 12.0*(.24*.40 + .96)) {
			MBLED1 = 0;
			MBLED2 = 1;
		} else {
			MBLED1 = 1;
			MBLED2 = 1;
		}
*/

	/*	test_adc = ReadADC();

		if((test_adc & 0b00000001) != (test_old & 0b00000001)) {
			LED1 = !LED1;
		}
		if((test_adc & 0b00000010) != (test_old & 0b00000010)) {
			LED2 = !LED2;
		}
		if((test_adc & 0b00000100) != (test_old & 0b00000100)) {
			LED3 = !LED3;
		}
		if((test_adc & 0b00001000) != (test_old & 0b00001000)) {
			MBLED1 = !MBLED1;
		}
		if((test_adc & 0b00010000) != (test_old & 0b00010000)) {
			MBLED2 = !MBLED2;
		}

		test_old = test_adc;
*/



		if (fakePWM_count <= fakePWM_High){
			DRIBBLER = 1;
			MBLED1 = 0;
		}
		else{
			DRIBBLER = 0;
			MBLED2 = 0;
		}
		if (fakePWM_count >= fakePWM_T){
			//start a new period
			fakePWM_count = 0;
		}
		fakePWM_count++;

		if (RxPacket.done){
			// clear done flag so that don't keep looping though
			RxPacket.done = 0;

			ClrWdt();
			//led = LED_LINK;

			switch (RxPacket.port){
			// === DRIBBLER ===
				// dribbler
				
				case 'd':
					switch( RxPacket.data[0]){//set one of a number of duty cycles
						case '0':
							fakePWM_High = 0;//fakePWM_T;
							break;
						case '1':
							fakePWM_High = 3;//fakePWM_T/10;
							break;
						case '2':
							fakePWM_High = 6;//fakePWM_T/5;
							break;
						case '3':
							fakePWM_High = 9;//fakePWM_T*3
							break;
						case '4':
							fakePWM_High = 12;//fakePWM_T*2/5;
							break;
						case '5':
							fakePWM_High = 15;//fakePWM_T/2;
							break;
						case '6':
							fakePWM_High = 18;//fakePWM_T*6/10;
							break;
						case '7':
							fakePWM_High = 21;//fakePWM_T*7/10;
							break;
						case '8':
							fakePWM_High = 24;//fakePWM_T*8/10;
							break;
						case '9':
							fakePWM_High = 27;//fakePWM_T*9/10;
							break;
						default:
							break;
					}

			// === KICKER ===				
				// kick
/*				case 'L'://for testing
					K_KICK1 = 0;
					K_KICK2 = 0;	
					K_CHIP1	 = 0;
					K_CHIP2	 = 0;
					K_CHARGE = 0;
					K_DISCHARGE	 = 0;
					LED3 = 1;
					break;
				case 'H'://for testing
					K_KICK1 = 1;
					K_KICK2 = 1;	
					K_CHIP1	= 1;
					K_CHIP2	= 1;
					K_CHARGE = 1;
					K_DISCHARGE	 = 1;
					LED3 =0;
					break;
					
				case 'B':		
					LED3 = 1;
					TRISDbits.TRISD7 = 1;
					//K_CHARGE = 1; // keep charging until we actually kick
					K_KICK1 = 1;  // stop kicking
					K_KICK2 = 1;  // stop kicking
					kick_counter = 1000000000000;
					break;
				
				case 'K':
					LED3 = 1;
					TRISDbits.TRISD7 = 0;
					K_CHARGE = 0;//stop charging while kicking.	
					for (i=0; i<0xFF; i++);
					K_KICK1 = 0;
					K_KICK2 = 0;
					for (i=0; i<0xFF; i++);
					K_KICK1 = 1;
					K_KICK2 = 1;
					break;
					

				// enable kicker - begin charging, don't kick
				case 'E':
					K_DISCHARGE = 0;
					K_KICK1 = 1;
					K_KICK2 = 1;
					TRISDbits.TRISD7 = 1;//set as an input so Vc on the lt1070 floats.
					K_CHARGE = 1;
					LED3 = 0;
				//	kickCon.enable = 1;
					break;

				// disable kicker - stop kicking
				case 'D'://STOP CHARGING
					TRISDbits.TRISD7 = 0;
					K_CHARGE = 0;
					K_DISCHARGE = 0;
					K_KICK1 = 1;
					K_KICK2 = 1;
					 
					LED3 = 1;	
				//	kickCon.enable = 0;
				case 'Q':
					TRISDbits.TRISD7 = 0;
					K_CHARGE = 0;
					K_DISCHARGE = 1;
					K_KICK1 = 1;
					K_KICK2 = 1;
				    break;
					*/
				case 'k': //Kick
					K_CHARGE = 0;//stop charging while kicking.	
					K_DISCHARGE = 0;
					for (i=0; i<0xFF; i++);
					K_KICK1 = 0;
					K_KICK2 = 0;
					for (i=0; i<0xFF; i++);
					K_KICK1 = 1;
					K_KICK2 = 1;
					breakBeam = 0; //just in case a kick was forced.
					break;

				case 'c': //Charge
					K_KICK1 = 1;
					K_KICK2 = 1;
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;
					break;

				case 'p': //Discharge
					K_CHARGE = 0;//stop charging while kicking.	
					K_KICK1 = 1;
					K_KICK2 = 1;
					for (i=0; i<0xFF; i++);
					K_DISCHARGE = 1;
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					for (i=0; i<0xFF; i++);
					K_DISCHARGE = 0;
					break;
				case 's': //Stop Charging
					K_CHARGE = 0;//stop charging while kicking.	
					K_DISCHARGE = 0;
					K_KICK1 = 1;
					K_KICK2 = 1;
					breakBeam = 0; //don't want to kick anymore.
					break;

				case 'b': //Starts charging the kicker and sets the breakbeam flag, so it will kick as soon as it sees the ball.
					//Start Charging
					K_KICK1 = 1;
					K_KICK2 = 1;
					for (i=0; i<0xFF; i++);
					K_CHARGE = 1;
					K_DISCHARGE = 0;

					//set the flag
					breakBeam = 1;


				// some other port
				default:
					//LED3 = !LED3;
					LED3 = PORTBbits.RB2;
					break;
			}
		}


		//Check if we need to kick
		if(PORTBbits.RB3 == 0 && breakBeam){
			breakBeam = 0;
			K_CHARGE = 0;	//stop charging while kicking
			K_DISCHARGE = 0;
			for (i=0; i<0xFF; i++);
			K_KICK1 = 0;
			K_KICK2 = 0;
			for (i=0; i<0xFF; i++);
			K_KICK1 = 1;
			K_KICK2 = 1;
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
	//	LED3 = 0;
		PIR1bits.TXIF = 0;
		//handleTx(&TxPacket);
	//	LED3 = 1;
	} 
}
#pragma


/*void high_ISR()
{
	if (PIR1bits.RCIF) {
		handleRx(&RxPacket);
		PIR1bits.RCIF = 0;
	//	LED2 = !LED2;
	//} else if (INTCONbits.TMR0IF) {
	//	if (led == LED_POWER)
	//		LED2 = !LED2;
	//	else if (led == LED_LINK)
	//		//LED2 = 0;
	//	INTCONbits.TMR0IF = 0;
	} else if (PIR1bits.TXIF) {
		PIR1bits.TXIF = 0;
	}
}*/