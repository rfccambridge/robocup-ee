
#include "ros/ros.h"

#include "shared_code.h"

//************************************************************************
// PID controller implementation
// 
// x_end: 	desired x-position
// y_end: 	desired y-position
// x:				current x-position
// y: 			current y-position
//
// u: 			controller output
// 
void controller(float x_end, float y_end, float x, float y, float *u) 
{
  //Make this function reusable, ie: w/o the static
  static float error_i_x = 0, error_i_y = 0;
  const float k_p = 0.5, k_i = 0.1, k_d = 0.1;

  // position and error terms			
  float pos_x, error_x, error_d_x = 0.0;	
  float pos_y, error_y, error_d_y = 0.0;

  // commanded velocity
  float v_x = 0.0; 	
  float v_y = 0.0;

  error_x = x_end - x;
  error_i_x += error_x * dt;
  error_d_x = error_x / dt;

  error_y = y_end - y;
  error_i_y += error_y * dt;
  error_d_y = error_y / dt;

  // controller output (velocity)
  v_x = k_p * error_x + k_i * error_i_x + k_d * error_d_x;
  v_y = k_p * error_y + k_i * error_i_y + k_d * error_d_y;

  // Ensure that velocity is within the physical limits of the robot
  if(v_x > 10.0)
    v_x = 10.0;
  if(v_x < -10.0)
    v_x = -10.0;

  if(v_y > 10.0)
    v_y = 10.0;
  if(v_y < -10.0)
    v_y = -10.0;

  // store controller outputs in contoller
  u[0] = v_x;
  u[1] = v_y;

  return;
}

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "command_publisher");

  ros::NodeHandle n;
  CubeInterface::initialize_coms(n); //Initialize the communication interface for the cubes

  ros::Rate loop_rate(rate);

  float u[2];

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
