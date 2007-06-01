// pin declarations

#ifndef __PINS_H
#define __PINS_H

// === KICKER ===
#define	K_KICK1			PORTAbits.RA4		// SCR 1 (out)
#define	K_KICK2			PORTAbits.RA5		// SCR 2 (out)
#define	K_KICK3			PORTEbits.RE0		// SCR 3 (out)
#define	K_KICK4			PORTEbits.RE1		// SCR 4 (out)
#define	K_CHARGE		PORTEbits.RE2		// charges (out)
#define	K_DISCHARGE		PORTDbits.RD5		// discharges (out)
#define	K_OVERVOLTAGE	PORTAbits.RA0		// threshold voltage reached (in)

// === DEBUG ===
#define LED1			PORTDbits.RD2
#define LED2			PORTDbits.RD3

#endif // __PINS_H
