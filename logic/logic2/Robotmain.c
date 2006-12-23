#include <p18f4431.h>
#include "Robotserial.h"
#include "PinDeclarations.h"

/*************************************************************************
* Constants                                                              *  
**************************************************************************/

//Positional Constants
#define TIME_INTERVAL 1
#define ROB_VOLT 5

//ADC ports for positional instruments
#define ADC_ACCELX 2
#define ADC_ACCELY 3
#define ADC_GYRO 4

#define GYRO_CONST 5 //Measured in mV/deg/s
	

/*************************************************************************
* Function Prototypes                                                    *  
**************************************************************************/
void reset(void);
void initPWM(void);
void setMotorDirection(uchar which, uchar direction);
void setMotorSpeed(uchar which, uchar data);

//ADC Functions
void initADC(void);
void adc(uchar which);

//Positional Functions
double posCalibrate(uchar which);
void updateGyro(void);

// interrupts
void InterruptHandlerHigh();
void InterruptHandlerLow();
void initInterrupts();

//Globals
uchar kickerEnabled = 0;
uchar sending = 0;
uchar lastBall = 0;
uchar chargeKick = 0;

SerialState serialState;
TxBuffer txBuffer;

/*************************************************************************
* Main                                                                   *  
**************************************************************************/

void main(void) {
  uchar data, flash = 0;

  reset();

  TMR0H = 0;                    //clear timer
  TMR0L = 0;                    //clear timer
  T0CON = 0b11000101;           //set up timer0 - prescaler 1:64
  //T0CON = 0b11000111;			// prescaler 1:256

	//Interrupts may be messing with kicker board.
  //initInterrupts();

// ===== main loop =====
  while(1) {
    // === Serial ===
    if(serialRead(&data)) {
      handleSerial(data);
    }
      
	// === Kicker ===
	// make sure both kickers are off
	KICK = 0;
	CHIP = 0;
	// charge or discharge to maintain kicker voltage between 200-220 (arbitrary units)
	if(kickerEnabled == 1) {
		adc(0); 								// ADC conversion for AN0
		if ((ADRESH < 200) &&( CHARGE==0)) {
		    DISCHARGE = 0; 
			CHARGE = 1;
    	} else if ((ADRESH>220) && (CHARGE==1)){
	      	CHARGE = 0;
    	}
	} else {
		CHARGE = 0;
		DISCHARGE = 1;
	}

	// === LEDS === may be causing interference problems
	/*if(BALL_DETECT != lastBall) {
		resetTxBuffer();
		putTxBuffer('<');
		if(BALL_DETECT) putTxBuffer('y');
		else putTxBuffer('n');
		putTxBuffer(ADDRESS);
		putTxBuffer('>');
		lastBall = BALL_DETECT;
	    LED2 = BALL_DETECT; // visual indication of ball in dribbler
}//*/
	LED2 = BALL_DETECT;

	if(BALL_DETECT && chargeKick) {
		//setPower(serialState.dataBytes[0] << 1);	// set the voltage of the capacitor
		KICK = 1;									// pulse chip kicker
		KICK = 0;									// (no additional delay needed)
		kickerEnabled = 0;
		chargeKick = 0;
}

    	// active flag - lights up if last instruction was to this robot
    LED0 = ((serialState.flags & ACTIVE) != 0);
  }
}

/*************************************************************************
* Functions                                                              *  
**************************************************************************/
void reset(void) {
  uchar i;
  
  // enable output on ports A,B,C,D
  TRISA = 0b00011111; // high pins == ADC
  TRISB = 0; // all outputs
  TRISC = 0b11010001; // high pins == Serial & ball_detect
  TRISD = 0; // LED's and Brakes
  TRISE = 0;
  
  LED3 = 1;
  
  //Init Dribbler and Kicker PWM pins (CCP module)
  PR2 = 255;
  T2CON = 0xFF;
  TMR2 = 0;
  DRIBBLER_DIR = 1;
  
  //CCP1 module setup for dribbler
  CCP1CON = 0xFF;
  CCPR1L = 0;  //0% duty cycle
     
  // set up PWM stuff
  initPWM();
  
  // set up ADC
  initADC();
  
  LED2 = 1; 
  
  // set up serial port stuff
  initSerial();
  for(i = 0; i < sizeof(serialState); i++)
    ((uchar*)&serialState)[i] = 0;
    
  serialState.address = ADDRESS;

  // calibration
  serialState.robDegrees = 0;
  serialState.gyroNull = posCalibrate(ADC_GYRO);
  serialState.accelXNull = posCalibrate(ADC_ACCELX);
  serialState.accelYNull = posCalibrate(ADC_ACCELY); 
  LED1 = 1;
  
  LED0 = 1;
  
  // Turn off all LED's
  LED0 = 0;
  LED1 = 0;
  LED2 = 0;
  LED3 = 0;
  
  // Kicker related
  CHARGE = 0;
  DISCHARGE = 0;  
  kickerEnabled = 0; //disable kicker
}

