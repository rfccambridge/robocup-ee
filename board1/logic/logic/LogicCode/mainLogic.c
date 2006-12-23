/* Coded by Minjae Kim, December 2006
Still at the testing stage
This code is for the main logic pic.
Power PWM: RB1, RB3, RB4, and RD7 <--(that is D, nor B)
Directional I/O RB3, RB4, RB6 RB7 

Assumptions
Max speed is assumed to be 5000 RPM
Baud rate is 9600

Note
ASCII 0x26 = "&"
	  0x2A = "*"
Testing
RC0 is used as test output
*/
#include <p18f4431.h>
#include "4Enet.h"
unsigned char SpeedR;		//Second byte information speed received from the radio in RPM (max 5000 RPM = 0xFF)
unsigned char AdDrt;		//First byte information.  First nybble is direction (1111 forward 0000 backward)
							//Second nybble is Address of the motor (0b100~001)
char Data00;		//First byte received
char Data01;
void high_ISR();	 //Interrupt Service Routine

PacketBuffer DataPacket;



#pragma code high_vector=0x08				//We are not using Priortized Interrupts: so all interrupts go to 0x08. 
void interrupt_high_vector(){
_asm GOTO high_ISR _endasm}					//branching to the actual ISR
#pragma code

#pragma interrupt high_ISR					 //Interrupt Service Routine (the real one)
void high_ISR(){

	
	if (PIR1bits.RCIF && PIE1bits.RCIE)
		handleRx(&DataPacket);
	PORTCbits.RC3=1;
	PIR1bits.RCIF=0;
	


}
#pragma



void main(){



//Power PWM.  PWM 1,3,5,7 used.
	//PWMCON0=0b01110000;  //Only Odd pins enabled (default)


//Interrupts
INTCON = 0b11000000;					//GIE and PEIE set.	
PIE1bits.RCIE = 1;						//Serial Receive Interrupt enabled.

//Testing
TRISD = 0b00000000;
PORTD = 0b00000000;
PORTDbits.RD1=1;


do {
	if(DataPacket.done) PORTDbits.RD0=1;

} while(1);

}
