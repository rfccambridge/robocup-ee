#include <RobocupDrivers.h>
#include <asf.h>

#define PWM1 IOPORT_CREATE_PIN(PIOA,0)
#define PWM2 IOPORT_CREATE_PIN(PIOA,1)
#define PWM3 IOPORT_CREATE_PIN(PIOA,2)
#define PWM4 IOPORT_CREATE_PIN(PIOB,14) // NOTE the this PWM channel utilizes peripheral B

void configure_pwm(){
	
	// configure pin 0 to respond to peripheral_A PWM
	pio_configure_pin(PWM1,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 1 to respond to peripheral_A PWM
	pio_configure_pin(PWM2,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 2 to respond to peripheral_A PWM
	pio_configure_pin(PWM3,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 14 to respond to peripheral_B PWM
	pio_configure_pin(PWM4,PIO_TYPE_PIO_PERIPH_B);
	
	// enable PWM module to receive master clock
	pmc_enable_periph_clk(ID_PWM);
}

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

void update_duty_cycle(uint32_t duty_cycle, Channel chan) {
	// set update duty cycle register to specified duty cycle. Duty cycle will change on next duty cycle period due to double buffering system
	REG_PWM_CPRDUPD0 = duty_cycle;
}

void attach_motor(Motor *m) {
	
	switch(m->motor_channel){
		case CHANNEL0 :
		
			// disable PWM channel in order to change clock configuration, then initialize PWM module clock details
			pwm_channel_disable(PWM, PWM_CHANNEL_0);
			
			pwm_channel_t pwm_0;

			pwm_clock_t clock_setting = {
				.ul_clka = 2500 * 1000,
				.ul_clkb = 0,
				.ul_mck = sysclk_get_cpu_hz()
			};
			pwm_init(PWM, &clock_setting);
		
			// specify channel settings and initialize
			pwm_0.ul_prescaler = PWM_CMR_CPRE_CLKA;
			pwm_0.ul_period = 100;
			pwm_0.ul_duty = 50;
			pwm_0.channel = PWM_CHANNEL_0;
			pwm_channel_init(PWM, &pwm_0);
		
			// finally, enable pwm channel
			pwm_channel_enable(PWM, PWM_CHANNEL_0);
			break;
		case CHANNEL1 :
			break;			
		case CHANNEL2 :
			break;	
		case CHANNEL3 :
			break;			
	}
	
}