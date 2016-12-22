#include <map>
#include <ros/ros.h>

#include "custom_markers.h"
#include "game.h"
#include "shared_code.h"

ros::ServiceServer Game::server_get_pos;
ros::Subscriber Game::subscriber_set_pos;
ros::Publisher Game::publisher_render;

std::map<int, marker_t*> Game::map_markers;

void Game::render_markers()
{
  std::map<int, marker_t*>::iterator it = map_markers.begin();
  for(; it != map_markers.end(); ++it)
  {
    //Make sure to publish the down-casted `cube`
    marker_t* marker = it->second;

    //TODO: Do I have to spin after this since publisher_render only has a stack of size 1
    publisher_render.publish(*marker);
  }
}

//TODO: maybe make position update more general
void Game::subscriber_set_pos_handle(const using_markers::robotCommand command)
{
  printf("Received %f for robot ID %d\n", command.speed0, command.robotID);

  marker_t* cube = Game::lookup_by_id(command.robotID);
  if(!cube)
    PRINT_ERROR_AND(return ); //Return on error

  //TODO: incorporate speed2 and speed3 into this
  //This only drives in straight lines
  cube->pose.position.x += command.speed0 * DT;
  cube->pose.position.y += command.speed1 * DT;

  return;
}

bool Game::server_get_pos_handle(using_markers::robotPosSrv::Request& req,
                                 using_markers::robotPosSrv::Response& res)
{
  marker_t* cube = Game::lookup_by_id(req.robotID);
  if(!cube)
    PRINT_ERROR_AND(return false); //Return `false` on error

  //Assign the response `pos_x`
  res.pos_x = cube->pose.position.x;
  res.pos_y = cube->pose.position.y;

  return true;
}
