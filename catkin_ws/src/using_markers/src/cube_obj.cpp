
#include <map>

#include <ros/ros.h>
#include "cube_obj.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;

int rate = 100; // If you change this value, you must also change it in 
// basic_shapes_publisher.c and basic_shapes.c
float dt = 1.0/(float)rate;

//Declare the static_cubes
std::map<int, Cube*> Cube::static_cubes;

void Cube::set_pos_x(const using_markers::robotCommand command)
{
  printf("Received %f\n", command.speed0); 

  //TODO: incorporate speed2 and speed3 into this
  // This only drives in straight lines
  pose.position.x += command.speed0 * dt;
  pose.position.y += command.speed1 * dt;
	
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



