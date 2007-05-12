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


void high_ISR();	 //Interrupt Service Routine


unsigned char commutate(unsigned char hall);


void main(){
	// PORTA inputs, PORTB-E outputs
	ANSEL0 = 0x3F;
	TRISA = 0xFF;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x00;

	// init QEI
	QEICON = 0b00000100;
		// velocity mode enabled
		// inc on QEA (2x update)

	do {
		PORTB = POSCNTL;
		PORTC = POSCNTH;
		PORTD = QEICON;
	} while(1);

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
