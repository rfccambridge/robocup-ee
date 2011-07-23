#include <p33FJ32MC304.h>

//all signal pins on the chip
//1
#define RX_TRIS               (TRISBbits.TRISB9)
#define RX_I				  (PORTBbits.RB9)
#define RX_O				  (LATBbits.LATB9)

//2
#define TXEN_TRIS             (TRISCbits.TRISC6)
#define TXEN_I				  (PORTCbits.RC6)
#define TXEN_O				  (LATCbits.LATC6)

//5
#define PWMDIS_TRIS           (TRISCbits.TRISC9)
#define PWMDIS_I		      (PORTCbits.RC9)
#define PWMDIS_O			  (LATCbits.LATC9)

//8
#define H3_TRIS               (TRISBbits.TRISB10)
#define H3_I				  (PORTBbits.RB10)
#define H3_O				  (LATBbits.LATB10)

//9
#define L3_TRIS               (TRISBbits.TRISB11)
#define L3_I				  (PORTBbits.RB11)
#define L3_O				  (LATBbits.LATB11)

//10
#define H2_TRIS               (TRISBbits.TRISB12)
#define H2_I				  (PORTBbits.RB12)
#define H2_O				  (LATBbits.LATB12)

//11
#define L2_TRIS               (TRISBbits.TRISB13)
#define L2_I				  (PORTBbits.RB13)
#define L2_O				  (LATBbits.LATB13)

//14
#define H1_TRIS               (TRISBbits.TRISB14)
#define H1_I				  (PORTBbits.RB14)
#define H1_O				  (LATBbits.LATB14)

//15
#define L1_TRIS               (TRISBbits.TRISB15)
#define L1_I				  (PORTBbits.RB15)
#define L1_O				  (LATBbits.LATB15)

//19
#define LED4_TRIS             (TRISAbits.TRISA0)
#define LED4_I				  (PORTAbits.RA0)
#define LED4_O				  (LATAbits.LATA0)

//20
#define LED3_TRIS             (TRISAbits.TRISA1)
#define LED3_I				  (PORTAbits.RA1)
#define LED3_O				  (LATAbits.LATA1)

//21
#define PGED1_TRIS            (TRISBbits.TRISB0)
#define PGED1_I				  (PORTBbits.RB0)
#define PGED1_O				  (LATBbits.LATB0)

//22
#define PGEC1_TRIS            (TRISBbits.TRISB1)
#define PGEC1_I				  (PORTBbits.RB1)
#define PGEC1_O				  (LATBbits.LATB1)

//23
#define SENSE_TRIS            (TRISBbits.TRISB2)
#define SENSE_I				  (PORTBbits.RB2)
#define SENSE_O				  (LATBbits.LATB2)

//24
#define LED2_TRIS             (TRISBbits.TRISB3)
#define LED2_I				  (PORTBbits.RB3)
#define LED2_O				  (LATBbits.LATB3)

//25
#define LED1_TRIS             (TRISCbits.TRISC0)
#define LED1_I				  (PORTCbits.RC0)
#define LED1_O				  (LATCbits.LATC0)

//30
#define BOTID3_TRIS           (TRISAbits.TRISA2)
#define BOTID3_I			  (PORTAbits.RA2)
#define BOTID3_O			  (LATAbits.LATA2)

//31
#define BOTID2_TRIS           (TRISAbits.TRISA3)
#define BOTID2_I			  (PORTAbits.RA3)
#define BOTID2_O			  (LATAbits.LATA3)

//32
#define BOTID1_TRIS           (TRISAbits.TRISA8)
#define BOTID1_I			  (PORTAbits.RA8)
#define BOTID1_O			  (LATAbits.LATA8)

//33
#define BOTID0_TRIS           (TRISBbits.TRISB4)
#define BOTID0_I			  (PORTBbits.RB4)
#define BOTID0_O			  (LATBbits.LATB4)

//34
#define BBID0_TRIS            (TRISAbits.TRISA4)
#define BBID0_I				  (PORTAbits.RA4)
#define BBID0_O			 	  (LATAbits.LATA4)

//35
#define BBID1_TRIS            (TRISAbits.TRISA9)
#define BBID1_I				  (PORTAbits.RA9)
#define BBID1_O			 	  (LATAbits.LATA9)

//36
#define QEB_TRIS              (TRISCbits.TRISC3)
#define QEB_I				  (PORTCbits.RC3)
#define QEB_O			 	  (LATCbits.LATC3)

