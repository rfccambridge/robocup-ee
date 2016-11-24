
#include <map>

#include <ros/ros.h>
#include "cube_obj.h"
#include "shared_code.h"

void Cube::subscriber_set_pos_handle(const using_markers::robotCommand command)
{
  printf("Received %f\n", command.speed0); 

  //TODO: incorporate speed2 and speed3 into this
  // This only drives in straight lines
  pose.position.x += command.speed0 * dt;
  pose.position.y += command.speed1 * dt;

  return;
}

bool Cube::server_get_pos_handle(using_markers::robotPosSrv::Request  &req, 
                                 using_markers::robotPosSrv::Response &res)
{
  //Assign the response `pos_x`
  res.pos_x = pose.position.x;
  res.pos_y = pose.position.y;

  return true;
}
