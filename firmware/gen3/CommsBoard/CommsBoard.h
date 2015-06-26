#include "EELib.h"

// Pin names
pin_def BID3 = pin_def(&PINA, 0);
pin_def BID2 = pin_def(&PINA, 1);
pin_def BID1 = pin_def(&PINA, 2);
pin_def BID0 = pin_def(&PINA, 3);

// returns robot ID from first half of pin A
// damn it have to reverse order
char getBotID() {
	return (0x0F & (reverse(PINA) >> 4));
}

pin_def EX3 = pin_def(&PINA, 4);
pin_def EX2 = pin_def(&PINA, 5);
pin_def EX1 = pin_def(&PINA, 6);
pin_def EX0 = pin_def(&PINA, 7);

pin_def SCK = pin_def(&PINB, 1);
pin_def MOSI = pin_def(&PINB, 2);
pin_def MISO = pin_def(&PORTB, 3);

pin_def RLED1 = pin_def(&PORTC, 0);
pin_def RLED2 = pin_def(&PORTC, 1);
pin_def BLED1 = pin_def(&PORTC, 2);
pin_def BLED2 = pin_def(&PORTC, 3);
pin_def GLED1 = pin_def(&PORTC, 4);
pin_def GLED2 = pin_def(&PORTC, 5);
pin_def YLED1 = pin_def(&PORTC, 6);
pin_def YLED2 = pin_def(&PORTC, 7);

pin_def SPARE1 = pin_def(&PORTD, 0);
pin_def SPARE2 = pin_def(&PORTD, 1);
pin_def SPARE3 = pin_def(&PORTD, 2);
pin_def SPARE4 = pin_def(&PORTD, 3);
pin_def SPARE5 = pin_def(&PORTD, 4);

pin_def RX = pin_def(&PORTE, 0);
pin_def TX = pin_def(&PORTE, 1);
pin_def XBRST = pin_def(&PORTE, 2);
pin_def INT = pin_def(&PORTE, 3);
pin_def SCL = pin_def(&PORTE, 4);
pin_def SDA = pin_def(&PORTE, 5);
pin_def RTS = pin_def(&PORTE, 6);
pin_def CTS = pin_def(&PORTE, 7);

pin_def SS_M = pin_def(&PORTF, 0);
pin_def SS_K = pin_def(&PORTF, 1);
pin_def SS_E1 = pin_def(&PORTF, 2);
pin_def SS_E2 = pin_def(&PORTF, 3);
pin_def SS_E3 = pin_def(&PORTF, 4);
pin_def SS_E4 = pin_def(&PORTF, 5);
pin_def SS_E5 = pin_def(&PORTF, 6);
pin_def TSENSE = pin_def(&PINF, 7);

pin_def RESET = pin_def(&PING, 5);