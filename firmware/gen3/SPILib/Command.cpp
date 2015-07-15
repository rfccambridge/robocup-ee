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
SafeModeCommand::SafeModeCommand(const Command &c) :
Command(c) {
}

// LED blinking commands
LEDCommand::LEDCommand(uint8_t pin_, bool status_) : 
	Command(LED_COMMAND, pin_, status_), 
	pin(m_arg1), 
	status((bool&)m_arg2) {
}
LEDCommand::LEDCommand(const Command &c) :
	Command(c),
	pin(m_arg1),
	status((bool&)m_arg2) {
}

// Wheel speed commands
WheelSpeedCommand::WheelSpeedCommand(uint8_t rf, uint8_t lf, uint8_t lb, uint8_t rb) : 
	Command(WHEEL_SPEED_COMMAND, rf, lf, lb, rb),
	speed_rf(m_arg1),
	speed_lf(m_arg2),
	speed_lb(m_arg3),
	speed_rb(m_arg4) {
}
WheelSpeedCommand::WheelSpeedCommand(const Command &c) :
	Command(c),
	speed_rf(m_arg1),
	speed_lf(m_arg2),
	speed_lb(m_arg3),
	speed_rb(m_arg4) {
}

SetPIDCommand::SetPIDCommand(uint8_t p, uint8_t i, uint8_t d) :
	Command(SET_PID_COMMAND, p, i, d, 0),
	k_p(m_arg1),
	k_i(m_arg2),
	k_d(m_arg3) {
}
SetPIDCommand::SetPIDCommand(const Command &c) :
	Command(c),
	k_p(m_arg1),
	k_i(m_arg2),
	k_d(m_arg3) {
}

// Charging command
ChargeCommand::ChargeCommand(uint8_t voltage_, bool discharge_) :
	Command(CHARGE_COMMAND, voltage_, discharge_),
	voltage(m_arg1),
	discharge((bool&)m_arg2) {
}
ChargeCommand::ChargeCommand(const Command &c) :
	Command(c),
	voltage(m_arg1),
	discharge((bool&)m_arg2) {
}

// kick command
KickCommand::KickCommand(uint8_t power_, bool breakbeam_) :
	Command(KICK_COMMAND, power_, breakbeam_),
	power(m_arg1),
	breakbeam((bool&)m_arg2) {
}
KickCommand::KickCommand(const Command &c) :
	Command(c),
	power(m_arg1),
	breakbeam((bool&)m_arg2) {
}

// dribbler command
DribbleCommand::DribbleCommand(uint8_t speed_) :
	Command(DRIBBLE_COMMAND, speed, 0), 
	speed(m_arg1) {
}
DribbleCommand::DribbleCommand(const Command &c) :
	Command(c),
	speed(m_arg1) {
}