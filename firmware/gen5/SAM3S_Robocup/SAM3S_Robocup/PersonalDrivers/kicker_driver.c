#include <RobocupDrivers.h>
#include <asf.h>

#define MAX_SPEED 30 // change these constants as necessary
#define MIN_SPEED 0

#define KICK_ENABLE IOPORT_CREATE_PIN(PIOB,0)
#define CHIP_ENABLE IOPORT_CREATE_PIN(PIOB,1)

uint32_t level = 0;

void configure_kicker(void)
{
	ioport_set_pin_dir(KICK_ENABLE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(KICK_ENABLE,false);
	
	ioport_set_pin_dir(CHIP_ENABLE,IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(CHIP_ENABLE,false);
}

// given a speed, determine what value to set KICK_REF DAC output voltage to
void set_kick_ref(uint32_t speed) 
{
	if(speed > MAX_SPEED)
		level = 0xFFF; // max DAC level, corresponds to approximately (5/6) * ADVREF which should be (5/6) * 3.3V = 2.75V
	else if(speed < MIN_SPEED)
		level = 0x000; // IMPORTANT, DAC output not zero: min DAC level, corresponds to 0 + (1/6) * ADVREF which should be around 0.55V
		
	level = (speed * 0xFFF) / MAX_SPEED;
		
	set_dac_level(level); 
	
}

// TODO: determine if we want this function to disable the kicker after enabling it
void kick_enable() 
{
	ioport_set_pin_level(KICK_ENABLE,true);
}


// TODO: determine if we want this function to disable the kicker after enabling it
void chip_enable()
{
	ioport_set_pin_level(CHIP_ENABLE,true);
}

