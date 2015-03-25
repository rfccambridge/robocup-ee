#ifndef __COMMAND_H__
#define __COMMAND_H__

class Command {
	// allow SPIMaster and SPISlave to access these protected variables
	friend class SPIMaster;
	friend class SPISlave;
protected:
	char m_commandType;
	char m_arg1;
	char m_arg2;
public:
	enum CommandType {
		WHEEL_SPEED_COMMAND
	};

	Command();
	Command(char commandType, char arg1, char arg2);
	char GetType();
};

class SetWheelSpeedCommand : public Command {
public:
	enum Wheel {
		WHEEL_LB,
		WHEEL_RB,
		WHEEL_LF,
		WHEEL_RF
	};

	SetWheelSpeedCommand(Wheel wheel, char speed);
	char GetWheel();
	char GetSpeed();
};

#endif //__COMMAND_H__
