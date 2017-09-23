#include <cmath>
#include <map>
#include <stdexcept>

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

  visualization_msgs::Marker field_marker;
  field_marker.header.frame_id = "/my_frame"; //SPECIFIC (hardcoded)
  field_marker.header.stamp = ros::Time::now();
  field_marker.ns = "field_mesh";
  field_marker.id = 1;
  field_marker.type = visualization_msgs::Marker::MESH_RESOURCE;
  field_marker.action = visualization_msgs::Marker::ADD;

  field_marker.pose.position.x = -4.73;
  field_marker.pose.position.y = 3.0;
  field_marker.pose.position.z = 0;
  field_marker.pose.orientation.x = 0.707;
  field_marker.pose.orientation.y = 0;
  field_marker.pose.orientation.z = 0;
  field_marker.pose.orientation.w = 0.707;

  field_marker.scale.x = 0.001;
  field_marker.scale.y = 0.001;
  field_marker.scale.z = 0.001;

  field_marker.color.r = 0.0;
  field_marker.color.g = 1.0;
  field_marker.color.b = 1.0;
  field_marker.color.a = 1.0;

  field_marker.mesh_resource = "package://using_markers/include/field_lines.stl";
  publisher_render.publish(field_marker);

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

    float vel_x = 0.5 * (command.speed3 - command.speed1);
    float vel_y = 0.5 * (command.speed0 - command.speed2);

    // angular velocity
    float omega = 0.25 / d * (command.speed0 + command.speed1 + command.speed2 + command.speed3);
    float pose = get_pose(marker);

    //Transform velocities to lab frame of reference
    float vel_x_trans = vel_y * cos(pose + PI / 2.0) + vel_x * cos(pose);
    float vel_y_trans = vel_y * cos(pose) + vel_x * cos(pose - PI / 2.0);

    marker->pose.position.x += vel_x_trans * DT;
    marker->pose.position.y += vel_y_trans * DT;

    // Uncomment this and remake to see marker continuously rotate
    Game::rotate_marker(marker, omega * DT);
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
    res.pose = get_pose(marker);
  }
  catch(const std::exception& e)
  {
    PRINT_ERROR(e.what());
    return false; //Return `false` on error
  }

  return true;
}
