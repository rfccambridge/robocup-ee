
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

#include "cube_obj.h"

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  ros::Rate loop_rate(30);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  //Instantiate a cube for us to move
  Cube cube(0, 0, 0);

  //Register this cube's x coords to change according to the influx of messages from "chatter"
  ros::Subscriber sub = n.subscribe("chatter", 1000, &Cube::set_pos_x, &cube);

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
