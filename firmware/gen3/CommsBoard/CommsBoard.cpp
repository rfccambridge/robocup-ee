#include <string.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/common.h>
#include <util/delay.h>
#include "SPIMaster.h"
#include "EELib.h"
#include "CommsBoard.h"
#include "SerialLib.h"
#include "Command.h"

// actual functions
bool message_to_command(const message &recvMsg, Command &c);
void handle_command(Command &c);
void handle_led_command(LEDCommand &c);
void handle_safe_mode_command(SafeModeCommand &c);
void handle_unknown_command(Command &c);

// eww, globals. make this a class at least
SPIMaster spi;

int main(void)
{
	// initialize display
	DDRC = 0xFF;
	PORTC = 0x00;
	
	// initalizing SPI
	
	//initializing serial comms
	initSerial();
	
	// TESTING MOTORBOARD
	bool result;
	char reply;
	while(true) {
		setBit(RLED1, true);
		for (uint8_t i = 0; i < 127; ++i) {
			WheelSpeedCommand c = WheelSpeedCommand(i, i, i, i);
			result = spi.SendCommand(spi.MOTOR_BOARD_SLAVE, c, &reply);
			setBit(GLED1, result);
			_delay_ms(250);
		}
		setBit(RLED1, false);
		for (uint8_t i = 127; i > 0; --i) {
			WheelSpeedCommand c = WheelSpeedCommand(i, i, i, i);
			result = spi.SendCommand(spi.MOTOR_BOARD_SLAVE, c, &reply);
			setBit(GLED1, result);
			_delay_ms(250);
		}
	}
	
	message recvMsg;
	while(true) {
		setBit(&PORTC, 6, true);
		int bytes = serialPopInbox(&recvMsg);
		
		// valid message?
		if (bytes == 0)
		{
			setBit(&PORTC, 3, true);
			continue;
		}
	
		// for us?
		char id = recvMsg.message[0];
		if (id != getBotID())
		{
			setBit(&PORTC, 2, true);
			continue;
		}
			
		// we're all good!
		setBit(&PORTC, 0, true);
		char source = recvMsg.message[1];
		char port = recvMsg.message[2];
		
		// cast into command
		Command c;
		bool valid = message_to_command(recvMsg, c);
		if (!valid)
			continue;

		// send message to correct place
		char reply;
		bool result;
		switch (source) {
			case 'c':
				// comms board
				handle_command(c);
				break;
			case 'w':
				// motor board
				result = spi.SendCommand(spi.MOTOR_BOARD_SLAVE, c, &reply);
				// TODO report on the reply, and result
				break;
			case 'v':
				// kicker board
				result = spi.SendCommand(spi.KICKER_BOARD_SLAVE, c, &reply);
				break;
			default:
				// unknown destination
				// handle error
				break;
		}
	}
}

// handles a command meant for the comms board
void handle_command(Command &c) {
	switch(c.GetType()) {
		case Command::SAFE_MODE_COMMAND: {
			SafeModeCommand sc = c;
			handle_safe_mode_command(sc);
			break;
		}
		case Command::LED_COMMAND: {
			LEDCommand lc = c;
			handle_led_command(lc);
			break;
		}
		default:
			handle_unknown_command(c);
			break;
	}
}

// processing individual commands
void handle_led_command(LEDCommand &c) {
	setBit(&PORTC, c.pin, c.status);
}

// pass along message to other two boards
void handle_safe_mode_command(SafeModeCommand &c) {
	char reply_m;
	char reply_k;
	spi.SendCommand(spi.MOTOR_BOARD_SLAVE, c, &reply_m);
	spi.SendCommand(spi.KICKER_BOARD_SLAVE, c, &reply_k);
}

void handle_unknown_command(Command &c) {
	// return some error message
	// TODO
}

// convert a serial message into an SPI command
// c is a reference to a command, not a pointer
bool message_to_command(const message &recvMsg, Command &c) {
	char source = recvMsg.message[1];
	char port = recvMsg.message[2];
	bool valid = true;
	// switch on message type
	switch(port) {
		case LEDCommand::key: {
			uint8_t pin = recvMsg.message[3];
			bool status = (bool)recvMsg.message[4];
			c = LEDCommand(pin, status);
			break;
		}
		case SafeModeCommand::key: {
			c = SafeModeCommand();
			break;
		}
		case WheelSpeedCommand::key: {
			int rf = recvMsg.message[3];
			int lf = recvMsg.message[4];
			int lb = recvMsg.message[5];
			int rb = recvMsg.message[6];
			c = WheelSpeedCommand(rf, lf, lb, rb);
			break;
		}
		case SetPIDCommand::key: {
			int k_p = recvMsg.message[3];
			int k_i = recvMsg.message[4];
			int k_d = recvMsg.message[5];
			c = SetPIDCommand(k_p, k_i, k_d);
			break;
		}
		case ChargeCommand::key: {
			uint8_t voltage = recvMsg.message[3];
			bool discharge = (bool)recvMsg.message[4];
			c = ChargeCommand(voltage, discharge);
			break;
		}
		case KickCommand::key: {
			uint8_t strength = recvMsg.message[3];
			bool breakbeam = (bool)recvMsg.message[4];
			c = KickCommand(strength, breakbeam);
			break;
		}
		case DribbleCommand::key: {
			uint8_t speed = recvMsg.message[3];
			c = DribbleCommand(speed);
			break;
		}
		default: {
			// unknown command
			setBit(&PORTC, 3, true);
			valid = false;
			break;
		}
	}
	return valid;
}