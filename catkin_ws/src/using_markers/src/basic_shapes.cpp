
#include <ros/ros.h>

#include "cube_obj.h"

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  ros::Rate loop_rate(1000);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  //Instantiate a cube for us to move
  Cube cube(n, 0, 0, 0);
	
  uint32_t shape = visualization_msgs::Marker::CUBE;
  while(ros::ok())
  {
    //Make sure to publish the down-casted `cube`
    marker_pub.publish((visualization_msgs::Marker)cube);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
