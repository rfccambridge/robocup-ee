#include <ros/ros.h>

#include "game.h"
#include "shared_code.h"

int main(int argc, char** argv)
{
  // Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;

  ros::Rate loop_rate(RATE);
  // Instantiate a cube for us to move
  Game game(n);
  game.create_cube(RED, 0, 0, 0);

  while(ros::ok())
  {
    // Loop until all coms are alive
    while(ros::ok() && !Game::coms_alive())
    {
      printf("Cube coms are down, trying to reconnect again...\n");
      Game::initialize_coms(n); // Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    // Render all of the markers
    game.render_markers();

    // Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
