#ifndef _ROS_H_
#define _ROS_H_

#include "ros/node_handle.h"
#include "atmega328p.h"

namespace ros {
	typedef ros::NodeHandle_<Atmega328p> NodeHandle;
}

#endif