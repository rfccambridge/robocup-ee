/*
*	Author: Liam Mulshine 
*	Personalized PWM Driver for SAM3s MCU
* 
*/

#include <asf.h>
#include "pwm_driver.h"

void pwm_test()
{
	
	// create pwm channel instance
	pwm_channel_t pwm_1;
	
	// enable the peripheral clock for pwm module
	pmc_enable_periph_clk(ID_PWM);
	
	// disable channel in order to set config details
	pwm_channel_disable(PWM,PWM_CHANNEL_0);
	
	pwm_clock_t clk_settings = {
		.ul_clka = 1000*100,
		.ul_clkb = 0,
		.ul_mck = 48000000, 
	};
	
	// initialize pwm module with updated clock settings
	pwm_init(PWM,&clk_settings);
	
	// set specific pwm channel settings, use CLKA as clock source
	pwm_1.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_1.ul_period = 100;
	pwm_1.ul_duty = 50;
	pwm_1.channel = PWM_CHANNEL_0;
	// initialize channel with specified settings and enable the channel
	pwm_channel_init(PWM,&pwm_1);
	
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	
	
}
