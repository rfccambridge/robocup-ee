#include <ros/ros.h>

#include "game.h"
#include "shared_code.h"

int main(int argc, char** argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;

  ros::Rate loop_rate(RATE);

  //Instantiate a robot, ball, and field for us to use in the `Game`
  Game game(n);
  game.create_our_robot(RED_ID, 0, 0, 0);
  game.create_ball(BALL_ID, 5, 0, 0);
  game.create_field(FIELD_ID);

  while(ros::ok())
  {
    //Loop until all coms are alive
    while(ros::ok() && !Game::coms_alive())
    {
      printf("Game coms are down, trying to reconnect again...\n");
      Game::initialize_coms(n); //Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    //Process all of the callbacks
    ros::spinOnce();

    //Render all of the markers
    game.render_markers();

    //Sleep a bit between loops
    loop_rate.sleep();
  }
}
