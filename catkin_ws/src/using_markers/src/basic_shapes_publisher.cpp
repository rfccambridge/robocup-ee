
#include <stdio.h>
#include <ros/ros.h>

#include "shared_code.h"



int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "command_publisher");

  ros::Rate loop_rate(RATE);

  ros::NodeHandle n;
  CubeInterface::initialize_coms(n); //Initialize the communication interface for the cubes

  while(ros::ok())
  {
    //Request the cube's position with ID of 0
    using_markers::robotPosSrv srv;
    srv.request.robotID = 0;

    //Loop until `pos_client` connects
    while(ros::ok() && !CubeInterface::coms_alive())
    {
      printf("Unable to connect the pos client, trying to reconnect again...\n");
      CubeInterface::initialize_coms(n); //Retry the failed connections

      ros::spinOnce();
      loop_rate.sleep();
    }

    if(pos_client.call(srv)) 
    {
      printf("The robot's pos is (%f, %f)\n", srv.response.pos_x, srv.response.pos_y);

      // Create and populate a message to send
      using_markers::robotCommand msg;
	
      //Get control input, u, given desired x and y positions
      controller(10, 10, srv.response.pos_x,srv.response.pos_y, u);

      printf("x_vel = %f\ny_vel = %f\n", u[0], u[1]);
			
      // ultimately we will want to change how we set wheel speeds  
      msg.speed0 = msg.speed2 = u[0];
      msg.speed1 = msg.speed3 = u[1];

      chatter_pub.publish(msg);
    }else
      fprintf(stderr, "Error: The pos client call failed!\n");

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}

//TODO: Make a CubeInterface obj that inherits from CubeComSpecs and packages the publisher and service client
// nicely into it. Also, begin making the brain and spin functions
