
#include <ros/ros.h>
#include <stdio.h>

#include "cube_interface.h"

ros::ServiceClient CubeInterface::client_get_pos;
ros::Publisher CubeInterface::publisher_set_vels;

// Calls the cube server to retrieve the current position
//
// Outputs in `ret_cur_pos` as [cur_x, cur_y] or returns false on error
bool CubeInterface::call_for_cur_pos(float ret_cur_pos[2])
{
  // Retrieve the current x and y positions of the robot
  float cur_x, cur_y;

  // Request the cube's position with ID of `id`
  using_markers::robotPosSrv srv;
  srv.request.robotID = id;

  // Send this request via the `client_get_pos`
  if(client_get_pos.call(srv))
  {
    printf("The robot's pos is (%f, %f)\n", srv.response.pos_x, srv.response.pos_y);

    ret_cur_pos[0] = srv.response.pos_x;
    ret_cur_pos[1] = srv.response.pos_y;
  } else
  {
    fprintf(stderr, "Error: The pos client call failed!\n");
    return false;
  }

  return true;
}

// Calculates the xy velocities of the cube given its current position and a desired destination
// using a
// PID controller implementation
//
// Outputs the velocities in `ret_vels` as [vel_x, vel_y] or returns false on error
bool CubeInterface::pid_calc_vels(float ret_vels[2])
{
  const float k_p = 0.5, k_i = 0.1, k_d = 0.1;

  // Error terms
  float error_x, error_d_x = 0.0;
  float error_y, error_d_y = 0.0;

  // Commanded velocities
  float vel_x = 0.0, vel_y = 0.0;

  // Retrieve the current x and y positions of the cube
  float cur_x, cur_y;

  {
    float ret[2];

    // Error the PID if the call for the current position fails
    if(!call_for_cur_pos(ret))
      return false;

    // Assign the returned values respectively
    cur_x = ret[0];
    cur_y = ret[1];
  }

  error_x = cmd_x_pos - cur_x;
  error_i_x += error_x * DT;
  error_d_x = error_x / DT;

  error_y = cmd_y_pos - cur_y;
  error_i_y += error_y * DT;
  error_d_y = error_y / DT;

  // Controller output (velocity)
  vel_x = k_p * error_x + k_i * error_i_x + k_d * error_d_x;
  vel_y = k_p * error_y + k_i * error_i_y + k_d * error_d_y;

  // Ensure that velocity is within the physical limits of the robot
  if(vel_x > 10.0)
    vel_x = 10.0;
  if(vel_x < -10.0)
    vel_x = -10.0;

  if(vel_y > 10.0)
    vel_y = 10.0;
  if(vel_y < -10.0)
    vel_y = -10.0;

  // Store controller outputs in contoller
  ret_vels[0] = vel_x;
  ret_vels[1] = vel_y;

  return true;
}

void CubeInterface::goto_xy_pos(const int x, const int y)
{
  cmd_x_pos = x;
  cmd_y_pos = y;

  // Reset the error counters for the PID controller
  error_i_x = error_i_y = 0;
}

// Operate the PID and send the output messages
// Returns false on error
bool CubeInterface::spin()
{
  // Retrieve the calculated velocities
  float vel_x, vel_y;

  {
    float ret[2];

    // Error the spin if the call for the current position fails
    if(!pid_calc_vels(ret))
      return false;

    // Assign the returned values respectively
    vel_x = ret[0];
    vel_y = ret[1];
  }

  // Create and populate a message to send
  using_markers::robotCommand msg;

  // Set the `robotID` by `id`
  msg.robotID = id;

  // TODO: ultimately we will want to change how we set wheel speeds
  msg.speed0 = msg.speed2 = vel_x;
  msg.speed1 = msg.speed3 = vel_y;

  // Actually send the message
  publisher_set_vels.publish(msg);

  return true;
}
