#include <p18f4431.h>
#include "Robotserial.h"
#include "PinDeclarations.h"

void initSerial(void) {
  SPBRG = 50;	//9600 Baud rate for 8Mhz
  TXSTAbits.BRGH = 1;
  BAUDCTLbits.BRG16 = 0;

  TXSTAbits.SYNC = 0;
  RCSTAbits.SPEN = 1;

  TXSTAbits.TXEN = 1; //Enable transmit
  RCSTAbits.CREN = 1; //Enable receive
	
  BAUDCTLbits.ABDEN = 0; //Disable auto baud rate detect

  TX_EN = 0; //Disable transmitter 
}

uchar serialRead(uchar *data) {
  if(PIR1bits.RCIF == 0) {
    LED1 = 0;
    return 0;
  }
  
  LED1 = 1;
  *data = RCREG;
  return 1;
}

// handle a new incoming serial bit
void handleSerial(uchar data) {
  uchar i;
  int j;
  if(data & 0x80) {
    uchar address = (data & 0x78) >> 3;
    if(address == serialState.address) {
      // turn on ACTIVE flag
      serialState.flags |= ACTIVE;
      serialState.command = data & 0x7;
      serialState.byteNumber = 0;
    }
    else {
      // turn off ACTIVE flag
      serialState.flags &= ~ACTIVE;
    }
    return;
  }

  // our robot is not active, can ignore data
  if((serialState.flags & ACTIVE) == 0) return;
  

  //we don't have transmissions 
  //that are just 1 byte	
  //this also allows us to extend commands
  if((serialState.byteNumber != 0) && 
	 (serialState.byteNumber >= cmdLength(serialState.command))) return;
  
  serialState.dataBytes[serialState.byteNumber] = data;

  if((serialState.byteNumber != 0) &&
	 (serialState.byteNumber == cmdLength(serialState.command) -1)) {
    if(checkCommand()) {
      handleCommand();
	}
  }
  serialState.byteNumber++;
}

uchar cmdLength(uchar cmd) {
	switch(cmd) {
	  case CMD_ALL:
		  return CMD_ALL_LEN;
	  case CMD_WHEELS:
		  return CMD_WHEELS_LEN;
	  case CMD_KICKER:
		  return CMD_KICKER_LEN;
	  case CMD_DRIBBLER:
		  return CMD_DRIBBLER_LEN;
	  case CMD_CHIP:
		  return CMD_CHIP_LEN;
	  case CMD_KICKER_ENABLE:
		  return CMD_KICKER_ENABLE_LEN;
	  case CMD_POLL_HEADING:
		  return CMD_POLL_HEADING_LEN;
      case CMD_POLL_BALL:
      	  return CMD_POLL_BALL_LEN;
	  case CMD_POLL_ACCEL_X:
	  	  return CMD_POLL_ACCEL_X_LEN;
	  case CMD_POLL_ACCEL_Y:
	  	  return CMD_POLL_ACCEL_Y_LEN;
	  case CMD_POLL_GYRO:
	      return CMD_POLL_GYRO_LEN;
	  case CMD_POLL_BATT:
	      return CMD_POLL_BATT_LEN;
	  case CMD_RESET:
	      return CMD_RESET_LEN;
	  case CMD_CHANGE_ADDRESS:
	      return CMD_CHANGE_ADDRESS_LEN;
	  case CMD_READ_NEXT_BYTE:
	      serialState.command = serialState.dataBytes[0];
		  return (cmdLength(serialState.command) + 1);
	  default:
		  return 0;
	}
}

uchar checkCommand()
{
  int i;
  int j;
  int checksum = 0;
	
  for(i = 0; i < cmdLength(serialState.command) - 1; i++) {
  	checksum = checksum + (int) serialState.dataBytes[i];
  }
  checksum = checksum % 128;

  if((uchar) checksum == serialState.dataBytes[cmdLength(serialState.command)-1]) {
   LED2 = 1;
   LED3 = 0;
   return 1;
  } else {
   LED3 = 1;
   LED2 = 0;
   return 0;
  }
}

