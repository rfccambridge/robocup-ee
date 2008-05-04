/* Coded by Minjae Kim, January 2007
RS232 communication working perfectly.
Protocol \H<destination><address>
This code is for the auxillery kicker board
*/



#include <p18f4431.h>
#include "Bemixnet.h"
#include "pins.h"


// *** set configuration word ***
#pragma config OSC = IRCIO
#pragma config WDTEN = OFF
#pragma config LVP = OFF
#pragma config WDPS = 512



void high_ISR();	 //Interrupt Service Routine
void handleTimer0();

PacketBuffer RxPacket;
//extern PacketBuffer TxPacket;
//extern KickerControl kickCon;

unsigned char led;
#define LED_LINK	0x02
#define LED_POWER	0x01

void main(){
	unsigned char temp;



	//ANSEL0 = 0x3f;
	
	TRISA = 0X20;//
	TRISB = 0X00;
	TRISC = 0X00;
	TRISD = 0X0F;
	TRISE = 0X03;
	PORTA = 0XFF;
	PORTB = 0XFF;
	PORTC = 0XFF;
	PORTD = 0XFF;
	PORTE = 0XFF;



	// === Initialization ===
	initRx(&RxPacket);
	
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
	
	ANSEL0 = 0x3f;
	TRISA = 0x00;
	LATA = 0xff;
	
	TRISD = 0;//0b00010011;
	PORTD = 0x00;
	
	TRISE = 0x00;
	PORTE = 0x00;
	
	// it's PNP!!!
	K_KICK1 = 1;
	K_KICK2 = 1;
	
	K_CHARGE = 0;
	
	// both LEDs off
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	led = LED_POWER;

	// === Main Loop ===	
	while(1){
		LED3 = !LED3;

	if (RxPacket.done){
			// clear done flag so that don't keep looping though
			RxPacket.done = 0;

			ClrWdt();
			led = LED_LINK;

			switch (RxPacket.port){
			// === DRIBBLER ===
				// dribbler
				case 'd':
					if (RxPacket.data[0] == '0')
						DRIBBLER = 0;
					else if (RxPacket.data[0] == '1')
						DRIBBLER = 1;
					break;

			// === KICKER ===				
				// kick
				case 'K':
					K_CHARGE = 0;
					K_KICK1 = 0;
					K_KICK2 = 0;

					for (temp=0; temp<255; temp++);

					K_KICK1 = 1;
					K_KICK2 = 1;
					break;

				// enable kicker
				case 'E':
					K_KICK1 = 1;
					K_KICK2 = 1;
					
					LED1 = 0;
					K_CHARGE = 1;
				//	kickCon.enable = 1;
					break;

				// disable kicker
				case 'D':
					K_KICK1 = 1;
					K_KICK2 = 1;
					
					LED1 = 1;			
					K_CHARGE = 0;
				//	kickCon.enable = 0;
					break;

				// some other port
				default:
					break;
			}
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
		LED2 = !LED2;
	} else if (INTCONbits.TMR0IF) {
		if (led == LED_POWER)
			LED2 = LED2;//!LED2;
		else if (led == LED_LINK)
			//LED2 = 0;
		INTCONbits.TMR0IF = 0;
	} else if (PIR1bits.TXIF) {
		PIR1bits.TXIF = 0;
	}
}
#pragma