// set appropriate SFR's to initialize the PWM module
void initPWM(void) {
  // disable pre/postscale, and put PWM in free-running mode
  PTCON0 = 0b00000000;
  
  // enable odd PWM pins (this is kind of arbitrary right now), and put all
  // pairs in independent mode
  PWMCON0 = 0b01111111;
  
  // enable updates from period/duty cycle regs, put special event trigger on
  // downward counting (I'm not sure what the significance of that is)
  PWMCON1 = 0b00001000;
  
  // disable "dead time"
  DTCON = 0;
  
  // disable output override, and make all override bits zero (I don't think the
  // second one is necessary)
  OVDCOND = 0xff;
  OVDCONS = 0;
  
  // disable fault conditions
  FLTCONFIG = 0;
  
  // initialize the PWM timer to 0
  PTMRH = 0;
  PTMRL = 0;
  
  // initialize the PWM period (we should look into what the optimal value for
  // this is)
  PTPERH = 0b00000011;
  PTPERL = 0b11111111;
  
  // enable the PWM time base
  PTCON1 = 0b10000000;

  //initialize directions
  setMotorDirection(0,0);
  setMotorDirection(1,0);
  setMotorDirection(2,1);
  setMotorDirection(3,1);
  
  //turn off all motors
  setMotorSpeed(0,0);
  setMotorSpeed(1,0);
  setMotorSpeed(2,0);
  setMotorSpeed(3,0);

}

void setMotorDirection(uchar which, uchar direction) {
  switch(which) {
  case 0: M0DIR = direction; break;
  case 1: M1DIR = direction; break;
  case 2: M2DIR = direction; break;
  case 3: M3DIR = direction; break;
  }
}

// set the PWM duty cycle for one motor
#define SETDCREGS(regprefix)  \
  do {                        \
    regprefix##L = dcl;       \
    regprefix##H = dch;       \
  } while(0)

// speed must be a 7-bit number
void setMotorSpeed(uchar which, uchar speed) {
  uchar dch, dcl;
  
  // convert 7 bit speed to 14 bit duty cycle in dch and dcl
  // speed = 0ABCDEFG (bits, not hex digits)
  // --> dch = 0000ABCD
  //     dcl = EFGABCDE
  dch = speed >> 3; // no need to worry about sign bit - speed is 7 bits
  dcl = (speed >> 2) | (speed << 5);
  
  // now set appropriate SFRs + ports for motor
  switch(which) {
  case 1: 
	if(speed == 0) {
	  BRAKE1 = 0; // turn on brake
	} else {
	  BRAKE1 = 1; // turn off brake
	}
	SETDCREGS(PDC0); 
	break;
  case 2: 
	if(speed == 0) {
	  BRAKE2 = 0; // turn on brake
	} else {
	  BRAKE2 = 1; // turn off brake
	}
	SETDCREGS(PDC1);
	break;
  case 0: 
	if(speed == 0) {
	  BRAKE0 = 0; // turn on brake
	} else {
	  BRAKE0 = 1; // turn off brake
	}
	SETDCREGS(PDC2);
	break;
  case 3: 
	if(speed == 0) {
	  BRAKE3 = 0; // turn on brake
	} else {
	  BRAKE3 = 1; // turn off brake
	}
	SETDCREGS(PDC3);
	break;
  }
}

#undef SETDCREGS

