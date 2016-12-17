
#include <ros/ros.h>
#include <stdio.h>

#include "cube_interface.h"
#include "shared_code.h"

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "command_publisher");

  ros::NodeHandle n;
  CubeInterface::initialize_coms(n); //Initialize the communication interface for the cubes

  ros::Rate loop_rate(RATE);

  //TODO: make this more how it should be
  CubeInterface c1(RED);
  c1.goto_xy_pos(10, 10);

  while(ros::ok())
  {
    //Loop until all coms are alive
    while(ros::ok() && !CubeInterface::coms_alive())
    {
      printf("CubeInterface coms are down, trying to reconnect again...\n");
      CubeInterface::initialize_coms(n); //Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    c1.spin();

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
