#ifndef DAC_DRIVER
#define DAC_DRIVER

#include "board.h"
#include <asf.h>

// Test function for PWM Module
void test_dac(void);

// configure io ports and master clock for pwm module
void configure_dac(void);

void set_dac_level(uint16_t level);

#endif