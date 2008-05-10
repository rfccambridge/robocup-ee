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

	//TRISA = 0x20;
	//LATA = 0xff;

	blink();
	// === Initialization ===
	initRx(&RxPacket);
	blink();
	
	//======oscillator configuration: internal used======
	OSCCON = OSCCON | 0b01110000;			//internal oscillator 8MHz
	
	// initialize timer0 for kicker
	T0CON = 0b10001000;
	INTCONbits.TMR0IE = 0;	
	
	//Power PWM.  PWM 1,3,5,7 used.
	PWMCON0= 0x00;//0b01110000; 						 //Only Odd PWM pins enabled (default)
	TRISB = 0b11001010;							//5,2,0 for directional I/O outputs
	PTPERH = 0x00;
	PTPERL = 0xFF;								//Setting PWM Period to 8 bits
	
	ANSEL0 = 0x3f;
	TRISA = 0b11100000;
	//LATA = 0xff;	
	TRISC = 0b11110001;
	TRISD = 0x1F;
	//PORTD = 0x00;	
	TRISE = 0x03;
	//PORTE = 0x00;
	
	// it's PNP!!!
	K_KICK1 = 1;
	K_KICK2 = 1;
	K_CHIP1 = 1;
	K_CHIP2 = 1;
	
	K_CHARGE = 0;
	
	// both LEDs off
	LED1 = 1;
	LED2 = 1;
	LED3 = 1;
	//led = LED_POWER;
	

	// === Main Loop ===	
	while(1){
	//	LED2 = PORTDbits.RD0;
	//	LED3 = PORTDbits.RD1;
		//LED1 = PORTDbits.RD1;
		LED1 = !LED1;//!LED3;
		if (RxPacket.done){
			// clear done flag so that don't keep looping though
			RxPacket.done = 0;

			ClrWdt();
			//led = LED_LINK;

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
				case 'L'://for testing
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
					
				case 'K':		
					K_CHARGE = 0; // stop charging
					K_KICK1 = 0;  // stop kicking
					K_KICK2 = 0;  // stop kicking
					kick_counter = 1000000000000;
					break;

				// enable kicker - begin charging, don't kick
				case 'E':
					K_DISCHARGE = 0;
					K_KICK1 = 1;
					K_KICK2 = 1;
					
					K_CHARGE = 1;
					LED3 = 0;
				//	kickCon.enable = 1;
					break;

				// disable kicker - stop kicking
				case 'D':
					K_DISCHARGE = 1;
					K_KICK1 = 1;
					K_KICK2 = 1;
					
					LED3 = 1;			
					K_CHARGE = 0;
				//	kickCon.enable = 0;
					break;

				// some other port
				default:
					break;
			}
		}
	if (kick_counter > 0)
		kick_counter--;
	
	// break bream check
	if ((PORTBbits.RB3 == 0) && (kick_counter > 0)){
		blink();	
		K_KICK1 = 1;
		K_KICK2 = 1;
		K_CHARGE = 1;
	}
/*	if(PORTBbits.RB3 == 0){
		LED3 = 0;
		kick_counter++;
	}
	else
		LED3 = 1;
*/
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

void blink2(){
	unsigned short i;
	MBLED1 = 0;
	MBLED2 = 0;
	for (i=0; i<0xFF; i++)ClrWdt();
	MBLED1 = 1;
	MBLED2 = 1;
	for (i=0; i<0xFF; i++)ClrWdt();
}
	



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