void initADC(void) {
  ANSEL0 = 0b00011111; //AN<4:0> are all analog inputs
  ANSEL1=0; //keeps PORTE sane
  ADCHS = 0; // selects AN0, AN1, AN2, AN3
  ADCON0 = 0b00000001; //selects single shot group A	
  ADCON1 = 0;        //sets voltage ref, disables buffer
  ADCON2 = 0;   //result is left justified, no time delay
  ADCON3 = 0b11000000; //no interupts, no external triggers (change!)
}
void adc(uchar which) {

  if(which > 4) {
    return;
  }
  else if (which == 4) {
    ADCHS = 1; //selects AN1,2,3,4
  } else {
    ADCHS = 0; //selects AN0,1,2,3
  }

  switch(which) {

        case 0:
          ADCON0 = 0b00000001; //selects single shot group A
          break;          
        case 1:
          ADCON0 = 0b00000101; //selects single shot group B
          break;
        case 2:
          ADCON0 = 0b00001001; //selects single shot group C
           break;
        case 3:
          ADCON0 = 0b00001101; //selects single shot group D
          break;
        case 4:
          ADCON0 = 0b00000001; //selects single shot group A
          break;
        default: break;
	}

  ADCON0bits.DONE = 1;     //start conversion
  while(PIR1bits.ADIF==0); //wait until complete
 }

double posCalibrate(uchar which)
{
  unsigned long sum1 = 0; //ulong gives over four billion
  unsigned long sum2 = 0;
  int i, max = 50;
  int tempH, tempL; //for bit shifting purposes
/*
  do {
	for(i = 0; i < max; i++)
  	{
    	adc(which);
    	tempH = (int) ADRESH;  
    	tempL = (int) ADRESL;
    	sum1 = sum1 + ((tempH << 2) | (tempL >> 6));
  	}

	for(i = 0; i < max; i++)
  	{
    	adc(which);
    	tempH = (int) ADRESH;  
    	tempL = (int) ADRESL;
    	sum2 = sum2 + ((tempH << 2) | (tempL >> 6));
  	}
  }while(sum1 != sum2);*/


	for(i = 0; i < max; i++)
  	{
    	adc(which);
    	tempH = (int) ADRESH;  
    	tempL = (int) ADRESL;
    	sum1 = sum1 + ((tempH << 2) | (tempL >> 6));
  	}


  return ((double) sum1) / max;

}

void updateGyro(void)
{
	int adcGyro;
 	int tempH, tempL; //for bit shifting purposes
	int change;
	double error = 2;

	adc(ADC_GYRO);
    tempH = (int) ADRESH;  
    tempL = (int) ADRESL;
	adcGyro = ((tempH << 2) | (tempL >> 6)); //gyro output in ADC int
	//adcGyro = (adcGyro & 0x03F8) - (serialState.gyroNull & 0x03F8);
	//adcGyro = adcGyro - serialState.gyroNull;

	//serialState.robDegrees = serialState.robDegrees + adcGyro;
    change = (double) adcGyro - serialState.gyroNull;

	if(change < error && change > -error)
		change = 0;

	serialState.robDegrees = serialState.robDegrees + change;	

}

void initInterrupts() {
	RCONbits.IPEN = 1;

	// interrupt priorities
    INTCON2bits.TMR0IP = 1;       //timer0 is high priority

	// interrupt enables
	INTCON = 0b11100000;

	PIE1bits.TMR1IE = 1; //enables timer1 interrupt 
	IPR1bits.TMR1IP = 0; //low priority

}	


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// High priority interrupt vector
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#pragma code InterruptVectorHigh = 0x08
void InterruptVectorHigh (void)
{
  _asm
    goto InterruptHandlerHigh
  _endasm
}


#pragma code
#pragma interrupt InterruptHandlerHigh
void InterruptHandlerHigh ()
{
	// updateGyro() takes the ADC away from the kicker and breaks setPower
	if(INTCONbits.TMR0IF) {
		INTCONbits.TMR0IF = 0; 
//		updateGyro();
//		LED3 = ~LED3;
	}

}


//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
// Low priority interrupt routine
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------

#pragma code InterruptVectorLow = 0x18
void InterruptVectorLow (void)
{
  _asm
    goto InterruptHandlerLow
  _endasm
}

#pragma code
#pragma interrupt InterruptHandlerLow
void InterruptHandlerLow ()
{
	//low interrupt code
	//this code takes care of turning on and off the
	//transmitter
	if((PIR1bits.TMR1IF) && (sending == 0)) {	
		PIR1bits.TMR1IF = 0; //clear timer1 flag
		//T1CON = 0b10010000; //disable timer1
		transmit();
	} else if ((PIR1bits.TMR1IF) && (sending == 1)) {
		PIR1bits.TMR1IF = 0; //clear timer1 flag
		T1CON = 0b10010000; //disable timer1
		TX_EN = 0; //disable transmitter
		sending = 0;
	}

}
