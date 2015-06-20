#ifndef __MOTORBOARD_H__
#define __MOTORBOARD_H__

#include "EELib.h"
#include <avr/io.h>

// Pin names
pin_def SS_M = pin_def(&PORTB, 0);
pin_def SCK = pin_def(&PORTB, 1);
pin_def MOSI = pin_def(&PORTB, 2);
pin_def MISO = pin_def(&PORTB, 3);
pin_def PWM1 = pin_def(&PORTB, 4);
pin_def PWM2 = pin_def(&PORTB, 5);
pin_def PWM3 = pin_def(&PORTB, 6);
pin_def PWM4 = pin_def(&PORTB, 7);

pin_def LED3 = pin_def(&PORTC, 0);
pin_def LED1 = pin_def(&PORTC, 1);
pin_def LED2 = pin_def(&PORTC, 2);
pin_def LED4 = pin_def(&PORTC, 3);

pin_def DIR1 = pin_def(&PORTD, 0);
pin_def DIR2 = pin_def(&PORTD, 1);
pin_def DIR3 = pin_def(&PORTD, 2);
pin_def DIR4 = pin_def(&PORTD, 3);
pin_def BREN = pin_def(&PORTD, 4);

pin_def M1QA = pin_def(&PORTE, 0);
pin_def M1QB = pin_def(&PORTE, 1);
pin_def M2QA = pin_def(&PORTE, 2);
pin_def M2QB = pin_def(&PORTE, 3);
pin_def M3QA = pin_def(&PORTE, 4);
pin_def M3QB = pin_def(&PORTE, 5);
pin_def M4QA = pin_def(&PORTE, 6);
pin_def M4QB = pin_def(&PORTE, 7);

pin_def SENSE1 = pin_def(&PORTF, 0);
pin_def SENSE2 = pin_def(&PORTF, 1);
pin_def SENSE3 = pin_def(&PORTF, 2);
pin_def SENSE4 = pin_def(&PORTF, 3);
pin_def TSENSE1 = pin_def(&PORTF, 4);
pin_def TSENSE2 = pin_def(&PORTF, 5);
pin_def TSENSE3 = pin_def(&PORTF, 6);
pin_def TSENSE4 = pin_def(&PORTF, 7);

pin_def FAULT1 = pin_def(&PORTG, 0);
pin_def FAULT2 = pin_def(&PORTG, 1);
pin_def FAULT3 = pin_def(&PORTG, 2);
pin_def FAULT4 = pin_def(&PORTG, 3);

// Set up system clock to max frequency and enable pins as output
void init(void);

// Set the break on if true (D4 low), otherwise turn break off (D4 high)
void setBrake(bool enable);

// Given a PWM line number and a direction as bool, sets the direction of that motor
void setDirection(PWM pwmNum, bool dir);

// Turns off all motors, enables brake
void safeMode(void);

#endif //__MOTORBOARD_H__