#include <map>
#include <stdexcept>
#include <cmath>

#include <ros/ros.h>

#include "custom_markers.h"
#include "game.h"
#include "shared_code.h"

ros::ServiceServer Game::server_get_pos;
ros::Subscriber Game::subscriber_set_pos;
ros::Publisher Game::publisher_render;

std::map<int, CustomMarker*> Game::map_markers;

void Game::render_markers()
{
			
  std::map<int, CustomMarker*>::iterator it = map_markers.begin();
  for(; it != map_markers.end(); ++it)
  {
    //Make sure to publish the down-casted `CustomMarker`
    CustomMarker* marker = it->second;

    //TODO: Do I have to spin after this since publisher_render only has a stack of size 1
    publisher_render.publish(*(visualization_msgs::Marker*)marker);
  }
}

//TODO: maybe make position update more general
void Game::subscriber_set_pos_handle(const using_markers::speedCommand command)
{
  printf("Received %f for marker ID %d\n", command.speed0, command.markerID);

  try
  {
    //Throws exception upon look up failure
    CustomMarker* marker = Game::lookup_by_id(command.markerID);

    //Sanity check: allow only markers with the appropriate permissions to continue
    if(!(marker->getComPermissions() & PERM_SET_POS))
      throw std::runtime_error("Marker not lowed to operate in set position function.");



		//!!!TODO: 	Convert command.speed0-3 to v_x (velocity in the x direction,
		//!!! 			v_y (velocity in the y direction), and w (angular velocity)
		//!!!	
		
		float vel_x = 0.5*(command.speed3 - command.speed1);
		float vel_y = 0.5*(command.speed0 - command.speed2);

		// angular velocity
		float omega = 0.25/d*(command.speed0 + command.speed1 + command.speed2 + command.speed3);

    marker->pose.position.x += vel_x * DT;
    marker->pose.position.y += vel_y * DT;
		
		
		// Uncomment this and remake to see marker continuously rotate
		Game::rotate_marker(marker,omega*DT);
		
  }
  catch(const std::exception& e)
  {
    PRINT_ERROR(e.what());
    return; //Return on error
  }
}

bool Game::server_get_pos_handle(using_markers::markerPosSrv::Request& req,
                                 using_markers::markerPosSrv::Response& res)
{
  try
  {
    //Throws exception upon look up failure
    CustomMarker* marker = Game::lookup_by_id(req.markerID);

    //Sanity check: allow only markers with the appropriate permissions to continue
    if(!(marker->getComPermissions() & PERM_GET_POS))
      throw std::runtime_error("Marker not allowed to operate in get position function.");

    //Assign the response accordingly
    res.pos_x = marker->pose.position.x;
    res.pos_y = marker->pose.position.y;

		// determine pose from quaternion - pose is represented in radians
		if (marker->pose.orientation.z < 0.0)
			res.pose = 2*PI - 2*acos(marker->pose.orientation.w);
		else 
			res.pose = 2*acos(marker->pose.orientation.w);
		
  }
  catch(const std::exception& e)
  {
    PRINT_ERROR(e.what());
    return false; //Return `false` on error
  }

  return true;
}
