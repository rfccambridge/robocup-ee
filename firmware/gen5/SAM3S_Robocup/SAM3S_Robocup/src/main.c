/**
 * Author: Liam Mulshine & ___
 *
 * RFC Cambridge Firmware
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
	ioport_set_pin_level(MY_LED,LOW);
		
	// configure pwm module to allow for motor control
   //  configure_pwm();
	
	//Motor motor1;
	//initialize_motor(&motor1,CHANNEL0);
	test_pwm();
	
	if(!pmc_is_periph_clk_enabled(ID_PWM))
		while(1);
	else 
		while(1);
	/* Insert application code here, after the board has been initialized. */
}