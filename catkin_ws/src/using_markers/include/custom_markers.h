
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

typedef visualization_msgs::Marker marker_t;

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

  marker_type_t getMarkerType() { return type; }
};

class Cube : public CustomMarker
{
public:
  Cube(int robot_id, double _x, double _y, double _z);
};

class Ball : public CustomMarker
{
public:
  Ball(int ball_id, double _x, double _y, double _z);
};

#endif //CUSTOM_MARKER_H
