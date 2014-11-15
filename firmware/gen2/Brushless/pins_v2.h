#include <p30F4011.h>

//all signal pins on the chip
//2
#define TX_TRIS               (TRISFbits.TRISF5)
#define TX_I				  (PORTFbits.RF5)
#define TX_O			 	  (LATFbits.LATF5)

//3
#define RX_TRIS               (TRISFbits.TRISF4)
#define RX_I				  (PORTFbits.RF4)
#define RX_O				  (LATFbits.LATF4)

//4
#define TXEN_TRIS             (TRISFbits.TRISF1)
#define TXEN_I				  (PORTFbits.RF1)
#define TXEN_O				  (LATFbits.LATF1)

//5
#define PWMDIS_TRIS           (TRISFbits.TRISF0)
#define PWMDIS_I		      (PORTFbits.RF0)
#define PWMDIS_O			  (LATFbits.LATF0)

//8
#define H3_TRIS               (TRISEbits.TRISE5)
#define H3_I				  (PORTEbits.RE5)
#define H3_O				  (LATEbits.LATE5)

//9
#define L3_TRIS               (TRISEbits.TRISE4)
#define L3_I				  (PORTEbits.RE4)
#define L3_O				  (LATEbits.LATE4)

//10
#define H2_TRIS               (TRISEbits.TRISE3)
#define H2_I				  (PORTEbits.RE3)
#define H2_O				  (LATEbits.LATE3)

//11
#define L2_TRIS               (TRISEbits.TRISE2)
#define L2_I				  (PORTEbits.RE2)
#define L2_O				  (LATEbits.LATE2)

//14
#define H1_TRIS               (TRISEbits.TRISE1)
#define H1_I				  (PORTEbits.RE1)
#define H1_O				  (LATEbits.LATE1)

//15
#define L1_TRIS               (TRISEbits.TRISE0)
#define L1_I				  (PORTEbits.RE0)
#define L1_O				  (LATEbits.LATE0)

//19
#define LED4_TRIS             (TRISBbits.TRISB0)
#define LED4_I				  (PORTBbits.RB0)
#define LED4_O				  (LATBbits.LATB0)

//20
#define LED3_TRIS             (TRISBbits.TRISB1)
#define LED3_I				  (PORTBbits.RB1)
#define LED3_O				  (LATBbits.LATB1)

//21
#define LED2_TRIS            (TRISBbits.TRISB2)
#define LED2_I				  (PORTBbits.RB2)
#define LED2_O				  (LATBbits.LATB2)

//22
#define LED1_TRIS            (TRISBbits.TRISB3)
#define LED1_I				  (PORTBbits.RB3)
#define LED1_O				  (LATBbits.LATB3)

//23
#define QEA_TRIS              (TRISBbits.TRISB4)
#define QEA_I				  (PORTBbits.RB4)
#define QEA_O			 	  (LATBbits.LATB4)

//24
#define QEB_TRIS              (TRISBbits.TRISB5)
#define QEB_I				  (PORTBbits.RB5)
#define QEB_O			 	  (LATBbits.LATB5)

//25
#define SENSE_TRIS            (TRISBbits.TRISB6)
#define SENSE_I				  (PORTBbits.RB6)
#define SENSE_O				  (LATBbits.LATB6)

//26
#define BBID0_TRIS            (TRISBbits.TRISB7)
#define BBID0_I				  (PORTBbits.RB7)
#define BBID0_O			 	  (LATBbits.LATB7)

//27
#define BBID1_TRIS            (TRISBbits.TRISB8)
#define BBID1_I				  (PORTBbits.RB8)
#define BBID1_O			 	  (LATBbits.LATB8)

//35
#define BOTID0_TRIS           (TRISCbits.TRISC14)
#define BOTID0_I			  (PORTCbits.RC14)
#define BOTID0_O			  (LATCbits.LATC14)

//36
#define BOTID1_TRIS           (TRISEbits.TRISE8)
#define BOTID1_I			  (PORTEbits.RE8)
#define BOTID1_O			  (LATEbits.LATE8)

//37
#define BOTID2_TRIS           (TRISDbits.TRISD1)
#define BOTID2_I			  (PORTDbits.RD1)
#define BOTID2_O			  (LATDbits.LATD1)

//38
#define BOTID3_TRIS           (TRISDbits.TRISD3)
#define BOTID3_I			  (PORTDbits.RD3)
#define BOTID3_O			  (LATDbits.LATD3)

//41
#define HALL3_TRIS            (TRISDbits.TRISD2)
#define HALL3_I				  (PORTDbits.RD2)
#define HALL3_O			 	  (LATDbits.LATD2)

//42
#define HALL1_TRIS            (TRISDbits.TRISD0)
#define HALL1_I				  (PORTDbits.RD0)
#define HALL1_O			 	  (LATDbits.LATD0)

//43
#define HALL2_TRIS            (TRISFbits.TRISF6)
#define HALL2_I				  (PORTFbits.RF6)
#define HALL2_O			 	  (LATFbits.LATF6)
