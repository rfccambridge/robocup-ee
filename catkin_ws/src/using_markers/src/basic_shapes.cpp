
#include <ros/ros.h>

#include "cube_obj.h"

//int rate = 1; // If you change this value, you must also change it in 
									// basic_shapes_publisher.c and cube_obj.c
//float dt = 1/rate;

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "points_and_lines");

  ros::NodeHandle n;
  ros::Rate loop_rate(1000);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);

  //Advertise the `speed` service for the cube objects
  ros::ServiceServer service = n.advertiseService("service_get_pos", &Cube::service_get_pos);

  //Instantiate a cube for us to move
  Cube cube(0, 0, 0);
	
  //Register this cube's x coords to change according to the influx of messages from  "chatter"
  ros::Subscriber sub = n.subscribe("chatter", 1, &Cube::set_pos_x, &cube);

  uint32_t shape = visualization_msgs::Marker::CUBE;
  while(ros::ok())
  {
    //Make sure to publish the down-casted `cube`
    marker_pub.publish((visualization_msgs::Marker)cube);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
  }
}
