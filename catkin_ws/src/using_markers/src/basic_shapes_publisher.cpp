
#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <using_markers/robotCommand.h> // include custom message 
#include <using_markers/robotPosSrv.h>

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "int8_publisher");

  ros::NodeHandle n;

  //TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd to
  ros::Publisher chatter_pub = n.advertise<using_markers::robotCommand>("chatter", 1000);
  ros::ServiceClient pos_client = n.serviceClient<using_markers::robotPosSrv>("service_get_pos", true);
  ros::Rate loop_rate(10);

  int count = 0, dir = 1;
  while(ros::ok())
  {
    //Request the cube's position with ID of 0
    using_markers::robotPosSrv srv;
    srv.request.robotID = 0;

    //Loop until `pos_client` connects
    while(ros::ok() && !pos_client)
    {
      printf("Unable to connect the pos client, trying to reconnect again...\n");
      pos_client = n.serviceClient<using_markers::robotPosSrv>("service_get_pos", true);

      ros::spinOnce();
      loop_rate.sleep();
    }

    if(pos_client.call(srv))
      printf("The robot's pos is (%d, %d)\n", srv.response.pos_x, srv.response.pos_y);
    else
      fprintf(stderr, "Error: The pos client call failed!\n");

    //Create and populate a message to send
    using_markers::robotCommand msg;
    msg.speed0 = dir*1;

    printf("Sending value: %d\n", count);
    chatter_pub.publish(msg);
	
    //Reset count every 20 iterations
    if(count >= 20)
    {
      count = 0;
      dir *= -1;
    }else 
      count++;

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();

  }

  return 0;
}
