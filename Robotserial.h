#ifndef __ROBOTSERIAL_H
#define __ROBOTSERIAL_H

#include <p18f4431.h>
#include "PinDeclarations.h"

/*************************************************************************
* Defines                                                                *  
**************************************************************************/

// size of serial command buffer
#define MAX_CMD_LEN 10

// serial commands
#define CMD_ALL                 0
#define CMD_WHEELS              1
#define CMD_KICKER              2
#define CMD_DRIBBLER            3
#define CMD_CHIP 	              4
#define CMD_KICKER_ENABLE       5

#define CMD_RESET               6
#define CMD_READ_NEXT_BYTE      7
#define CMD_POLL_GYRO           8
#define CMD_POLL_BATT           9
#define CMD_POLL_BALL           10
#define CMD_CHANGE_ADDRESS      11
#define CMD_POLL_ACCEL_X        12
#define CMD_POLL_ACCEL_Y		13
#define CMD_POLL_HEADING		14


//serial command lengths (not counting address but including checksum)
#define CMD_ALL_LEN             9
#define CMD_WHEELS_LEN          6
#define CMD_KICKER_LEN          2
#define CMD_DRIBBLER_LEN        2
#define CMD_CHIP_LEN 	        2
#define CMD_KICKER_ENABLE_LEN   2

#define CMD_RESET_LEN           2
#define CMD_POLL_BALL_LEN       2
#define CMD_POLL_GYRO_LEN       2
#define CMD_POLL_BATT_LEN       2
#define CMD_CHANGE_ADDRESS_LEN  5
#define CMD_POLL_ACCEL_X_LEN    2
#define CMD_POLL_ACCEL_Y_LEN    2
#define CMD_POLL_HEADING_LEN	2

#define txBufferLength 32

/*************************************************************************
* Typedefs                                                               *  
**************************************************************************/
typedef unsigned char uchar;

// serial state flags
enum {
  ACTIVE = 1
};

typedef struct {
  uchar flags;
  uchar command;
  uchar byteNumber;
  uchar address;
  uchar dataBytes[MAX_CMD_LEN];
  
  //Position data
  double robPosX;
  double robPosY;
  double robDegrees;
  
  //Sensor nullpoints
  double gyroNull;
  double accelXNull;
  double accelYNull;  
  
} SerialState;

typedef struct {
	uchar buffer[txBufferLength];
	uchar ptr;
} TxBuffer;

/*************************************************************************
* Function Prototypes                                                    *  
**************************************************************************/


void initSerial(void);
uchar serialRead(uchar *data);
void handleSerial(uchar data);
void setPower(uchar power);
void handleCommand(void);
uchar checkCommand(void);
uchar cmdLength(uchar cmd);

void putTxBuffer(uchar dataByte);
void resetTxBuffer(void);
void transmit(void);
void transmitByte(uchar dataByte);

extern void reset(void);
extern void initPWM(void);
extern void initADC(void);
extern void setMotorDirection(uchar which, uchar direction);
extern void setMotorSpeed(uchar which, uchar data);
extern void adc(uchar which);


/*************************************************************************
* Globals                                                                *  
**************************************************************************/
extern SerialState serialState;
extern uchar kickerEnabled;
extern uchar sending;
extern uchar chargeKick;

extern TxBuffer txBuffer; 

#endif