//37
#define QEA_TRIS              (TRISCbits.TRISC4)
#define QEA_I				  (PORTCbits.RC4)
#define QEA_O			 	  (LATCbits.LATC4)

//41
#define HALL3_TRIS            (TRISBbits.TRISB5)
#define HALL3_I				  (PORTBbits.RB5)
#define HALL3_O			 	  (LATBbits.LATB5)

//42
#define HALL1_TRIS            (TRISBbits.TRISB6)
#define HALL1_I				  (PORTBbits.RB6)
#define HALL1_O			 	  (LATBbits.LATB6)

//43
#define HALL2_TRIS            (TRISBbits.TRISB7)
#define HALL2_I				  (PORTBbits.RB7)
#define HALL2_O			 	  (LATBbits.LATB7)

//44
#define TX_TRIS               (TRISBbits.TRISB8)
#define TX_I				  (PORTBbits.RB8)
#define TX_O			 	  (LATBbits.LATB8)

//selectable input sources
/*
Input Name				Fn Name	Reg		Configuration Bits
-----------------------------------------------------------
External Interrupt 1 	INT1 	RPINR0 	INT1R<4:0>
External Interrupt 2 	INT2 	RPINR1 	INT2R<4:0>
Timer2 External Clock 	T2CK 	RPINR3 	T2CKR<4:0>
Timer3 External Clock 	T3CK 	RPINR3 	T3CKR<4:0>
Timer4 External Clock 	T4CK 	RPINR4 	T4CKR<4:0>
Timer5 External Clock 	T5CK 	RPINR4 	T5CKR<4:0>
Input Capture 1 		IC1 	RPINR7 	IC1R<4:0>
Input Capture 2 		IC2 	RPINR7 	IC2R<4:0>
Input Capture 7 		IC7 	RPINR10 IC7R<4:0>
Input Capture 8 		IC8 	RPINR10 IC8R<4:0>
Output Compare Fault A 	OCFA 	RPINR11 OCFAR<4:0>
PWM1 Fault 				FLTA1 	RPINR12 FLTA1R<4:0>
PWM2 Fault 				FLTA2 	RPINR13 FLTA2R<4:0>
QEI1 Phase A 			QEA1 	RPINR14 QEA1R<4:0>
QEI1 Phase B 			QEB1 	RPINR14 QEB1R<4:0>
QEI1 Index 				INDX1 	RPINR15 INDX1R<4:0>
QEI2 Phase A 			QEA2 	RPINR16 QEA2R<4:0>
QEI2Phase B 			QEB2 	RPINR16 QEB2R<4:0>
QEI2 Index 				INDX2 	RPINR17 INDX2R<4:0>
UART1 Receive 			U1RX 	RPINR18 U1RXR<4:0>
UART1 Clear To Send 	U1CTS 	RPINR18 U1CTSR<4:0>
UART2 Receive 			U2RX 	RPINR19 U2RXR<4:0>
UART2 Clear To Send 	U2CTS 	RPINR19 U2CTSR<4:0>
SPI1 Data Input 		SDI1 	RPINR20 SDI1R<4:0>
SPI1 Clock Input	 	SCK1 	RPINR20 SCK1R<4:0>
SPI1 Slave Select Input SS1 	RPINR21 SS1R<4:0>
SPI2 Data Input 		SDI2 	RPINR22 SDI2R<4:0>
SPI2 Clock Input 		SCK2 	RPINR22 SCK2R<4:0>
SPI2 Slave Select Input SS2 	RPINR23 SS2R<4:0>
ECAN1 Receive 			CIRX 	RPINR26 CIRXR<4:0>
*/

