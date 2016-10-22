/**
 * Author: Liam Mulshine & ___
 *
 * RFC Cambridge Firmware
 */

#include <asf.h>
#include <RobocupDrivers.h>

#define MY_LED IOPORT_CREATE_PIN(PIOA, 8)

extern pwm_channel_t pwm_0;
extern pwm_channel_t pwm_1;


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	ioport_init();
	ioport_set_pin_dir(MY_LED, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(MY_LED,LOW);
		
	//	REG_PWM_FCR = 1;	// clear the pwm fault if you accidentally set pwm period or duty cycle to an bad value :)	

	// configure pwm module to allow for motor control
	configure_pwm();
	
	Motor motor0;
	Motor motor1;
	Motor motor2;
	Motor motor3;
	initialize_motor(&motor0,CHANNEL0);
	initialize_motor(&motor1,CHANNEL1);
	initialize_motor(&motor2,CHANNEL2);
	initialize_motor(&motor3,CHANNEL3); 
	
	// test dac function
	test_dac();  

	while(1){
		
		// check if another conversion is ready to be performed, and if so write to the conversion data register
		if(dacc_get_interrupt_status(DACC) & 0x8){
			dacc_write_conversion_data(DACC,0xFFF/2);
		}
		
	};
	/* Insert application code here, after the board has been initialized. */
}