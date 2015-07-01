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
bool handle_command(const Command &c);
bool message_to_command(const message &recvMsg, Command &c);
void handle_led_command(const LEDCommand &c);
void handle_safe_mode_command();
void handle_unknown_command(const Command &c);

int main(void)
{
	// initialize display
	DDRC = 0xFF;
	PORTC = 0x00;
	//initializing serial comms
	initSerial();
	message recvMsg;
	while(true) {
		setBit(&PORTC, 7, true);
		int bytes = serialPopInbox(&recvMsg);
		
		// valid message?
		if (bytes == 0) 
			continue;
	
		// for us?
		char id = recvMsg.message[0];
		if (id != getBotID()) 
			continue;
			
		// we're all good!
		setBit(&PORTC, 0, true);
		char source = recvMsg.message[1];
		char port = recvMsg.message[2];
		
		// cast into command
		Command c;
		bool valid = message_to_command(recvMsg, c);
		if (~valid)
			continue;
				
		// send message to correct place
		switch (source) {
			case 'c':
				// comms board
				handle_command(c);
				break;
			case 'w':
				// motor board
				break;
			case 'v':
				// kicker board
				break;
			default:
				// unknown destination
				// handle error
				break;
		}
	}
}

// handles a command meant for the comms board
bool handle_command(Command &c) {
	switch(c.GetType()) {
		case Command::SAFE_MODE_COMMAND:
			handle_safe_mode_command();
			break;
		case Command::LED_COMMAND:
			handle_led_command((LEDCommand)c);
			break;
		default:
			handle_unknown_command(c);
			break;
	}
}

// processing individual commands
void handle_led_command(const LEDCommand &c) {
	setBit(&PORTC, c.pin, c.status);
}

void handle_safe_mode_command() {
	// pass along message to other two boards
	// TODO
}

void handle_unknown_command(const Command &c) {
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