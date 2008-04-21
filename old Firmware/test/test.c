#include <p18f4431.h>

void main()
{
	unsigned char i, j, k;

	TRISA = 0x00;
	TRISB = 0x00;
	TRISC = 0x00;
	TRISD = 0x00;
	TRISE = 0x00;
	
	while(1) {
		PORTA = 0xff;
		PORTB = 0xff;
		PORTC = 0xff;
		PORTD = 0xff;
		PORTE = 0xff;

		for (i=0; i<255; i++)
	//		for (j=0; j<255; j++)
				Nop();

		PORTA = 0x00;
		PORTB = 0x00;
		PORTC = 0x00;
		PORTD = 0x00;
		PORTE = 0x00;

	//	for (i=0; i<255; i++)
			for (j=0; j<255; j++)
				Nop();

	}	
}
