/**
 * Author: Liam Mulshine & ___
 *
 * Robocup Firmware
 */

#include <asf.h>
#include <RobocupDrivers.h>

#define MY_LED IOPORT_CREATE_PIN(PIOA, 8)

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	ioport_init();
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,HIGH);
	
	test_pwm();

	while(1);
	/* Insert application code here, after the board has been initialized. */
}