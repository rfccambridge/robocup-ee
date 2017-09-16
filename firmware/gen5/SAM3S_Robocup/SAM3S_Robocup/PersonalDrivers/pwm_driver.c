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

void update_duty_cycle(uint32_t duty_cycle, Channel chan) {
	// set update duty cycle register to specified duty cycle. Duty cycle will change on next duty cycle period due to double buffering system
	switch(chan)
	{
		case CHANNEL0:
			pwm_channel_update_duty(PWM,&pwm_0,duty_cycle);
			break;		
		case CHANNEL1:
			pwm_channel_update_duty(PWM,&pwm_1,duty_cycle);
			break;
		case CHANNEL2:
			pwm_channel_update_duty(PWM,&pwm_2,duty_cycle);
			break;
		case CHANNEL3:
			pwm_channel_update_duty(PWM,&pwm_3,duty_cycle);
			break;
	}
}