
#ifndef CUSTOM_MARKER_H
#define CUSTOM_MARKER_H

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

//For the initial values of a marker
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Quaternion.h>
#include <geometry_msgs/Vector3.h>
#include <std_msgs/ColorRGBA.h>

//Marker types (cube, sphere, etc.) are secretly just 8bit integers as spec'd by ros
typedef uint8_t marker_type_t;

typedef enum {
  M_OUR_ROBOT,
  M_BALL,
  M_FIELD_LINES,
  M_FIELD_GRASS,
  M_FIELD_CIRCLE
} marker_identity_t;

//The permissions flag bits for weather certain communication handles can operate over certain custom markers
typedef uint8_t com_permissions_t;

//Start off the effective permissions with 0b1 and shift from there
#define PERM_NONE 0
#define PERM_GET_POS 0b1
#define PERM_SET_POS (PERM_GET_POS << 1)

class NonactiveMarker : public visualization_msgs::Marker
{
public:
  NonactiveMarker(marker_type_t marker_type,
               geometry_msgs::Point _position,
               geometry_msgs::Quaternion _orientation,
               geometry_msgs::Vector3 _scale,
               std_msgs::ColorRGBA _color)
  {
    //All of these fields are inherited from the `Marker` type
    header.frame_id = "/my_frame";
    header.stamp = ros::Time::now();
    ns = "basic_shapes";

    type = marker_type;

    lifetime = ros::Duration();

    //Set the input geometry traits
    pose.position = _position;
    pose.orientation = _orientation;
    scale = _scale;
    color = _color;
  }
};

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

  //Returns the identity of the derived class
  virtual marker_identity_t getMarkerIdentity() = 0;

  //Require each derived class to specify the communication handle permissions
  virtual com_permissions_t getComPermissions() = 0;
};

// TODO: make the dimensions of robot and ball to scale
class OurRobot : public CustomMarker
{
public:
  OurRobot(int robot_id, double _x, double _y, double _z);

  marker_identity_t getMarkerIdentity() { return M_OUR_ROBOT; }

  //Allow both getting and setting the position of our robots
  com_permissions_t getComPermissions() { return PERM_GET_POS | PERM_SET_POS; }
};

class Ball : public CustomMarker
{
public:
  Ball(int ball_id, double _x, double _y, double _z);

  marker_identity_t getMarkerIdentity() { return M_BALL; }

  //Allow only getting position of the ball
  com_permissions_t getComPermissions() { return PERM_GET_POS; }
};

class Field : public NonactiveMarker
{
public:
  Field(char* file);
};

class FieldLines : public CustomMarker
{
public:
  FieldLines(int field_lines_id);

  marker_identity_t getMarkerIdentity() { return M_FIELD_LINES; }
  com_permissions_t getComPermissions() { return PERM_GET_POS; }
};

class FieldGrass : public CustomMarker
{
public:
  FieldGrass(int field_grass_id);

  marker_identity_t getMarkerIdentity() { return M_FIELD_GRASS; }
  com_permissions_t getComPermissions() { return PERM_GET_POS; }
};
class FieldCircle : public CustomMarker
{
public:
  FieldCircle(int field_circle_id, double diameter, double height,
              int r, int g, int b, int a);

  marker_identity_t getMarkerIdentity() { return M_FIELD_CIRCLE; }
  com_permissions_t getComPermissions() { return PERM_GET_POS; }
};

#endif //CUSTOM_MARKER_H
