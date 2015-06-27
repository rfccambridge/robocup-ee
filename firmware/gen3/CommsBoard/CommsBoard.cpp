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

int main(void)
{
	// initialize display
	DDRC = 0xFF;
	PORTC = 0x00;
	
	//initializing serial comms
	initSerial();
	message recvMsg;
	
	while(true) {
		int bytes = serialPopInbox(&recvMsg);
		if(bytes != 0) {
			// Use the received message.
			char id = recvMsg.message[0];
			if (id == getBotID()) {
				char source = recvMsg.message[1];
				char port = recvMsg.message[2];
				Command c;
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
						valid = false;
						break;
					}
				}
				
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
	}
}