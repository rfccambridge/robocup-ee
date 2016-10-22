#include <RobocupDrivers.h>
#include <asf.h>

#define PWM1 IOPORT_CREATE_PIN(PIOA,0)
#define PWM2 IOPORT_CREATE_PIN(PIOA,1)
#define PWM3 IOPORT_CREATE_PIN(PIOA,2)
#define PWM4 IOPORT_CREATE_PIN(PIOA,14) // NOTE the this PWM channel utilizes peripheral B

void configure_pwm(){
	
	// configure pin 0 to respond to peripheral_A PWM
	pio_configure_pin(PWM1,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 1 to respond to peripheral_A PWM
	pio_configure_pin(PWM2,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 2 to respond to peripheral_A PWM
	pio_configure_pin(PWM3,PIO_TYPE_PIO_PERIPH_A);
	// configure pin 14 to respond to peripheral_B PWM
	pio_configure_pin(PWM4,PIO_TYPE_PIO_PERIPH_B); // PWMH3 is part of peripheral B

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
		.ul_clka = 0,
		.ul_clkb = 2500 * 1000, // dont use clockA! It will save you lots of debugging time
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &clock_setting);
	
	// specify channel settings and initialize
	pwm_1.ul_prescaler = PWM_CMR_CPRE_CLKB;
	pwm_1.ul_period = 1000;
	pwm_1.ul_duty = 500;
	pwm_1.channel = PWM_CHANNEL_0;
	pwm_channel_init(PWM, &pwm_1);
	
	// finally, enable pwm channel
	pwm_channel_enable(PWM, PWM_CHANNEL_0);
	
}

void update_duty_cycle(uint32_t duty_cycle, Channel chan) {
	// set update duty cycle register to specified duty cycle. Duty cycle will change on next duty cycle period due to double buffering system
	pwm_channel_update_duty(PWM,PWM_CHANNEL_0,500);
}

pwm_channel_t pwm_0;
pwm_channel_t pwm_1;
pwm_channel_t pwm_2;
pwm_channel_t pwm_3;

void attach_motor(Motor *m) {
	
	switch(m->motor_channel){
		case CHANNEL0 :
		
			// disable PWM channel in order to change clock configuration, then initialize PWM module clock details
			pwm_channel_disable(PWM, PWM_CHANNEL_0);

			pwm_clock_t clock_setting_0 = {
				.ul_clka = 0,
				.ul_clkb = 25000 * 1000, // this gives us approximately a 30kHz signal (perfect for the DVR motor controllers which require freq between 16kHz and 50kHz
				.ul_mck = sysclk_get_cpu_hz()
			};
			pwm_init(PWM, &clock_setting_0);
		
			// specify channel settings and initialize
			pwm_0.ul_prescaler = PWM_CMR_CPRE_CLKB;
			pwm_0.ul_period = 1000;
			pwm_0.ul_duty = 500;
			pwm_0.channel = PWM_CHANNEL_0;
			pwm_channel_init(PWM, &pwm_0);
		
			// finally, enable pwm channel
			pwm_channel_enable(PWM, PWM_CHANNEL_0);
			break;
		case CHANNEL1 :
			pwm_channel_disable(PWM, PWM_CHANNEL_1);
			
			pwm_clock_t clock_setting_1 = {
				.ul_clka = 0,
				.ul_clkb = 25000 * 1000,
				.ul_mck = sysclk_get_cpu_hz()
			};
			pwm_init(PWM, &clock_setting_1);

			pwm_1.ul_prescaler = PWM_CMR_CPRE_CLKB;
			pwm_1.ul_period = 1000;
			pwm_1.ul_duty = 500;
			pwm_1.channel = PWM_CHANNEL_1;
			pwm_channel_init(PWM, &pwm_1);
			pwm_channel_enable(PWM, PWM_CHANNEL_1);
			break;			
		case CHANNEL2 :
			pwm_channel_disable(PWM, PWM_CHANNEL_2);
			
			pwm_clock_t clock_setting_2 = {
				.ul_clka = 0,
				.ul_clkb = 25000 * 1000,
				.ul_mck = sysclk_get_cpu_hz()
			};
			pwm_init(PWM, &clock_setting_2);
			
			pwm_2.ul_prescaler = PWM_CMR_CPRE_CLKB;
			pwm_2.ul_period = 1000;
			pwm_2.ul_duty = 500;
			pwm_2.channel = PWM_CHANNEL_2;
			pwm_channel_init(PWM, &pwm_2);
			
			pwm_channel_enable(PWM, PWM_CHANNEL_2);
			break;	
		case CHANNEL3 :
				pwm_channel_disable(PWM, PWM_CHANNEL_3);
						
				pwm_clock_t clock_setting_3 = {
					.ul_clka = 0,
					.ul_clkb = 25000 * 1000, 
					.ul_mck = sysclk_get_cpu_hz()
				};
				pwm_init(PWM, &clock_setting_3);
						
				pwm_3.ul_prescaler = PWM_CMR_CPRE_CLKB;
				pwm_3.ul_period = 1000;
				pwm_3.ul_duty = 500;
				pwm_3.channel = PWM_CHANNEL_3;
				pwm_channel_init(PWM, &pwm_3);

				pwm_channel_enable(PWM, PWM_CHANNEL_3);
			break;			
	}
	
}