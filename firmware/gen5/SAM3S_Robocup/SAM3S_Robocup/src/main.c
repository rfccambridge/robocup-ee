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
#define BREN0 IOPORT_CREATE_PIN(PIOA,10)
#define DIR0 IOPORT_CREATE_PIN(PIOA,9)
#define FAULTN0 IOPORT_CREATE_PIN(PIOA,17)
#define BREN2 IOPORT_CREATE_PIN(PIOA,7)
#define DIR2 IOPORT_CREATE_PIN(PIOA,12)
#define FAULTN2 IOPORT_CREATE_PIN(PIOA,20)

int i = 0;
void SysTick_Handler( void )
{	
	i++;
	if (i > 10)
	{
		i = 0;
		ioport_set_pin_level(CHARGE, false);
	}
	if (i == 2)
	{
		ioport_set_pin_level(CHARGE,true);
	}
	
	
	
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	ioport_init();
	ioport_set_pin_dir(DISCHARGE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(BREN0,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(DIR0,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(FAULTN0,IOPORT_DIR_INPUT);
	ioport_set_pin_mode(FAULTN0,IOPORT_MODE_PULLUP);
	ioport_set_pin_level(DISCHARGE,false);
	
	ioport_set_pin_level(BREN0,false);
	ioport_set_pin_level(DIR0,false);
	ioport_set_pin_dir(CHARGE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(CHARGE,false);
	ioport_set_pin_level(CHARGE_DONE,IOPORT_DIR_INPUT);
	
	
	ioport_set_pin_dir(FAULTN2,IOPORT_DIR_INPUT);
	ioport_set_pin_mode(FAULTN2,IOPORT_MODE_PULLUP);
	ioport_set_pin_dir(BREN2,IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(DIR2,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(BREN2,false);
	ioport_set_pin_level(DIR2,false);
	
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
	//chip_enable();
	//kick_enable();
	SysTick_Config(BOARD_FREQ_MAINCK_BYPASS);

    while(1){
		
		if(!ioport_get_pin_level(CHARGE_DONE))
		{
			ioport_set_pin_level(CHARGE,false);
			kick_enable();
		}

		// right now we set the kicker reference value each time through the loop. 
		// We may want to change this later on if we find that this is a bottle neck in
		// our control loop
		set_kick_ref(kicker_speed);	
	
		/* Insert application code here, after the board has been initialized. */
	}
}