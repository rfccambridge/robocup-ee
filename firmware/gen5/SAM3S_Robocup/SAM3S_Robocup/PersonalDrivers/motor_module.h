#ifndef MOTOR_MODULE
#define MOTOR_MODULE

#include "board.h"

//TODO think of a way to remove  this from this file so that pwm does not depend on it
// PWM channel on which to attach motor driver
typedef enum channel {
	CHANNEL0,
	CHANNEL1,
	CHANNEL2,
	CHANNEL3
}Channel;

// Update four motor speeds
void update_motor_speeds(uint32_t speed0, uint32_t speed1, uint32_t speed2, uint32_t speed3);
void initialize_motors(void);

#endif