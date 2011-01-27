// pin declarations

#ifndef __PINS_H
#define __PINS_H
#include <p18f4431.h>
// === KICKER ===
#define K_KICK1			LATCbits.LATC3
//2nd power of kicking is not used currently
//#define K_KICK2		LATDbits.LATD6 
#define K_CHIP1			LATCbits.LATC2
//2nd power of chipping is not used currently
//#define K_CHIP2		LATCbits.LATC1
#define K_CHARGE		LATDbits.LATD7
#define K_DISCHARGE		LATCbits.LATC1
#define K_DONE          PORTCbits.RC4

// === DEBUG ===
#define LED3			LATAbits.LATA0
#define LED2			LATAbits.LATA1
#define LED1			LATAbits.LATA2

//Mother board LEDs (only one)
#define MBLED1			LATAbits.LATA3
//#define MBLED2		LATAbits.LATA4

//Incoming voltages
#define BattV			PORTEbits.RE1
#define CapV            PORTAbits.RA5

// === DRIBBLER ===
#define DRIBBLER		PORTBbits.RB5

//===Break beam
//goes low when the ball is seen
#define	BBEAM			PORTCbits.RC5

#endif // __PINS_H
