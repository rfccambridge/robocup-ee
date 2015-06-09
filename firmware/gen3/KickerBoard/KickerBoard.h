#include "EELib.h"

// Pin names
pin_def CHARGE(&PORTA, 0);
pin_def DISCHARGE(&PORTA, 1);
pin_def KICK_ENABLE = pin_def(&PORTA, 2);
pin_def CHIP_ENABLE = pin_def(&PORTA, 3);
pin_def DONE = pin_def(&PORTA, 4);

pin_def SS_K = pin_def(&PORTB, 0);
pin_def SCK = pin_def(&PORTB, 1);
pin_def MOSI = pin_def(&PORTB, 2);
pin_def MISO = pin_def(&PORTB, 3);

pin_def KICK_PWM = pin_def(&PORTB, 5);
pin_def DRIB = pin_def(&PORTB, 6);
pin_def BB_OUT = pin_def(&PORTB, 7);

pin_def RLED1 = pin_def(&PORTC, 1);
pin_def RLED2 = pin_def(&PORTC, 2);
pin_def BLED1 = pin_def(&PORTC, 3);
pin_def BLED2 = pin_def(&PORTC, 4);
pin_def GLED1 = pin_def(&PORTC, 5);
pin_def GLED2 = pin_def(&PORTC, 6);

pin_def DIVCAP = pin_def(&PORTF, 0);
pin_def BATSENSE = pin_def(&PORTF, 1);
pin_def BB_IN = pin_def(&PORTF, 2);

pin_def RESET = pin_def(&PORTG, 5);