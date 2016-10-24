#include <RobocupDrivers.h>
#include <asf.h>

#define MAX_SPEED 30 // change these constants as necessary
#define MIN_SPEED 0

uint32_t level = 0;

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