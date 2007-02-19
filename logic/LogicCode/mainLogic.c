/* Coded by Minjae Kim, January 2007
RS232 communication working perfectly.
Protocol \H<destination><address>
This code is for the main logic pic.
Power PWM: 			RD7			RB1 		RB3 		RB4
					motor 0 	motor 1		motor 2		motor3

Directional I/O: 	RB0			RB2			RB5 		RD6
					motor 0		motor 1		motor 2		motor 3
					low -> clockwise  high->counterclockwise (from observer)


Assumptions
Max speed is assumed to be 5000 RPM
Baud rate is 9600

Note
ASCII 0x26 = "&"
	  0x2A = "*"
Testing
RC0 is used as test output
*/

/* === PINOUT ===
* RA0
* RA1
* RA2
* RA3
* RA4		kick 1
* RA5		kick 2
* RA6/OSC	40 MHz XTAL
* RA7/OSC	40 MHz XTAL
* RB0		dir 1
* RB1/PWM1	speed 1
* RB2		dir 2
* RB3/PWM3	speed 2
* RB4/PWM5	speed 3
* RB5		dir 3
* RB6		ICSP
* RB7		ICSP
* RC0		x
* RC1
* RC2
* RC3
* RC4
* RC5
* RC6
* RC7
* RD0		address 1
* RD1		address 2
* RD2		LED 1
* RD3		LED 2
* RD4		address 3
* RD5		discharge
* RD6		dir 4
* RD7/PWM7	speed4
* RE0		kick 3
* RE1		kick 4
* RE2		charge
*/



#include <p18f4431.h>
#include "4Enet.h"
#include "kicker.h"
#include "pins.h"


void high_ISR();	 //Interrupt Service Routine
void handleTimer0();

PacketBuffer RxPacket;
extern PacketBuffer TxPacket;

extern KickerControl kickCon;



void main(){

	// === Initialization ===
	initRx(&RxPacket);
	initKicker();
	//======oscillator configuration: internal used======
	OSCCON = OSCCON | 0b01110000;			//internal oscillator 8MHz

	// initialize timer0 for kicker
	T0CON = 0b10001000;
	INTCONbits.TMR0IE = 1;	

	//Power PWM.  PWM 1,3,5,7 used.
	PWMCON0=0b01110000; 						 //Only Odd PWM pins enabled (default)
	TRISB = 0b11011010;							//5,2,0 for directional I/O outputs
	PTPERH = 0x00;
	PTPERL = 0xFF;								//Setting PWM Period to 8 bits
	


	TRISD = 0b00000000;
	PORTD = 0b00000000;


	RxPacket.data[0]=0xff;
	RxPacket.data[1]=0xff;
	RxPacket.data[2]=0xff;
	RxPacket.data[3]=0xff;
	PDC0H=RxPacket.data[0]>>6;			//Duty cycle for PWM1 -> motor 0
	PDC0L=RxPacket.data[0]<<2;
	PDC1H=RxPacket.data[1]>>6;			//Duty cycle for PWM3 -> motor 1
	PDC1L=RxPacket.data[1]<<2;
	PDC2H=RxPacket.data[2]>>6;			//Duty cycle for PWM5 -> motor 2
	PDC2L=RxPacket.data[2]<<2;
	PDC3H=RxPacket.data[3]>>6;			//Duty cycle for PWM7 -> motor 3
	PDC3L=RxPacket.data[3]<<2;
	PTCON1bits.PTEN = 1;					//PWM timer enabled



	// === Main Loop ===	
	while(1){

		LED2 = RxPacket.done;

		if (RxPacket.done){

			// clear done flag so that don't keep looping though
			RxPacket.done = 0;

			switch (RxPacket.port){

			// === WHEELS ===
				case 'w':        	//wheel speed and direction control
					//give signal out to the brushless pic	
					//0-5v corresponds 0-100% of speed, which is 0-5000 RPM
					
					
					PORTBbits.RB0 = ((RxPacket.data[4]&0b00000001)==1); 					//checking motor 0 (RB bit 0)	RB0
					PORTBbits.RB2 = ((RxPacket.data[4]&0b00000010)==2);
					PORTBbits.RB5 = ((RxPacket.data[4]&0b00000100)==4);
					PORTDbits.RD6 = ((RxPacket.data[4]&0b00001000)==8); 
											
					//speed info by PWM  works fine
					PDC0H=RxPacket.data[0]>>6;			//Duty cycle for PWM1 -> motor 0
					PDC0L=RxPacket.data[0]<<2;
					PDC1H=RxPacket.data[1]>>6;			//Duty cycle for PWM3 -> motor 1
					PDC1L=RxPacket.data[1]<<2;
					PDC2H=RxPacket.data[2]>>6;			//Duty cycle for PWM5 -> motor 2
					PDC2L=RxPacket.data[2]<<2;
					PDC3H=RxPacket.data[3]>>6;			//Duty cycle for PWM7 -> motor 3
					PDC3L=RxPacket.data[3]<<2;
				
					PTCON1bits.PTEN = 1;					//PWM timer enabled
		
					break;
			
			// === DRIBBLER ===
				// dribbler
				case 'd':
					// set speed using CCP module
					// set direction
					break;

			// === KICKER ===				
				// kick
				case 'K':
					kickCon.kick1 = ((RxPacket.data[0] & 0x01) == 0x01);
					kickCon.kick2 = ((RxPacket.data[0] & 0x02) == 0x02);
					kickCon.kick3 = ((RxPacket.data[0] & 0x04) == 0x04);
					kickCon.kick4 = ((RxPacket.data[0] & 0x08) == 0x08);
					kickCon.kick = 1;
					break;

				// enable kicker
				case 'E':
					kickCon.enable = 1;
					break;

				// disable kicker
				case 'D':
					kickCon.enable = 0;
					break;

				default:
					break;
			}

										//	PORTDbits.RD0 = RxPacket.done;

		}
	
		}
	}






#pragma code high_vector=0x08				//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
	_asm GOTO high_ISR _endasm				//branching to the actual ISR
}
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR()
{
	if (PIR1bits.RCIF) {
		handleRx(&RxPacket);	
		PIR1bits.RCIF = 0;
	} else if (INTCONbits.TMR0IF) {
//		handleKicker();
		INTCONbits.TMR0IF = 0;
	} else if (PIR1bits.TXIF) {
	//	handleTx();
	//	PIR1bits.TXIF = 0;
	}
}
#pragma


