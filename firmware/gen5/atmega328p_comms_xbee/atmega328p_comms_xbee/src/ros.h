/* ros.h
 * Jon Cruz
 */

#ifndef _ROS_H_
#define _ROS_H_

#include "ros_lib/ros/node_handle.h"
#include "Atmega328pHardware.h"

namespace ros {
	typedef ros::NodeHandle_<Atmega328pHardware, 25, 25, 100, 100> NodeHandle;
}

#endif