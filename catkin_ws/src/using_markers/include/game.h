#ifndef GAME_H
#define GAME_H

#include <map>
#include <stdexcept>
#include <cmath>

#include <ros/ros.h>
#include <using_markers/markerPosSrv.h>
#include <using_markers/speedCommand.h>
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

  ~Game()
  {
    //Clean all of the allocated markers
    std::map<int, CustomMarker*>::iterator it = map_markers.begin();
    for(; it != map_markers.end(); ++it)
      delete it->second;
  }

	// rotates marker `rotation` radians
	static void rotate_marker(CustomMarker* marker, float rotation)
	{
			// intialize unit quaternion with z-axis as axis of rotation
			float q_x = 0.0;
			float q_y = 0.0;
			float q_z = 1.0;
			float q_w = 0.0;

			// unit quaternion for rotation 
			float local_x = q_x*sinf(rotation/2.0);
			float local_y = q_y * sinf(rotation/2.0);
			float local_z = q_z * sinf(rotation/2.0);
			float local_w = cosf(rotation/2.0);

			// store marker's initial quaternion (before rotation)
			float total_x = marker->pose.orientation.x;
			float total_y = marker->pose.orientation.y;
			float total_z = marker->pose.orientation.z;
			float total_w = marker->pose.orientation.w;
		
			// execute rotation calculation, and set new values for the marker's quaternion
			marker->pose.orientation.x = local_w*total_x +  local_x*total_w  +  local_y*total_z - local_z*total_y;
			marker->pose.orientation.y = local_w*total_y -  local_x*total_z  +  local_y*total_w + local_z*total_x;
			marker->pose.orientation.z = local_w*total_z +  local_x*total_y  -  local_y*total_x + local_z*total_w;
			marker->pose.orientation.w = local_w*total_w -  local_x*total_x  -  local_y*total_y - local_z*total_z;
	}

	//Returns the current pose of the robot in radians
	static float get_pose (CustomMarker* marker)
	{
		if (marker->pose.orientation.z < 0.0)
			return (2*PI - 2*acos(marker->pose.orientation.w));
		else 
			return (2*acos(marker->pose.orientation.w));
	}

  void render_markers();

  //Creates an `OurRobot` and adds it to the `map_markers`
  void create_our_robot(int id, double _x, double _y, double _z)
  {
    //Cast to a polymorphic type
    CustomMarker* r = new OurRobot(id, _x, _y, _z);

    map_markers.insert(std::pair<int, CustomMarker*>(id, r));
  }

  //Creates a `Ball` and adds it to the `map_markers`
  void create_ball(int id, double _x, double _y, double _z)
  {
    //Cast to a polymorphic type
    CustomMarker* b = new Ball(id, _x, _y, _z);

    map_markers.insert(std::pair<int, CustomMarker*>(id, b));
  }

  //Creates the 6m x 9m field
  void create_field(int lines_id, int grass_id)
  {
    // creates the marker by repeatedly pushing points onto
    // a linelist to form rectangle
    CustomMarker* f = new FieldLines(lines_id);
    geometry_msgs::Point p;
    p.x = 0;
    p.y = 0;
    p.z = 0;
    f->points.push_back(p);
    p.x = FIELD_LENGTH;
    p.y = 0;
    p.z = 0;
    f->points.push_back(p);
    f->points.push_back(p);
    p.x = FIELD_LENGTH;
    p.y = FIELD_WIDTH;
    p.z = 0;
    f->points.push_back(p);
    f->points.push_back(p);
    p.x = 0;
    p.y = FIELD_WIDTH;
    p.z = 0;
    f->points.push_back(p);
    f->points.push_back(p);
    p.x = 0;
    p.y = 0;
    p.z = 0;
    f->points.push_back(p);
    p.x = FIELD_LENGTH / 2.;
    p.y = 0;
    p.z = 0;
    f->points.push_back(p);
    p.x = FIELD_LENGTH / 2.;
    p.y = FIELD_WIDTH;
    p.z = 0;
    f->points.push_back(p);
    // TODO: added boxes (and goals?) according to field specs
    map_markers.insert(std::pair<int, CustomMarker*>(lines_id, f));
    // also add the grass
    CustomMarker* g = new FieldGrass(grass_id);
    map_markers.insert(std::pair<int, CustomMarker*>(grass_id, g));
  }

  //Sets the x position based on an incoming message
  static void subscriber_set_pos_handle(const using_markers::speedCommand command);

  static bool server_get_pos_handle(using_markers::markerPosSrv::Request& req,
                                    using_markers::markerPosSrv::Response& res);

  //Initializes the communication interfaces
  static void initialize_coms(ros::NodeHandle n)
  {
    //Establish a connection to the simulation renderer
    if(!publisher_render)
      publisher_render = n.advertise<visualization_msgs::Marker>("visualization_marker", 100);

    if(!server_get_pos)
      server_get_pos = n.advertiseService(MARKER_POS_SERVER, server_get_pos_handle);

    if(!subscriber_set_pos)
      subscriber_set_pos = n.subscribe(MARKER_COMMAND_TOPIC, 1, subscriber_set_pos_handle);
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
