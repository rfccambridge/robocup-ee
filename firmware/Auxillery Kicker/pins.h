// pin declarations

#ifndef __PINS_H
#define __PINS_H

// === KICKER ===
#define K_KICK1			LATAbits.LATA0
#define K_KICK2			LATAbits.LATA4
#define K_KICK3			LATAbits.LATA5
#define K_KICK4			LATEbits.LATE0
#define K_CHARGE		LATEbits.LATE2

// === DEBUG ===
#define LED1			PORTAbits.RA0
#define LED2			PORTAbits.RA1

// === DRIBBLER ===
#define DRIBBLER		PORTCbits.RC2

#endif // __PINS_H
