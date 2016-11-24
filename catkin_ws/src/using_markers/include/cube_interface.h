
#ifndef CUBE_INTERFACE_H
#define CUBE_INTERFACE_H

#include <ros/ros.h>

#include <using_markers/robotCommand.h>
#include <using_markers/robotPosSrv.h>

#include "cube_com_specs.h"

class CubeInterface, public CubeComSpecs
{
public:
  static ros::ServiceClient client_get_pos;
  static ros::Publisher publisher_set_pos;

  CubeInterface()
  {
    
  }

  //Initializes the communication interfaces
  static void initialize_coms(ros::NodeHandle n)
  {
    //These only get initialized once as they are static variable
    if(!client_get_pos)
      client_get_pos = n.serviceClient<using_markers::robotPosSrv>(name_service_get_pos(), true);

    //TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd to
    if(!publisher_set_pos)
      publisher_set_pos = n.advertise<using_markers::robotCommand>(name_messenger_set_pos(), 1);
  }

  //Checks connection status
  static bool coms_alive()
  {
    return client_get_pos;
  }
};

#endif /* CUBE_INTERFACE_H */
