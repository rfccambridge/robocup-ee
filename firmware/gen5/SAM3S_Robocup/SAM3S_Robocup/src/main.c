/**
 * Author: Liam Mulshine 
 *
 * RFC Cambridge Firmware
 */

#include <asf.h>
#include <RobocupDrivers.h>
#include <pins.h>
int pin1 = 0;
int pin2 = 0;
int pin3 = 0;
int pin4 = 0;

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
	/*
	pin1 = ioport_get_pin_level(FAULTN0);
	pin2 = ioport_get_pin_level(FAULTN2);
	pin3 = ioport_get_pin_level(FAULTN0);
	pin4 = ioport_get_pin_level(FAULTN2);
	ioport_toggle_pin_level(DIR2);*/
	
	// set flag to indicate that we need to read from the comms board in the main loop
	flag = 1;	
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	pin_config();
	SysTick_Config(sysclk_get_cpu_hz() / 10);

	REG_PWM_FCR = 0;	// clear the pwm fault if you accidentally set pwm period or duty cycle to an bad value :)	

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
	
	configure_twi();
	//configure_io_expander();
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
		
		parse_speeds(speed);
		if(speed_buf[0] != prev_speed[0] || speed_buf[1] != prev_speed[1])
		{	
			update_speed(&motor0,speed_buf[0]);
			update_speed(&motor1,speed_buf[1]);
			prev_speed[0] = speed_buf[0];
			prev_speed[1] = speed_buf[1];
			
		}
		
		//send_packet(0,0,ARDUINO_ADDR,speed[0],sizeof(uint8_t));
		// right now we set the kicker reference value each time through the loop. 
		// We may want to change this later on if we find that this is a bottle neck in
		// our control loop
		set_kick_ref(kicker_speed);
		/* Insert application code here, after the board has been initialized. */
	}
}