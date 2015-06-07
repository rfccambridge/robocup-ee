#include "Command.h"

Command::Command() {
}


Command::Command(char commandType, char arg1, char arg2) {
	m_commandType = commandType;
	m_arg1 = arg1;
	m_arg2 = arg2;
}

char Command::GetType() {
	return m_commandType;
}

// Wheel speed commands
SetWheelSpeedCommand::SetWheelSpeedCommand(Wheel wheel, char speed) : Command(WHEEL_SPEED_COMMAND, wheel, speed) {
}

char SetWheelSpeedCommand::GetWheel() {
	return m_arg1;
}

char SetWheelSpeedCommand::GetSpeed() {
	return m_arg2;
}

// LED blinking commands
LEDCommand::LEDCommand(int pin, bool status) : Command(LED_COMMAND, pin, status) {
}

int LEDCommand::getPin() {
	return m_arg1;
}

bool LEDCommand::getStatus() {
	return m_arg2;
}