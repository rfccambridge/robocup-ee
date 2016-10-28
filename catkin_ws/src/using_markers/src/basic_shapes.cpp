
#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <using_markers/robotCommand.h>

#include "cube_obj.h"


int x;

void set_pos (const using_markers::robotCommand command)
{
  x += command.dir * command.speed;
	printf("Receiving value: %d\n %d", command.speed,x);
}

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  ros::Rate loop_rate(30);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
	
  //Register this cube's x coords to change according to the influx of messages from  "chatter"
  ros::Subscriber sub = n.subscribe("chatter", 1000, set_pos);
  //Instantiate a cube for us to move
	Cube cube(0, 0, 0);

  uint32_t shape = visualization_msgs::Marker::CUBE;
  while(ros::ok())
  {

		cube.pose.position.x = x;
    //Make sure to publish the down-casted `cube`
    marker_pub.publish((visualization_msgs::Marker)cube);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
