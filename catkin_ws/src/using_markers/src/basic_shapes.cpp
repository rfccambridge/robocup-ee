
#include <ros/ros.h>

#include "shared_code.h"
#include "cube_obj.h"

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  Cube::initialize_coms(n);

  ros::Rate loop_rate(RATE);

  //Instantiate a cube for us to move
  Cube cube(0, 0, 0);
	
  while(ros::ok())
  {
    //Loop until all coms are alive
    while(ros::ok() && !Cube::coms_alive())
    {
      printf("Cube coms are down, trying to reconnect again...\n");
      Cube::initialize_coms(n); //Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    //Render all of the cubes
    Cube::render_cubes();

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
