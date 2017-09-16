/**
 * Author: Liam Mulshine 
 *
 * RFC Cambridge Firmware
 */

/******************************
 * Includes
 ******************************/
#include <asf.h>
#include <RobocupDrivers.h>
#include <io_expander.h>
#include <pins.h>

/******************************
 * Data Types
 ******************************/

/******************************
 * Constant and Macro Definitions
 ******************************/
int pin1 = 0;
int pin2 = 0;
int pin3 = 0;
int pin4 = 0;

/******************************
 * Static Data Declarations
 ******************************/

/******************************
 * Private Function Prototypes
 ******************************/

/******************************
 * Public Function Bodies
 ******************************/

// packet in which we should receive the speed commands from comms board
uint8_t speed[4] = {0x00,0x00,0x00,0x00};
// indicate the previous speed commands... use to check if we should update motor speeds
uint32_t prev_speed[2] = {0x00000000,0x00000000};
// buffer that holds up to date speed commands... updated in parse_speeds()
uint32_t speed_buf[2] = {0x00,0x00};
// flag set whenever speed request from comms board is needed
int flag = 0;

void parse_speeds(uint8_t *buf) {
	speed_buf[0] = ((uint32_t) buf[0]) | ((uint32_t) buf[1] << 8);	
	speed_buf[1] = ((uint32_t) buf[2]) | ((uint32_t) buf[3] << 8);	
}

void SysTick_Handler(void) {
	// set flag to indicate that we need to read from the comms board in the main loop
	flag = 1;	
}

/******************************
 * Private Function Bodies
 ******************************/

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	pin_config();
	SysTick_Config(sysclk_get_cpu_hz() / 10);

	REG_PWM_FCR = 0;		// clear the pwm fault if you accidentally set pwm period or duty cycle to an bad value :)	


	// put all configuration functions in system init function
	// configure PWM module to allow for motor speed control - bring this into motor initialization module
	configure_pwm();
	// configure DAC so that kicker power commands can be made later		
	configure_dac();	
	uint32_t kicker_speed = 15;
	configure_kicker();
	configure_twi();
	io_expander_init();
	
	initialize_motors();
	
	uint32_t new_speed = 1;
    while(1){
		
		if(!ioport_get_pin_level(CHARGE_DONE))
		{
			ioport_set_pin_level(CHARGE,false);
			kick_enable();
		}
		
		if(flag)
		{
			receive_packet(0,0,ARDUINO_ADDR,speed,4*sizeof(uint8_t));	
			flag = 0;
		}
		
		/*
		parse_speeds(speed);
		if(speed_buf[0] != prev_speed[0] || speed_buf[1] != prev_speed[1])
		{	
			update_speed(&motor0,speed_buf[0]);
			update_speed(&motor1,speed_buf[1]);
			prev_speed[0] = speed_buf[0];
			prev_speed[1] = speed_buf[1];
			
		}
		*/
		
		//send_packet(0,0,ARDUINO_ADDR,speed[0],sizeof(uint8_t));
		// right now we set the kicker reference value each time through the loop. 
		// We may want to change this later on if we find that this is a bottle neck in
		// our control loop
		set_kick_ref(kicker_speed);
		/* Insert application code here, after the board has been initialized. */
	}
}