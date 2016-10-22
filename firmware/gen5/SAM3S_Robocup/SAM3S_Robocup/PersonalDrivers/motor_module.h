#ifndef MOTOR_MODULE
#define MOTOR_MODULE

#include "board.h"

// PWM channel on which to attach motor driver
typedef enum channel {
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3
}Channel;

// Direction of motion for motor
typedef enum direction {
	FORWARD,
	REVERSE	
}Direction;

// motor structure
typedef struct motor {
	
	// motor channel - do not change once initialized
	Channel motor_channel;
	
	// motor speed - need to do sync up with others on how we will be representing speed in our data transfer
	uint8_t speed;
	
	// motor direction element
	Direction motor_direction;
	
}Motor;

// Initialize motor to default settings (forward direction, zero speed)
void initialize_motor(Motor *m, Channel chan);

#endif