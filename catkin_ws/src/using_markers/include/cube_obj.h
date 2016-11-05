
#ifndef CUBE_OBJ
#define CUBE_OBJ

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <using_markers/robotCommand.h>

class Cube : public visualization_msgs::Marker
{
protected:
  static int running_id;
  
public:
  Cube(double _x, double _y, double _z)
  {
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = running_id++;
    type = visualization_msgs::Marker::CUBE;

    lifetime = ros::Duration();

    //Set the pose position from the input arguments
    pose.position.x = _x;
    pose.position.y = _y;
    pose.position.z = _z;

    //Set all of the other values to their default
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;
    pose.orientation.w = 1.0;

    //1x1x1 here means 1m on a side
    scale.x = 1.0;
    scale.y = 1.0;
    scale.z = 1.0;

    //Be sure to set alpha to something non-zero!
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = 0.0f;
    color.a = 1.0;
  }

  void set_pos_x(const using_markers::robotCommand command);
};

#endif // MACRO
