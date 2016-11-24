
#ifndef CUBE_OBJ
#define CUBE_OBJ

#include <map>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <using_markers/robotCommand.h>
#include <using_markers/robotPosSrv.h>

#include "cube_com_specs.h"

class Cube : public visualization_msgs::Marker, public CubeComSpecs<Cube>
{
protected:
  static std::map<int, Cube*> static_cubes;
  ros::ServiceServer server_get_pos;
  ros::Subscriber subscriber_set_pos;
  
public:
  Cube(ros::NodeHandle n, double _x, double _y, double _z)
  {
    //All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = running_id;
    type = visualization_msgs::Marker::CUBE;

    //Add `this` to the map of cubes
    static_cubes.insert(std::pair<int, Cube*>(id, this));

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

    //Initialize the servers and subscriptions
    server_get_pos = n.advertiseService(name_service_get_pos(), &Cube::server_get_pos_handle, this);
    subscriber_set_pos = n.subscribe(name_messenger_set_pos(), 1, &Cube::subscriber_set_pos_handle, this);    
  }

  static Cube *lookup_cube(uint8_t id);

  //Sets the x position based on an incoming message
  void subscriber_set_pos_handle(const using_markers::robotCommand command);
  
  //
  // Cube Services
  //
  bool server_get_pos_handle(using_markers::robotPosSrv::Request  &req,
                             using_markers::robotPosSrv::Response &res);

};

#endif // MACRO
