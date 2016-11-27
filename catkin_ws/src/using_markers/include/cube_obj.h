
#ifndef CUBE_OBJ
#define CUBE_OBJ

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <using_markers/robotCommand.h>
#include <using_markers/robotPosSrv.h>

#include "cube_com_specs.h"

class Cube : public visualization_msgs::Marker, public CubeComSpecs<Cube>
{
protected:
  static ros::ServiceServer server_get_pos;
  static ros::Subscriber subscriber_set_pos;
  static ros::Publisher publisher_render;
  
public:
  Cube(double _x, double _y, double _z)
  {
    //All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = com_id; //Set the `Marker` id based on the associated `CubeComSpecs` id
    type = visualization_msgs::Marker::CUBE;

    lifetime = ros::Duration();

    //Set the pose position from the input arguments
    pose.position.x = _x;
    pose.position.y = _y;
    pose.position.z = _z;

    //Set all of the other values to their default
    pose.orientation.x = 0.0;
    pose.orientation.y = 0.0;
    pose.orientation.z = 0.0;
    pose.orientation.w = 1.0;

    //1x1x1 here means 1m on a side
    scale.x = 1.0;
    scale.y = 1.0;
    scale.z = 1.0;

    //Be sure to set alpha to something non-zero!
    color.r = 0.0f;
    color.g = 1.0f;
    color.b = 0.0f;
    color.a = 1.0;
  }

  static void render_cubes();

  //Sets the x position based on an incoming message
  static void subscriber_set_pos_handle(const using_markers::robotCommand command);
  
  //
  // Cube Services
  //
  static bool server_get_pos_handle(using_markers::robotPosSrv::Request  &req,
                                    using_markers::robotPosSrv::Response &res);

  //Initializes the communication interfaces
  static void initialize_coms(ros::NodeHandle n)
  {
    //Establish a connection to the simulation renderer
    if(!publisher_render)
      publisher_render = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    if(!server_get_pos)
      server_get_pos = n.advertiseService(name_service_get_pos(), server_get_pos_handle);

    if(!subscriber_set_pos)
      subscriber_set_pos = n.subscribe(name_messenger_set_pos(), 1, subscriber_set_pos_handle);        
  }

  //Checks connection status
  static bool coms_alive()
  {
    return publisher_render && server_get_pos && subscriber_set_pos;
  }
};

#endif // MACRO
