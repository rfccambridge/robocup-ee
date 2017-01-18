/**
 * Author: Liam Mulshine & ___
 *
 * RFC Cambridge Firmware
 */

#include <asf.h>
#include <RobocupDrivers.h>

extern pwm_channel_t pwm_0;
extern pwm_channel_t pwm_1;
#define DISCHARGE IOPORT_CREATE_PIN(PIOA,23)
#define CHARGE IOPORT_CREATE_PIN(PIOB,3)
#define CHARGE_DONE IOPORT_CREATE_PIN(PIOB,2)

void SysTick_Handler( void )
{
	ioport_toggle_pin_level(DISCHARGE);
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	ioport_init();
	ioport_set_pin_dir(DISCHARGE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(DISCHARGE,true);
	ioport_set_pin_dir(CHARGE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(CHARGE,true);
	ioport_set_pin_level(CHARGE_DONE,IOPORT_DIR_INPUT);
	
	//	REG_PWM_FCR = 1;	// clear the pwm fault if you accidentally set pwm period or duty cycle to an bad value :)	

	// configure PWM module to allow for motor speed control
	configure_pwm();
	//configure DAC in order to set kicker reference values later
	configure_dac();
	
	Motor motor0;
	Motor motor1;
	Motor motor2;
	Motor motor3;
	initialize_motor(&motor0,CHANNEL0);
	initialize_motor(&motor1,CHANNEL1);
	initialize_motor(&motor2,CHANNEL2);
	initialize_motor(&motor3,CHANNEL3); 
	
	uint32_t kicker_speed = 15;
	configure_kicker();
	chip_enable();
	kick_enable();
	SysTick_Config(sysclk_get_cpu_hz() * 10);

    while(1){

		// right now we set the kicker reference value each time through the loop. 
		// We may want to change this later on if we find that this is a bottle neck in
		// our control loop
		set_kick_ref(kicker_speed);	
	
		/* Insert application code here, after the board has been initialized. */
	}
}