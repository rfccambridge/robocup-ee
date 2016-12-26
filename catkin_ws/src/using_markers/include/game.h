#ifndef GAME_H
#define GAME_H

#include <map>
#include <stdexcept>

#include <ros/ros.h>
#include <using_markers/speedCommand.h>
#include <using_markers/robotPosSrv.h>
#include <visualization_msgs/Marker.h>

#include "custom_markers.h"
#include "shared_code.h"

class Game
{
protected:
  static ros::ServiceServer server_get_pos;
  static ros::Subscriber subscriber_set_pos;
  static ros::Publisher publisher_render;

  //A map of marker ID's and polymorphic casts of custom marker types -- ewww
  static std::map<int, CustomMarker*> map_markers;

public:
  Game(ros::NodeHandle n)
  {
    //TODO: we can create 6 robots and a ball or something
    initialize_coms(n);
  }

  void render_markers();

  //Creates a `Cube` and adds it to the `map_markers`
  void create_cube(int id, double _x, double _y, double _z)
  {
    //Cast to a polymorphic type
    CustomMarker* c = new Cube(id, _x, _y, _z);

    map_markers.insert(std::pair<int, CustomMarker*>(id, c));
  }

  //Creates a `Ball` and adds it to the `map_markers`
  void create_ball(int id, double _x, double _y, double _z)
  {
    //Cast to a polymorphic type
    CustomMarker* b = new Ball(id, _x, _y, _z);

    map_markers.insert(std::pair<int, CustomMarker*>(id, b));
  }

  //Sets the x position based on an incoming message
  static void subscriber_set_pos_handle(const using_markers::speedCommand command);

  static bool server_get_pos_handle(using_markers::robotPosSrv::Request& req,
                                    using_markers::robotPosSrv::Response& res);

  //Initializes the communication interfaces
  static void initialize_coms(ros::NodeHandle n)
  {
    //Establish a connection to the simulation renderer
    if(!publisher_render)
      publisher_render = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

    if(!server_get_pos)
      server_get_pos = n.advertiseService(ROBOT_POS_SERVER, server_get_pos_handle);

    if(!subscriber_set_pos)
      subscriber_set_pos = n.subscribe(ROBOT_COMMAND_TOPIC, 1, subscriber_set_pos_handle);
  }

  //Checks connection status
  static bool coms_alive() { return publisher_render && server_get_pos && subscriber_set_pos; }

  static CustomMarker* lookup_by_id(const int id)
  {
    std::map<int, CustomMarker*>::iterator it = map_markers.find(id);

    //Return accordingly based on whether `id` was found
    if(it == map_markers.end())
    {
      boost::format err_fmt("Marker id %1% not found in map look up");
      std::string e_str = boost::str(err_fmt % id);

      PRINT_ERROR_AND(throw std::out_of_range(e_str));
    } else
      return it->second;
  }
};

#endif //GAME_H
