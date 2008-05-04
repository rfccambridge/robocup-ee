// pin declarations

#ifndef __PINS_H
#define __PINS_H

// === KICKER ===
#define K_KICK1			LATcbits.LATc3
#define K_KICK2			LATDbits.LATD6
#define K_CHIP1			LATCbits.LATC2
#define K_CHIP2			LATCbits.LATC1
#define K_CHARGE		LATDbits.LATD7
#define K_DISCHARGE		LATBbits.LATB4

// === DEBUG ===
#define LED1			PORTAbits.LATA0
#define LED2			PORTAbits.LATA1
#define LED3			PORTAbits.LATA2

//Mother board LEDs
#define MBLED1			PORTAbits.LATA3
#define MBLED2			PORTAbits.LATA4

//Incoming voltages
#define BattV			PORTAbits.LATA5
// === DRIBBLER ===
#define DRIBBLER		PORTCbits.RC2

#endif // __PINS_H
