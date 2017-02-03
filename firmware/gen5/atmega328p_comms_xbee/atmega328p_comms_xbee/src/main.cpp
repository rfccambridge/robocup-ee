/*
 * atmega328p_comms_xbee.cpp
 *
 * Created: 1/29/2017 14:46:12
 * Author : Jon Cruz
 */ 

#include "ros.h"
#include "ros_lib/std_msgs/String.h"

extern "C" {
	#include <util/delay.h>
}

// Needed for AVR to use virtual functions
extern "C" void __cxa_pure_virtual(void);
void __cxa_pure_virtual(void);

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter_test("chatter_test", &str_msg);

char hello[13] = "hello world!";

int main(void)
{
	uint32_t prev_time = 0UL;
	
	// Initialize ROS
	nh.initNode();
	nh.advertise(chatter_test);
	
    while (1) {
		// Send message each second
		if (avr_time_now() - prev_time > 1000) {
			str_msg.data = hello;
			chatter_test.publish(&str_msg);
			prev_time = avr_time_now();
		}
		nh.spinOnce();
    }
	return 0;
}

