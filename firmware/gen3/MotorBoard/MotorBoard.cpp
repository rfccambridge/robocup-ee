#include "MotorBoard.h"
#include "SPISlave.h"
#include "Motor.h"
#include <avr/io.h>
#include <avr/interrupt.h>

// used for controlling frequency at which we update quad encoders
int counter = 0;
bool inSafeMode = false;
Motor motors[4] = {Motor(OUTPUT1, TSENSE1, SENSE1),
				   Motor(OUTPUT2, TSENSE2, SENSE2),
				   Motor(OUTPUT3, TSENSE3, SENSE3),
				   Motor(OUTPUT4, TSENSE4, SENSE4)};
				   
int main(void)
{	
	SPISlave spi;
	Command* command;

	// setup defaults
	init();
	
	while(1) {
		PORTC ^= (1 << 0); // flip LED 0 every tick
		
		spi.ReceiveSPI(); // handle SPI state machine
		
		if (spi.GetCommand(command))
		{
			// a command has been transmitted
			PORTC |= (1 << 1); // turn on LED 1
			
			// do something with command
			if (command->GetType() == Command::LED_COMMAND) {
				LEDCommand& led_cmd = * (LEDCommand*)command;
				
				// set the appropriate LED
				setBit(&PORTC, led_cmd.pin, led_cmd.status);
			} 
			// ignore speed commands if in safe mode
			else if (command->GetType() == Command::WHEEL_SPEED_COMMAND && !inSafeMode) {
				SetWheelSpeedCommand& wheel_cmd = * (SetWheelSpeedCommand*)command;
				
				// set the speed of the appropriate wheel
				bool success = motors[(int)wheel_cmd.wheel].setSpeed(wheel_cmd.speed);
				if (!success) {
					// something went wrong with setting the speed, send a bad reply
				}
			} else if (command->GetType() == Command::SAFE_MODE_COMMAND) {
				inSafeMode = true;
				safeMode();
			}
			// we shouldn't be receiving other types of commands (i.e. charge, kick dribble)
			else {
				// TODO: send some sort of bad reply
			}
			
			// send an "OK" reply
			spi.SetReply(0x42);
			
		}
		else {
			// no command 
		}
		
		// update the motors and the duty cycles
		for (int i = 0; i < 4; i++) {
			double duty = motors[i].update();
			
			// enter safemode if the status is anything other than OK
			if (motors[i].getStatus() != STATUS_OK){
				safeMode();
			}
			
			setDutyCycle((PWM) i, duty);
		}
	}
}

// Interrupt handler for timer1 overflow, should fire at 31.25 kHz
ISR(TIMER1_OVF_vect) {
	// only do anything every 250 cycles so that we go from 31.25kHz -> 125Hz
	if (++counter > 250) {
		counter = 0;
		for (int i = 0; i < 4; i++) {
			motors[i].handleQEI();
		}
	}
}

void setBrake(bool enable)
{
	setBit(BREN, !enable); 
}

void setDirection(PWM pwmNum, bool dir)
{
	switch (pwmNum)
	{
		case OUTPUT1:
			setBit(PWM1, dir);
			break;
		case OUTPUT2:
			setBit(PWM2, dir);
			break;
		case OUTPUT3:
			setBit(PWM3, dir);
			break;
		case OUTPUT4:
			setBit(PWM4, dir);
			break;
	}
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
	
	// enable interrupts
	sei();
	
	// disable brake
	setBrake(false);
}