#define INT1R_I	RPINR0bits.INT1R
#define INT2R_I RPINR1bits.INT2R
#define T2CKR_I RPINR3bits.T2CKR
#define T3CKR_I RPINR3bits.T3CKR
#define T4CKR_I RPINR4bits.T4CKR
#define T5CKR_I RPINR4bits.T5CKR
#define IC1R_I RPINR7bits.IC1R
#define IC2R_I RPINR7bits.IC2R
#define IC7R_I RPINR10bits.IC7R
#define IC8R_I RPINR10bits.IC8R
#define OCFAR_I RPINR11bits.OCFAR
#define FLTA1R_I RPINR12bits.FLTA1R
#define FLTA2R_I RPINR13bits.FLTA2R
#define QEA1R_I RPINR14bits.QEA1R
#define QEB1R_I RPINR14bits.QEB1R
#define INDX1R_I RPINR15bits.INDX1R
#define QEA2R_I RPIN16bits.QEA2R
#define QEB2R_I RPIN16bits.QEB2R
#define INDX2R_I RPIN17bits.INDX2R
#define U1CTSR_I RPINR18bits.U1CTSR
#define U1RXR_I RPINR18bits.U1RXR
#define U2CTSR_I RPINR19bits.U2CTSR
#define U2RXR_I RPINR19bits.U2RXR
#define SDI1R_I RPINR20bits.SDI1R
#define SCK1R_I RPINR20bits.SCK1R
#define SS1R_I RPINR21bits.SS1R
#define SDI2R_I RPINR22bits.SDI2R
#define SCK2R_I RPINR22bits.SCK2R
#define SS2R_I RPINR23bits.SS2R
#define CIRXR_I RPIN26bits.CIRXR

// Peripheral Pin Select Outputs

/*
Fn		RPnR	Output Name
--------------------------------------------------
NULL 	00000 	RPn tied to default port pin
C1OUT 	00001 	RPn tied to Comparator1 Output
C2OUT 	00010 	RPn tied to Comparator2 Output
U1TX 	00011 	RPn tied to UART1 Transmit
U1RTS 	00100 	RPn tied to UART1 Ready To Send
U2TX 	00101 	RPn tied to UART2 Transmit
U2RTS 	00110 	RPn tied to UART2 Ready To Send
SDO1 	00111 	RPn tied to SPI1 Data Output
SCK1 	01000 	RPn tied to SPI1 Clock Output
SS1 	01001	RPn tied to SPI1 Slave Select Output
SDO2 	01010 	RPn tied to SPI2 Data Output
SCK2 	01011 	RPn tied to SPI2 Clock Output
SS2 	01100 	RPn tied to SPI2 Slave Select Output
C1TX 	10000 	RPn tied to ECAN1 Transmit
OC1 	10010 	RPn tied to Output Compare 1
OC2 	10011 	RPn tied to Output Compare 2
OC3 	10100 	RPn tied to Output Compare 3
OC4 	10101 	RPn tied to Output Compare 4
UPDN1 	11010 	RPn tied to QEI1 direction (UPDN) status
UPDN2 	11011 	RPn tied to QEI2 direction (UPDN) status
*/

#define NULL_O		0
#define C1OUT_O		1
#define C2OUT_O		2
#define U1TX_O		3
#define U1RTS_O		4
#define U2TX_O		5
#define U2RTS_O		6
#define SDO1_O		7
#define SCK1OUT_O	8
#define SS1OUT_O	9
#define SDO2_O		10
#define SCK2OUT_O	11
#define SS2OUT_O	12
#define C1TX_O		16
#define OC1_O		18
#define OC2_O		19
#define OC3_O		20
#define OC4_O		21
#define UPDN1_O		26
#define UPDN2_O		27

// Peripheral Pin Select pin output registers
#define RP0_O RPOR0bits.RP0R
#define RP1_O RPOR0bits.RP1R
#define RP2_O RPOR1bits.RP2R
#define RP3_O RPOR1bits.RP3R
#define RP4_O RPOR2bits.RP4R
#define RP5_O RPOR2bits.RP5R
#define RP6_O RPOR3bits.RP6R
#define RP7_O RPOR3bits.RP7R
#define RP8_O RPOR4bits.RP8R
#define RP9_O RPOR4bits.RP9R
#define RP10_O RPOR5bits.RP10R
#define RP11_O RPOR5bits.RP11R
#define RP12_O RPOR6bits.RP12R
#define RP13_O RPOR6bits.RP13R
#define RP14_O RPOR7bits.RP14R
#define RP15_O RPOR7bits.RP15R
#define RP16_O RPOR8bits.RP16R
#define RP17_O RPOR8bits.RP17R
#define RP18_O RPOR9bits.RP18R
#define RP19_O RPOR9bits.RP19R
#define RP20_O RPOR10bits.RP20R
#define RP21_O RPOR10bits.RP21R
#define RP22_O RPOR11bits.RP22R
#define RP23_O RPOR11bits.RP23R
#define RP24_O RPOR12bits.RP24R
#define RP25_O RPOR12bits.RP25R

