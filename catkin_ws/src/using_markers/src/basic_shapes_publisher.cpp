
#include <ros/ros.h>
#include <stdio.h>

#include "robot_interface.h"
#include "shared_code.h"

int main(int argc, char** argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "command_publisher");

  ros::NodeHandle n;
  RobotInterface::initialize_coms(n); //Initialize the communication interface for our robots

  ros::Rate loop_rate(RATE);

  RobotInterface r1(RED_ID);
  r1.goto_xy_pos(10, 10);

  while(ros::ok())
  {
    //Loop until all coms are alive
    while(ros::ok() && !RobotInterface::coms_alive())
    {
      printf("RobotInterface coms are down, trying to reconnect again...\n");
      RobotInterface::initialize_coms(n); //Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    r1.spin();

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }

  return 0;
}
