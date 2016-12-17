
#ifndef CUBE_INTERFACE_H
#define CUBE_INTERFACE_H

#include <ros/ros.h>

#include <using_markers/robotCommand.h>
#include <using_markers/robotPosSrv.h>

#include "shared_code.h"

class CubeInterface
{
protected:
  static ros::ServiceClient client_get_pos;
  static ros::Publisher publisher_set_vels;

  //!!!TODO
  //!!!TODO: Enclose the commands from the controller better
  //!!!TODO
  int cmd_x_pos, cmd_y_pos;
  float error_i_x, error_i_y;

  // Calls the cube server to retrieve the current position
  bool call_for_cur_pos(float ret_cur_pos[2]);

  // Calculates the xy velocities of the cube given its current position and a desired destination
  // using a
  // PID controller implementation
  bool pid_calc_vels(float ret_vels[2]);

public:
  // TODO: make this an enum type
  int id;

  CubeInterface(int _id) : id(_id) {}

  //!!!TODO
  //!!!TODO: Enclose the commands from the controller better
  //!!!TODO
  void goto_xy_pos(const int x, const int y);

  // Operate the PID and send the output messages
  bool spin();

  // Initializes the communication interfaces
  static void initialize_coms(ros::NodeHandle n)
  {
    if(!client_get_pos)
      client_get_pos = n.serviceClient<using_markers::robotPosSrv>(ROBOT_POS_SERVER, true);

    // TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd
    // to
    if(!publisher_set_vels)
      publisher_set_vels = n.advertise<using_markers::robotCommand>(ROBOT_COMMAND_TOPIC, 1);
  }

  // Checks connection status
  static bool coms_alive() { return client_get_pos && publisher_set_vels; }
};

#endif /* CUBE_INTERFACE_H */
