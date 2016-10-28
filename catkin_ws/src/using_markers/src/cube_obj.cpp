
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include "cube_obj.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;
