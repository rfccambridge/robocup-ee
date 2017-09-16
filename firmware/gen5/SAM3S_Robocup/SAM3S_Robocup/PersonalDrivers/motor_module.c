/******************************
 * Includes
 ******************************/
#include <RobocupDrivers.h>
#include <asf.h>


/******************************
 * Private Data Types
 ******************************/

// Direction of motion for motor
typedef enum direction {
	FORWARD,
	REVERSE
}Direction;

// motor structure
typedef struct motor {
	
	// motor channel - do not change once initialized
	Channel motor_channel;
	
	// motor speed - need to do sync up with others on how we will be representing speed in our data transfer
	uint8_t speed;
	
	// motor direction element
	Direction motor_direction;
	
}Motor;


/******************************
 * Static Data Declarations
 ******************************/
static Motor robotMotors[4] = { { 0 } };
const static Channel motorChannels[4] = {CHANNEL0, CHANNEL1, CHANNEL2, CHANNEL3};

/******************************
 * Private Functions Prototypes
 ******************************/

void update_speed(uint8_t motorID, uint32_t speed);
void attach_motor(uint8_t motorID);

/******************************
 * Private Functions Bodies
 ******************************/

// Initialize all motors with speed zero and forward direction - attach each to unique pwm channel
void initialize_motors() {
	
	for (int motorID = 0; motorID < sizeof(robotMotors) / sizeof(Motor); motorID++)
	{	
		// set each motor to a unique pwm channel
		robotMotors[motorID].motor_channel = motorChannels[motorID];
		// initialize motor direction as forward and speed 0
		robotMotors[motorID].motor_direction = FORWARD;
		robotMotors[motorID].speed = 0;
		
		// attach motor to the appropriate pwm channel
		attach_motor(motorID);
	}
}

void update_speed(uint8_t motorID, uint32_t speed)
{
	if(speed > 1000)
		speed = 1000;
	else if (speed < 0)
		speed = 0;
	update_duty_cycle(speed, robotMotors[motorID].motor_channel);	
}

/*
*	Attaches motor struct, m, to the pwm channel specified by channelValue and enables the pwm channel.
*/
void attach_motor(uint8_t motorID) {

	Motor m = robotMotors[motorID];
	
	switch(m.motor_channel){
		case CHANNEL0 :
		
		// disable PWM channel in order to change clock configuration, then initialize PWM module clock details
		pwm_channel_disable(PWM, PWM_CHANNEL_0);

		pwm_clock_t clock_setting_0 = {
			.ul_clka = 0,
			.ul_clkb = 25000 * 1000, // this gives us approximately a 30kHz signal (perfect for the DVR motor controllers which require freq between 16kHz and 50kHz
			.ul_mck = sysclk_get_cpu_hz()
		};
		pwm_init(PWM, &clock_setting_0);
		
		// specify channel settings and initialize
		pwm_0.ul_prescaler = PWM_CMR_CPRE_CLKB;
		pwm_0.ul_period = 1000;
		pwm_0.ul_duty = 100;
		pwm_0.channel = PWM_CHANNEL_0;
		pwm_channel_init(PWM, &pwm_0);
		
		// finally, enable pwm channel
		pwm_channel_enable(PWM, PWM_CHANNEL_0);
		break;
		case CHANNEL1 :
		pwm_channel_disable(PWM, PWM_CHANNEL_1);
		
		pwm_clock_t clock_setting_1 = {
			.ul_clka = 0,
			.ul_clkb = 25000 * 1000,
			.ul_mck = sysclk_get_cpu_hz()
		};
		pwm_init(PWM, &clock_setting_1);

		pwm_1.ul_prescaler = PWM_CMR_CPRE_CLKB;
		pwm_1.ul_period = 1000;
		pwm_1.ul_duty = 500;
		pwm_1.channel = PWM_CHANNEL_1;
		pwm_channel_init(PWM, &pwm_1);
		pwm_channel_enable(PWM, PWM_CHANNEL_1);
		break;
		case CHANNEL2 :
		pwm_channel_disable(PWM, PWM_CHANNEL_2);
		
		pwm_clock_t clock_setting_2 = {
			.ul_clka = 0,
			.ul_clkb = 25000 * 1000,
			.ul_mck = sysclk_get_cpu_hz()
		};
		pwm_init(PWM, &clock_setting_2);
		
		pwm_2.ul_prescaler = PWM_CMR_CPRE_CLKB;
		pwm_2.ul_period = 1000;
		pwm_2.ul_duty = 500;
		pwm_2.channel = PWM_CHANNEL_2;
		pwm_channel_init(PWM, &pwm_2);
		
		pwm_channel_enable(PWM, PWM_CHANNEL_2);
		break;
		case CHANNEL3 :
		pwm_channel_disable(PWM, PWM_CHANNEL_3);
		
		pwm_clock_t clock_setting_3 = {
			.ul_clka = 0,
			.ul_clkb = 25000 * 1000,
			.ul_mck = sysclk_get_cpu_hz()
		};
		pwm_init(PWM, &clock_setting_3);
		
		pwm_3.ul_prescaler = PWM_CMR_CPRE_CLKB;
		pwm_3.ul_period = 1000;
		pwm_3.ul_duty = 500;
		pwm_3.channel = PWM_CHANNEL_3;
		pwm_channel_init(PWM, &pwm_3);

		pwm_channel_enable(PWM, PWM_CHANNEL_3);
		break;
	}
	
}

void update_motor_speeds(uint32_t speed0, uint32_t speed1, uint32_t speed2, uint32_t speed3)
{
	uint32_t speeds[4] = {speed0, speed1, speed2, speed3};
		
	for (int motorID = 0; motorID < sizeof(robotMotors) / sizeof(Motor); motorID++)
	{
		update_speed(motorID, speeds[motorID]);
	}
}
