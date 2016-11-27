
#include <map>

#include <ros/ros.h>
#include "cube_obj.h"
#include "shared_code.h"

ros::ServiceServer Cube::server_get_pos;
ros::Subscriber Cube::subscriber_set_pos;
ros::Publisher Cube::publisher_render;

void Cube::render_cubes()
{
  std::map<int, Cube*>::iterator it = map_instances.begin();
  for(; it != map_instances.end(); ++it)
  {
    //Make sure to publish the down-casted `cube`
    visualization_msgs::Marker *marker = it->second;

    //TODO: Do I have to spin after this since publisher_render only has a stack of size 1
    publisher_render.publish(*marker);
  }
}

void Cube::subscriber_set_pos_handle(const using_markers::robotCommand command)
{
  printf("Received %f for robot ID %d\n", command.speed0, command.robotID); 

  Cube *cube = lookup_by_id(command.robotID);
  if(!cube)
    PRINT_ERROR_AND(return); //Return on error

  //TODO: incorporate speed2 and speed3 into this
  // This only drives in straight lines
  cube->pose.position.x += command.speed0 * DT;
  cube->pose.position.y += command.speed1 * DT;

  return;
}

bool Cube::server_get_pos_handle(using_markers::robotPosSrv::Request  &req, 
                                 using_markers::robotPosSrv::Response &res)
{
  Cube *cube = lookup_by_id(req.robotID);
  if(!cube)
    PRINT_ERROR_AND(return false); //Return `false` on error

  //Assign the response `pos_x`
  res.pos_x = cube->pose.position.x;
  res.pos_y = cube->pose.position.y;

  return true;
}
