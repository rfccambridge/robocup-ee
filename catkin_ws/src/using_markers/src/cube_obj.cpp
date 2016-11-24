
#include <map>

#include <ros/ros.h>
#include "cube_obj.h"
#include "shared_code.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;

//Declare the static_cubes
std::map<int, Cube*> Cube::static_cubes;

Cube *Cube::lookup_cube(uint8_t id)
{
  std::map<int, Cube*>::iterator it = static_cubes.find(id);

  //Return accordingly based on whether cube `id` was found
  if(it == static_cubes.end())
    return NULL;
  else
    return it->second;
}

bool Cube::set_pos_x(const using_markers::robotCommand command)
{
  //Extract the cube pointer
  Cube *cube = lookup_cube(command.robotID);
  if(!cube)
    return false;

  printf("Received %f\n", command.speed0); 

  //TODO: incorporate speed2 and speed3 into this
  // This only drives in straight lines
  cube->pose.position.x += command.speed0 * dt;
  cube->pose.position.y += command.speed1 * dt;

  return true;
}

bool Cube::service_get_pos(using_markers::robotPosSrv::Request  &req, using_markers::robotPosSrv::Response &res)
{
  //Extract the cube pointer
  Cube *cube = lookup_cube(req.robotID);
  if(!cube)
    return false;

  printf("CUBE ID: %d\n", cube->id);

  //Assign the response `pos_x`
  res.pos_x = cube->pose.position.x;
  res.pos_y = cube->pose.position.y;

  return true;
}



