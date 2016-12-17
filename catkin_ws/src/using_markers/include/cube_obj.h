
#ifndef CUBE_OBJ
#define CUBE_OBJ

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

class Cube : public visualization_msgs::Marker
{

public:
  Cube(int robot_id, double _x, double _y, double _z)
  {
    // All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = robot_id; // Set the `Marker` id based on the input `robot_id`
    type = visualization_msgs::Marker::CUBE;

    lifetime = ros::Duration();

    // Set the pose position from the input arguments
    pose.position.x = _x;
    pose.position.y = _y;
    pose.position.z = _z;

    // Set all of the other values to their default
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;
    pose.orientation.w = 1.0;

    // 1x1x1 here means 1m on a side
    scale.x = 1.0;
    scale.y = 1.0;
    scale.z = 1.0;

    // Be sure to set alpha to something non-zero!
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = 0.0f;
    color.a = 1.0;
  }
};

#endif // MACRO
