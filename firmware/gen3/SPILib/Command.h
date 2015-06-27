#ifndef __COMMAND_H__
#define __COMMAND_H__
#include <inttypes.h>
struct Command {
	friend class SPIMaster;
	friend class SPISlave;
protected:
	uint8_t m_commandType;
	uint8_t m_arg1;
	uint8_t m_arg2;
	uint8_t m_arg3;
	uint8_t m_arg4;
public:
	enum CommandType {
		SAFE_MODE_COMMAND,
		LED_COMMAND,
		WHEEL_SPEED_COMMAND,
		SET_PID_COMMAND,
		CHARGE_COMMAND,
		KICK_COMMAND,
		DRIBBLE_COMMAND
	};

	Command();
	Command(uint8_t commandType, uint8_t arg1, uint8_t arg2);
	Command(uint8_t commandType, uint8_t arg1, uint8_t arg2, uint8_t arg3, uint8_t arg4);
	uint8_t GetType();
};

// puts board into a safe mode when an error occurs
// for instance, turning off motors, discharging
struct SafeModeCommand : public Command {
	static const char key = 's';
	SafeModeCommand();
};

// blinks an LED on another board
struct LEDCommand : public Command {
	static const char key = 'l';
	uint8_t& pin;
	bool& status;
	LEDCommand(uint8_t pin_, bool status_);
};

// sets the desired wheelspeed for one wheel
struct WheelSpeedCommand : public Command {
	static const char key = 'w';
	uint8_t& speed_rf;
	uint8_t& speed_lf;
	uint8_t& speed_lb;
	uint8_t& speed_rb;
	WheelSpeedCommand(uint8_t rf, uint8_t lf, uint8_t lb, uint8_t rb);
};

// override PID values for debugging
struct SetPIDCommand : public Command {
	static const char key = 'f';
	uint8_t& k_p;
	uint8_t& k_i;
	uint8_t& k_d;
	SetPIDCommand(uint8_t p, uint8_t i, uint8_t d);
};

// charges the capacitors
// voltage: target voltage (volts)
// discharge: whether to discharge the caps when higher
struct ChargeCommand : public Command {
	static const char key = 'c';
	uint8_t& voltage;
	bool& discharge;
	ChargeCommand(uint8_t voltage_, bool discharge_);
};

// kick the ball
// power: 0 -> 256 scale
// breakbeam: true to wait for the breakbeam
struct KickCommand : public Command {
	static const char key = 'k';
	uint8_t& power;
	bool& breakbeam;
	KickCommand(uint8_t power_, bool breakbeam_);
};

// set the dribbler speed
struct DribbleCommand : public Command {
	static const char key = 'd';
	uint8_t& speed;
	DribbleCommand(uint8_t speed_);
};
	
// [] set wheelspeed
// [] safe shutdown
// [] charge
// [] kick
// [] dribbler speed


#endif //__COMMAND_H__
