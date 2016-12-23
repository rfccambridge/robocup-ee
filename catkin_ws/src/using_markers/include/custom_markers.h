
#ifndef CUSTOM_MARKER_H
#define CUSTOM_MARKER_H

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

//For the initial values of a marker
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/ColorRGBA.h>

//Marker types (cube, sphere, etc.) are secretly just 8bit integers
typedef uint8_t marker_type_t;

//The permissions flag bits for weather certain communication handles can operate over certain custom markers
typedef uint8_t com_permissions_t;

//Start off the effective permissions with 0b1 and shift from there
#define PERM_NONE      0
#define PERM_GET_POS   0b1
#define PERM_SET_POS   (PERM_GET_POS << 1)

class CustomMarker : public visualization_msgs::Marker
{
public:
  CustomMarker(int _id, marker_type_t marker_type,
               geometry_msgs::Point _position,
               geometry_msgs::Quaternion _orientation,
               geometry_msgs::Vector3 _scale,
               std_msgs::ColorRGBA _color)
  {
    //All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = _id; //Set the `Marker` id based on the input `_id`

    type = marker_type;

    lifetime = ros::Duration();

    //Set the input geometry traits
    pose.position = _position;
    pose.orientation = _orientation;
    scale = _scale;
    color = _color;
  }

  //TODO!!!!
  //TODO: What if we have Cubes of different derived classes!!!!
  //TODO!!!!
  marker_type_t getMarkerType() { return type; }

  //Require each derived class to specify the communication handle permissions
  virtual com_permissions_t getComPermissions() = 0;

};

class Cube : public CustomMarker
{
public:
  Cube(int robot_id, double _x, double _y, double _z);

  com_permissions_t getComPermissions()
  {
    return PERM_GET_POS | PERM_SET_POS;
  }
};

class Ball : public CustomMarker
{
public:
  Ball(int ball_id, double _x, double _y, double _z);

  //Allow only getting position of the ball
  com_permissions_t getComPermissions()
  {
    return PERM_GET_POS;
  }
};

#endif //CUSTOM_MARKER_H
