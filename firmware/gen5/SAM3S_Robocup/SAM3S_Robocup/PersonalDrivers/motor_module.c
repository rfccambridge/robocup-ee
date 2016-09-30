#include <RobocupDrivers.h>
#include <asf.h>

// Attaches motor to specified channel and initializes to default speed and direction (0,FORWARD)
void initialize_motor(Motor *m, Channel chan) {
	m->motor_channel = chan;
	m->motor_direction = FORWARD;
	m->speed = 0;	
	
	attach_motor(m);
}