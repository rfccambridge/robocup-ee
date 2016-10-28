
#include <ros/ros.h>
#include <std_msgs/Int8.h>
#include <visualization_msgs/Marker.h>

#include "cube_obj.h"

//TODO: This is BAD!!!
int x_pos = 0;

void subscriber_callback(const std_msgs::Int8 i)
{
  printf("Received %d\n", x_pos = i.data);
}

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  ros::Rate loop_rate(30);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  //Provides data for the coords of our marker
  ros::Subscriber sub = n.subscribe("chatter", 1000, subscriber_callback);

  uint32_t shape = visualization_msgs::Marker::CUBE;
  while(ros::ok())
  {
    Cube cube(0, 0, 0);

    //Make sure to publish the down-casted `cube`
    marker_pub.publish((visualization_msgs::Marker)cube);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
