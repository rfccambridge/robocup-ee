// kicker.h

#ifndef __KICKER_H
#define __KICKER_H


// pin definitions
#define	K_KICK1			PORTAbits.RA4		// SCR 1 (out)
#define	K_KICK2			PORTAbits.RA5		// SCR 2 (out)
#define	K_KICK3			PORTEbits.RE0		// SCR 3 (out)
#define	K_KICK4			PORTEbits.RE1		// SCR 4 (out)
#define	K_CHARGE		PORTEbits.RE2		// charges (out)
#define	K_DISCHARGE		PORTDbits.RD5		// discharges (out)
#define	K_OVERVOLTAGE	PORTAbits.RA0		// threshold voltage reached (in)

typedef struct{
	unsigned enable:1;			// set and the interrupt will maintain the cap voltage
	unsigned kick1:1;
	unsigned kick2:1;
	unsigned kick3:1;
	unsigned kick4:1;
	unsigned kick:1;			// set to kick with with selected caps	
	unsigned charged:1;			// set when at least one cap is charged
	unsigned updated:1;			// set by interrupt, clear in main
} KickerControl;

enum KickerState {CHARGE, FULL, KICK, DISCHARGE};



void initKicker();
void handleKicker();

#endif //__KICKER_H
