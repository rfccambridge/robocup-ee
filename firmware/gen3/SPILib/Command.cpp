#include "Command.h"

Command::Command() {
}

Command::Command(uint8_t commandType, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4) {
	m_commandType = commandType;
	m_arg1 = arg1;
	m_arg2 = arg2;
	m_arg3 = arg3;
	m_arg4 = arg4;
}

// delegating constructor
Command::Command(uint8_t commandType, uint8_t arg1, uint8_t arg2) :
	Command(commandType, arg1, arg2, 0, 0) {
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
SetWheelSpeedCommand::SetWheelSpeedCommand(uint8_t lb, uint8_t rb, uint8_t lf, uint8_t rf) : 
	Command(WHEEL_SPEED_COMMAND, lb, rb, lf, rf),
	speed_lb(m_arg1),
	speed_rb(m_arg2),
	speed_lf(m_arg3),
	speed_rf(m_arg4) {
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