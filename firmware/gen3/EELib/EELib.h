#ifndef __EELIB_H_
#define __EELIB_H_

#endif //__EELIB_H_

#include <inttypes.h>

// Given  a port, a pin in the port, and a boolean value (0 or 1),
// sets the pin in the given port
void setBit(volatile uint8_t port, uint8_t pin, bool val);

// Defines a type that enumerates the four possible PWM pins
typedef enum pwm {
	PWM1,
	PWM2,
	PWM3,
	PWM4
} PWM;

// Given a PWM pin, enables fast PWM mode on that pin with initial duty cycle of 0%
void enablePWM(PWM PWMnum);

// Given a PWM pin and a float between 0.0 and 1.0 representing the duty cycle,
// sets duty cycle for that pin.
void setDutyCycle(PWM PWMnum, float dutyCycle);
