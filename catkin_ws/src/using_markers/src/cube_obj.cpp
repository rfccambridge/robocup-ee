
#include <map>

#include <ros/ros.h>
#include "cube_obj.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;

//Declare the static_cubes
std::map<int, Cube*> Cube::static_cubes;

void Cube::set_pos_x(const using_markers::robotCommand command)
{
  printf("Received %d\n", command.speed0);
  pose.position.x += command.speed0;
}

bool Cube::service_get_pos(using_markers::robotPosSrv::Request  &req,
                           using_markers::robotPosSrv::Response &res)
{
  std::map<int, Cube*>::iterator it = static_cubes.find(req.robotID);

  //The robot `robotID` was unable to be found
  if(it == static_cubes.end())
    return false;

  //Extract the cube pointer
  Cube *cube = it->second;

  printf("CUBE ID: %d\n", cube->id);

  //Assign the response `pos_x`
  res.pos_x = cube->pose.position.x;
  res.pos_y = cube->pose.position.y;

  return true;
}



