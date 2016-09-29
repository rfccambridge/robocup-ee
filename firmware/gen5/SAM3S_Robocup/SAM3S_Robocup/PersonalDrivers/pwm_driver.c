#include <pwm_driver.h>
#include <asf.h>

#define PWM1 IOPORT_CREATE_PIN(PIOA,0)

void test_pwm(void)
{
	// configure pin 0 to respond to peripheral_A PWM
	pio_configure_pin(PWM1,PIO_TYPE_PIO_PERIPH_A);
	
	// create instance of pwm channel for configuration
	pwm_channel_t pwm_1;
	
	// enable PWM module to receive master clock
	pmc_enable_periph_clk(ID_PWM);
	
	// disable PWM channel in order to change clock configuration, then initialize PWM module clock details 
	pwm_channel_disable(PWM, PWM_CHANNEL_0);
	pwm_clock_t clock_setting = {
		.ul_clka = 2500 * 1000,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &clock_setting);
	
	// specify channel settings and initialize
	pwm_1.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_1.ul_period = 100;
	pwm_1.ul_duty = 50;
	pwm_1.channel = PWM_CHANNEL_0;
	pwm_channel_init(PWM, &pwm_1);
	
	// finally, enable pwm channel
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	
}

void update_duty_cycle(uint32_t duty_cycle)
{
	// set update duty cycle register to specified duty cycle. Duty cycle will change on next duty cycle period due to double buffering system
	REG_PWM_CPRDUPD0 = duty_cycle;
}