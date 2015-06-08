#include "Command.h"

Command::Command() {
}

Command::Command(uint8_t commandType, uint8_t arg1, uint8_t arg2) {
	m_commandType = commandType;
	m_arg1 = arg1;
	m_arg2 = arg2;
}

uint8_t Command::GetType() {
	return m_commandType;
}

// Safety commands
SafeModeCommand::SafeModeCommand() :
	Command(SAFE_MODE_COMMAND, 0, 0) {
}

// LED blinking commands
LEDCommand::LEDCommand(uint8_t pin_, bool status_) : 
	Command(LED_COMMAND, pin_, status_), 
	pin(m_arg1), 
	status((bool&)m_arg2) {
}

// Wheel speed commands
SetWheelSpeedCommand::SetWheelSpeedCommand(Wheel wheel_, uint8_t speed_) : 
	Command(WHEEL_SPEED_COMMAND, wheel_, speed_),
	wheel((Wheel&)m_arg1),
	speed(m_arg2) {
}

// Charging command
ChargeCommand::ChargeCommand(uint8_t voltage_, bool discharge_) :
	Command(CHARGE_COMMAND, voltage_, discharge_),
	voltage(m_arg1),
	discharge((bool&)m_arg2) {
}

// kick command
KickCommand::KickCommand(uint8_t power_, bool breakbeam_) :
	Command(KICK_COMMAND, power_, breakbeam_),
	power(m_arg1),
	breakbeam((bool&)m_arg2) {
}

// dribbler command
DribbleCommand::DribbleCommand(uint8_t speed_) :
	Command(DRIBBLE_COMMAND, speed, 0), 
	speed(m_arg1){
}