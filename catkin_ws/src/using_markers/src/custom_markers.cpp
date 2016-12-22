
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

//For the initial values of a marker
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/ColorRGBA.h>

#include "custom_markers.h"

//
//Small helper functions meant only for this file
//

static inline geometry_msgs::Point create_point(double _x, double _y, double _z)
{
  geometry_msgs::Point p;
  p.x = _x;
  p.y = _y;
  p.z = _z;

  return p;
}

static inline geometry_msgs::Quaternion create_quaternion(double _x, double _y, double _z, double _w)
{
  geometry_msgs::Quaternion o;
  o.x = _x;
  o.y = _y;
  o.z = _z;
  o.w = _w;

  return o;
}

static inline geometry_msgs::Vector3 create_vector3(double _x, double _y, double _z)
{
  geometry_msgs::Vector3 v;
  v.x = _x;
  v.y = _y;
  v.z = _z;

  return v;
}

static inline std_msgs::ColorRGBA create_colorRGBA(double _r, double _g, double _b, double _a)
{
  std_msgs::ColorRGBA c;
  c.r = _r;
  c.g = _g;
  c.b = _b;
  c.a = _a;

  return c;
}

Cube::Cube(int robot_id, double _x, double _y, double _z)
    : CustomMarker(robot_id, visualization_msgs::Marker::CUBE,
                   create_point(_x, _y, _z),      //Set the initial pose position from the input arguments
                   create_quaternion(0, 0, 0, 1), //Set the initial pose orientation to a default
                   create_vector3(1, 1, 1),       //Set the initial scale, 1x1x1 means 1m per side
                   create_colorRGBA(0, 1, 0, 1))  //Set the default color to green
{
}

Ball::Ball(int ball_id, double _x, double _y, double _z)
    : CustomMarker(ball_id, visualization_msgs::Marker::SPHERE,
                   create_point(_x, _y, _z),         //Set the initial pose position from the input arguments
                   create_quaternion(0, 0, 0, 1),    //Set the initial pose orientation to a default
                   create_vector3(0.75, 0.75, 0.75), //Set the initial scale
                   create_colorRGBA(0, 0, 1, 1))     //Set the default color to blue
{
}
