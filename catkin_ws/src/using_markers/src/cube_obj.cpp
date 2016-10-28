
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include "cube_obj.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;

void Cube::set_pos_x(const std_msgs::Int8 _x)
{
  printf("Setting x position to: %d\n", _x.data);
  pose.position.x = _x.data;
}
