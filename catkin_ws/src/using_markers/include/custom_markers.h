
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
  CustomMarker(int _id, marker_type_t marker_type)
  {
    //All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";
    id = _id; //Set the `Marker` id based on the input `_id`

    type = marker_type;

    lifetime = ros::Duration();
  }

  marker_type_t getMarkerType()
  {
    return type;
  }

};

class Cube : public CustomMarker
{
public:

Cube(int robot_id, double _x, double _y, double _z) : CustomMarker(robot_id, visualization_msgs::Marker::CUBE)
  {
    //Set the initial pose position from the input arguments
    {
      geometry_msgs::Point p;
      p.x = _x;
      p.y = _y;
      p.z = _z;

      pose.position = p;
    }

    //Set the initial pose orientation to a default
    {
      geometry_msgs::Quaternion o;
      o.x = 0.0;
      o.y = 0.0;
      o.z = 0.0;
      o.w = 1.0;

      pose.orientation = o;
    }

    //Set the initial scale
    {
      //1x1x1 here means 1m on a side
      geometry_msgs::Vector3 s;      
      s.x = 1.0;
      s.y = 1.0;
      s.z = 1.0;

      scale = s;
    }

    //Set the initial color. Be sure to set alpha to something non-zero!
    {
      std_msgs::ColorRGBA c;
      c.r = 0.0;
      c.g = 1.0;
      c.b = 0.0;
      c.a = 1.0;

      color = c;
    }    
  }
};

class Ball : public CustomMarker
{
public:

Ball(int ball_id, double _x, double _y, double _z) : CustomMarker(ball_id, visualization_msgs::Marker::SPHERE)
  {
    //Set the initial pose position from the input arguments
    {
      geometry_msgs::Point p;
      p.x = _x;
      p.y = _y;
      p.z = _z;

      pose.position = p;
    }

    //Set the initial pose orientation to a default
    {
      geometry_msgs::Quaternion o;
      o.x = 0.0;
      o.y = 0.0;
      o.z = 0.0;
      o.w = 1.0;

      pose.orientation = o;
    }

    //Set the initial scale
    {
      //1x1x1 here means 1m on a side
      geometry_msgs::Vector3 s;      
      s.x = 0.75;
      s.y = 0.75;
      s.z = 0.75;

      scale = s;
    }

    //Set the initial color. Be sure to set alpha to something non-zero!
    {
      std_msgs::ColorRGBA c;
      c.r = 0.0;
      c.g = 0.0;
      c.b = 1.0;
      c.a = 1.0;

      color = c;
    }    
  }
};

#endif //CUSTOM_MARKER_H
