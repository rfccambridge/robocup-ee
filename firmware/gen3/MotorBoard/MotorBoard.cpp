#include "MotorBoard.h"
#include "SPISlave.h"
#include "Motor.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// used for controlling frequency at which we update pid
int counter = 0;
const int COUNTER_MAX = 250;
const double dt = 31250.0 / COUNTER_MAX;

bool inSafeMode = false;
Motor motors[4] = {Motor(OUTPUT1, TSENSE1, SENSE1),
				   Motor(OUTPUT2, TSENSE2, SENSE2),
				   Motor(OUTPUT3, TSENSE3, SENSE3),
				   Motor(OUTPUT4, TSENSE4, SENSE4)};
				   
// used to save the value of portE so that we can
// figure out which pin change(s) triggered the external interrupt
volatile uint8_t portEPrev = 0xFF;

// returns the reply to send
int handle_command(Command &command);
   
int main(void)
{	
	SPISlave spi;
	Command command;

	// setup defaults
	init();
	
	while(1) {
		
		spi.ReceiveSPI(); // handle SPI state machine
		
		// handle received message
		if (spi.GetCommand(command)) {
			spi.SetReply(handle_command(command));			
		}
		/*
		// update the motors and the duty cycles
		for (int i = 0; i < 4; i++) {
			motors[i].update();
			
			// enter safemode if the status is anything other than OK
			if (motors[i].getStatus() != STATUS_OK){
				safeMode();
			}
		}*/
	}
}

// returns the reply to send
int handle_command(Command &command) {
	// a command has been transmitted
		
	// do something with command
	if (command.GetType() == Command::LED_COMMAND) {
		LEDCommand led_cmd = (LEDCommand)command;
		
		// set the appropriate LED
		setBit(&PORTC, led_cmd.pin, led_cmd.status);
	}
	// ignore speed commands if in safe mode
	else if (command.GetType() == Command::WHEEL_SPEED_COMMAND && !inSafeMode) {
		WheelSpeedCommand wheel_cmd = (WheelSpeedCommand)command;
		
		if (wheel_cmd.speed_lb > 65) {
			PORTC = 0xFF;
		}
		else {
			PORTC = 0x00;
		}
		
		
		
		setDutyCycle(OUTPUT1, wheel_cmd.speed_lb / 127.0);
		setDutyCycle(OUTPUT2, wheel_cmd.speed_rb / 127.0);
		setDutyCycle(OUTPUT3, wheel_cmd.speed_lf / 127.0);
		setDutyCycle(OUTPUT4, wheel_cmd.speed_rf / 127.0);
		/*
		// set the speed of the appropriate wheel
		bool s_lb = motors[0].setSpeed(wheel_cmd.speed_lb);
		bool s_rb = motors[1].setSpeed(wheel_cmd.speed_rb);
		bool s_lf = motors[2].setSpeed(wheel_cmd.speed_lf);
		bool s_rf = motors[3].setSpeed(wheel_cmd.speed_rf);
		bool success = s_lb && s_rb && s_lf && s_rf;
		if (!success) {
			// something went wrong with setting the speed, return a bad reply
		}
		*/
	} 
	else if (command.GetType() == Command::SAFE_MODE_COMMAND) {
		inSafeMode = true;
		safeMode();
	}
	// we shouldn't be receiving other types of commands (i.e. charge, kick dribble)
	else {
		// TODO: return some sort of bad reply
	}
	
	// return an "OK" reply
	return 0x42;
}

// Interrupt handler for timer1 overflow, should fire at 31.25 kHz
ISR(TIMER1_OVF_vect) {
	// only do anything every 250 cycles so that we go from 31.25kHz -> 125Hz
	if (++counter > COUNTER_MAX) {
		counter = 0;
		for (int i = 0; i < 4; i++) {
			//setDutyCycle((PWM) i, motors[i].getDutyCycle(dt));
		}
	}
}

ISR (PCINT0_vect) {
	uint8_t changedbits = PINE ^ portEPrev;
	portEPrev = PINE;

	if (changedbits & (1 << PE0)) {
		motors[0].handleQEI();
	}

	if (changedbits & (1 << PE1)) {
		motors[0].handleQEI();
	}

	if (changedbits & (1 << PE2)) {
		motors[1].handleQEI();
	}
	
	if (changedbits & (1 << PE3)) {
		motors[1].handleQEI();
	}
	
	if (changedbits & (1 << PE4)) {
		motors[2].handleQEI();
	}

	if (changedbits & (1 << PE5)) {
		motors[2].handleQEI();
	}
	
	if (changedbits & (1 << PE6)) {
		motors[3].handleQEI();
	}
	
	if (changedbits & (1 << PE7)) {
		motors[3].handleQEI();
	}
}

void setBrake(bool enable) {
	setBit(BREN, !enable); 
}

void safeMode() {
	inSafeMode = true;
	setDutyCycle(OUTPUT1, 0);
	setDutyCycle(OUTPUT2, 0);
	setDutyCycle(OUTPUT3, 0);
	setDutyCycle(OUTPUT4, 0);
	setBrake(true);
}

void init(void) {
	// Set system clock prescale factor to 2, so the clock will run at 8 MHz,
	// making the PWM frequency 8 MHz / 256 = 31.25 kHz
	CLKPR = (1 << CLKPCE);
	CLKPR = (1 << CLKPS0);
	
	
	DDRB = (0 << SS_M.pin) | (0 << SCK.pin) | (0 << MOSI.pin) | (1 << MISO.pin);
	DDRB |= (1 << PWM1.pin) | (1 << PWM2.pin) | (1 << PWM3.pin) | (1 << PWM4.pin);
	
	// enable LED's as output, make sure they're all off
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// Enable break and dir pins as output
	DDRD = 0xFF;
	
	// enable quad encoder pins as input
	DDRE = 0x00;
	// turn on pull-up to avoid noise triggering interrupts
	PORTE = 0xFF;
	
	// enable sense pins as input
	DDRF = 0x00;
	
	// enable fault and reset pins as input
	DDRG = 0x00;
	
	// turn on ADC
	setUpADC();
	
	// disable interrupts while messing with timer settings
	cli();
	
	// enable pwm with 0% duty cycle
	enablePWM(OUTPUT1);
	enablePWM(OUTPUT2);
	enablePWM(OUTPUT3);
	enablePWM(OUTPUT4);
	
	// disable input capture and output match interrupt, enable overflow interrupt
	TIMSK1 = (0 << ICIE1) | (0 << OCIE1B) | (0 << OCIE1A) | (1 << TOIE1);
	
	// Enable external interrupts on PORTE
	EIMSK |= (1 << PCIE0);
	PCMSK0 = 0xFF;
	
	// enable interrupts
	sei();
	
	// disable brake
	setBrake(false);
}