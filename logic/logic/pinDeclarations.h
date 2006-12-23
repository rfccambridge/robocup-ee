/*************************************************************************
* Defines                                                                *  
**************************************************************************/

// software settable address
#define ADDRESS 3

// motor direction control pins (swapped to accomodate f'ed up electronics, setMotorFunc also swapped)
#define M0DIR PORTBbits.RB5
#define M1DIR PORTBbits.RB0
#define M2DIR PORTBbits.RB2
#define M3DIR PORTBbits.RB6

// brake pins (Low true: ie. 0V == brake) (not swapped)
#define BRAKE0 PORTDbits.RD4
#define BRAKE1 PORTDbits.RD6
#define BRAKE2 PORTDbits.RD5
#define BRAKE3 PORTCbits.RC5

// LED pins
#define LED0 PORTDbits.RD0
#define LED1 PORTDbits.RD1
#define LED2 PORTDbits.RD2
#define LED3 PORTDbits.RD3

// other pins
#define KICK PORTAbits.RA6
#define CHIP PORTCbits.RC1
#define CHARGE PORTEbits.RE1
#define DISCHARGE PORTEbits.RE0
#define DRIBBLER_DIR PORTCbits.RC3
#define BALL_DETECT PORTCbits.RC4 // this one is an input

// serial pins 
#define TX_EN PORTEbits.RE2
