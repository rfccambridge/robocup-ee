#include "EELib.h"

// Pin names
#define BID3 PINA0
#define BID2 PINA1
#define BID1 PINA2
#define BID0 PINA3
#define EX3 PINA4
#define EX2 PINA5
#define EX1 PINA6
#define EX0 PINA7

#define SCK PINB1
#define MOSI PINB2
#define MISO PINB3

pin_def GLED1 = pin_def(&PORTC, 1);
#define RLED1 PINC1 
#define GLED2 PINC2
#define RLED2 PINC3
#define GLED3 PINC4
#define RLED3 PINC5
#define GLED4 PINC6
#define RLED4 PINC7

#define SPARE1 PIND0
#define SPARE2 PIND1
#define SPARE3 PIND2
#define SPARE4 PIND3
#define SPARE5 PIND4

#define RX PINE0
#define TX PINE1
#define XBRST PINE2
#define INT PINE3
#define SCL PINE4
#define SDA PINE5
#define RTS PINE6
#define CTS PINE7

#define SS_M PINF0
#define SS_K PINF1
#define SS_E1 PINF2
#define SS_E2 PINF3
#define SS_E3 PINF4
#define SS_E4 PINF5
#define SS_E5 PINF6
#define TSENSE PINF7

#define RESET PING5