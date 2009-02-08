// pin declarations

#ifndef __PINS_H
#define __PINS_H
#include <p18f4431.h>
// === KICKER ===
#define K_KICK1			LATCbits.LATC3
#define K_KICK2			LATDbits.LATD6
#define K_CHIP1			LATCbits.LATC2
#define K_CHIP2			LATCbits.LATC1
#define K_CHARGE		PORTDbits.RD7
#define K_DISCHARGE		LATBbits.LATB4

// === DEBUG ===
#define LED1			LATAbits.LATA0
#define LED2			LATAbits.LATA1
#define LED3			LATAbits.LATA2

//Mother board LEDs
#define MBLED1			LATAbits.LATA3
#define MBLED2			LATAbits.LATA4

//Incoming voltages
#define BattV			PORTAbits.RA5

// === DRIBBLER ===
#define DRIBBLER		LATEbits.LATE1

//===Break beam
//goes low when the ball is seen
#define	BBEAM			PORTBbits.RB3

#endif // __PINS_H
