
#include <ros/ros.h>

#include "cube_obj.h"

//Initialize the static running_id to 0.
// This has to be done outside of the header file since
// we don't want this bit of code copied everywhere the
// header is used
int Cube::running_id = 0;

void Cube::set_pos_x(const using_markers::robotCommand command)
{
  printf("Received %d %d\n", command.dir, command.speed);
  pose.position.x += command.dir * command.speed;
}