void handleCommand()
{
	int i;
	int j;
	
	switch(serialState.command){

	  case CMD_ALL:
		break;   

	// === wheel commands ===
	  case CMD_WHEELS:
		  for(i = 0; i < 4; i++) {
			  setMotorDirection(i, (serialState.dataBytes[0] & (1 << (6-i))) >> (6-i));
		  }
		  for(i = 1; i < 5; i++) {
		  	setMotorSpeed(i - 1, serialState.dataBytes[i]);
		  }
	  	break;

	// === Kicker commands ===
	case CMD_KICKER_ENABLE:
		kickerEnabled = (serialState.dataBytes[0]==1);
		break;

	case CMD_KICKER:
		if(kickerEnabled == 1) {
			//setPower(serialState.dataBytes[0] << 1);	// set the voltage of the capacitor
			KICK = 1;									// pulse ground kicker
			KICK = 0;									// (no additional delay needed)	
			kickerEnabled = 0;
		}
		break;

	case CMD_CHIP:

	//Temp function
		if(kickerEnabled) {
			chargeKick = 1;


/*
  		if(kickerEnabled == 1) {
			setPower(serialState.dataBytes[0] << 1);	// set the voltage of the capacitor
			CHIP = 1;									// pulse chip kicker
			CHIP = 0;									// (no additional delay needed)
			kickerEnabled = 0;
*/

		}
		break;

	// === Dribbler commands ===
	case CMD_DRIBBLER:
      	CCPR1L = (serialState.dataBytes[0] << 1);  //Set Dribbler PWM
		break;

	// === Ball detect commands ===
	case CMD_POLL_BALL:
	  resetTxBuffer();
  	  putTxBuffer('<');
	  if(BALL_DETECT) putTxBuffer('n');
	  else putTxBuffer('y');
	  putTxBuffer('>');
	  break;

	// === Accelerometer and gyro commands ===
	case CMD_POLL_ACCEL_X:
      adc(3);
	  resetTxBuffer();
	  putTxBuffer((char)((int)serialState.accelXNull >> 2));
	  putTxBuffer((char)((int)serialState.accelXNull << 6));
	  break;
  
	case CMD_POLL_ACCEL_Y:
	  adc(2);
	  resetTxBuffer();
	  putTxBuffer((char)((int)serialState.accelYNull >> 2));
	  putTxBuffer((char)((int)serialState.accelYNull << 6));  
	  break;

	case CMD_POLL_GYRO:
	  //testing only
/*
      adc(4);
	  resetTxBuffer();
	  putTxBuffer(ADRESH);
	  putTxBuffer(ADRESL); 
	 */
	  resetTxBuffer();
	  //Returns the nullpoint
	  putTxBuffer((char)((int)serialState.gyroNull >> 2));
	  putTxBuffer((char)((int)serialState.gyroNull << 6));
      break;

	// === Misc. commands ===
	case CMD_POLL_BATT:
	  // returns battery voltage
      adc(1);
	  resetTxBuffer();
  	  putTxBuffer('<');
	  putTxBuffer(ADRESH);
	  putTxBuffer(ADRESL);
	  putTxBuffer('>');	
	  break;

	case CMD_POLL_HEADING:
	  resetTxBuffer();
	  putTxBuffer((char)(((int)serialState.robDegrees) >> 8));
	  putTxBuffer((char) ((int)serialState.robDegrees));
	  break;

	case CMD_RESET:
	  Reset(); 									// this doesn't just call reset(), it reboots the PIC
	  break;

	case CMD_CHANGE_ADDRESS:
	  // magic numbers / password to change address
	  if((serialState.dataBytes[0] == 39) && 
		 (serialState.dataBytes[1] == 98) && 
		 (serialState.dataBytes[2] == 52)) 
      serialState.address = serialState.dataBytes[3];
	  break;
	  
	default:
	  break;

	}
    ClrWdt();
}

void setPower(uchar power) {
	do{
		// start A2D conversion
	    ADCON0bits.DONE = 1;

    	// wait until its finished
	    while(PIR1bits.ADIF==0);

	 	CHARGE = 0;
	    DISCHARGE = 1; // Start discharging

	} while (ADRESH > power);

	CHARGE = 0; 		// Stop charging
	DISCHARGE = 0;		// Stop discharging
}


// === putTxBuffer ===
// adds a byte to the txBuffer, wraps around if
// buffer overflows
void putTxBuffer(uchar dataByte){
//	if (buffer.ptr>=txBufferLength)
//		buffer.ptr=0;
	txBuffer.buffer[txBuffer.ptr++] = dataByte;
}

// === resetTxBuffer ===
// resets transmit buffer
void resetTxBuffer() {
	TX_EN = 1; //enable transmitter
	T1CON = 0b10100001; //enable timer1 1:1 prescale
  	TMR1H = 0xB1;                    //timer1 HB
  	TMR1L = 0xDF;                    //timer1 LB -> total= 45535

	txBuffer.ptr = 0;
}
 

// === transmit ===
// transmits txBuffer to destinationAddress
void transmit(void) {
	uchar i;
	for (i=0; i<txBuffer.ptr; i++)
		transmitByte(txBuffer.buffer[i]);

	T1CON = 0b10110001; //enable timer1 1:8 prescale
  	TMR1H = 0;                    //reset timer1 
  	TMR1L = 0;                    //reset timer1
	sending = 1;
}
	
// === transmitByte ===
void transmitByte(uchar dataByte) {
	while (PIR1bits.TXIF==0);	// wait until USART is ready
	PIR1bits.TXIF=0;
	TXREG = dataByte;			// transmit dataByte
}
