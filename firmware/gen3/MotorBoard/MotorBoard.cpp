#include "MotorBoard.h"
#include "SPISlave.h"
#include "Motor.h"

int main(void)
{	
	SPISlave spi;
	Command* command;
	Motor motors[4] = {Motor(OUTPUT1, TSENSE1, SENSE1),
					   Motor(OUTPUT2, TSENSE2, SENSE2),
					   Motor(OUTPUT3, TSENSE3, SENSE3),
					   Motor(OUTPUT4, TSENSE4, SENSE4)};

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
			else if (command->GetType() == Command::WHEEL_SPEED_COMMAND) {
				SetWheelSpeedCommand& wheel_cmd = * (SetWheelSpeedCommand*)command;
				
				// set the speed of the appropriate wheel
				bool success = motors[(int)wheel_cmd.wheel].setSpeed(wheel_cmd.speed);
				if (!success) {
					// something went wrong with setting the speed
				}
			} else if (command->GetType() == Command::SAFE_MODE_COMMAND) {
				safeMode();
			}
			// we shouldn't be receiving other types of commands (i.e. charge, kick dribble)
			else {
				// send some sort of bad reply
			}
			
			// send a reply
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
	/*
	while(1) {
		PORTC ^= 0x02; // flip 2nd LED
		
		bool hasCommand = spi.GetCommand(&command);
		if(hasCommand)
		{
			PORTC |= 0x04; // turn on 3rd LED
			char reply = 0;
			switch(command.GetType())
			{
				case Command::WHEEL_SPEED_COMMAND:
					//SetWheelSpeedCommand* c = (SetWheelSpeedCommand*)&command;
					// TODO: execute command
				break;
			
				case Command::LED_COMMAND:
					PORTC |= 0x08; // turn on 4th LED
					LEDCommand* c2 = (LEDCommand*)&command;
					int pin = c2->getPin();
					bool on = c2->getStatus();
				
					// turn on / off LED
					
					if (on) {
						PORTC |= 1 << pin;
					}
					else {
						PORTC &= ~(1 << pin);
					}
			}
			
			spi.SetReply(reply);
		}
		else {
			// no command
			PORTC &= ~(0x04); // turn off 3rd LED
		}
		_delay_ms(100);
	}
	*/
}

void init(void) {
	// Disable system clock prescaling (max clock frequency)
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
	
	// enable pwm with 0% duty cycle
	enablePWM(OUTPUT1);
	enablePWM(OUTPUT2);
	enablePWM(OUTPUT3);
	enablePWM(OUTPUT4);
	
	// disable brake
	setBrake(false);
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

// TODO: how to make sure that we stay in safemode
void safeMode() {
	setDutyCycle(OUTPUT1, 0);
	setDutyCycle(OUTPUT2, 0);
	setDutyCycle(OUTPUT3, 0);
	setDutyCycle(OUTPUT4, 0);
	setBrake(true);
}