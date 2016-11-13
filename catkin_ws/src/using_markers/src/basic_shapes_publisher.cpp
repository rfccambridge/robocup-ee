
#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include <using_markers/robotCommand.h> // include custom message 

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "int8_publisher");

  ros::NodeHandle n;

  //TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd to
  ros::Publisher chatter_pub = n.advertise<using_markers::robotCommand>("chatter", 1000);
  ros::Rate loop_rate(10);

  int count = 0, dir = 1;
  while(ros::ok())
  {
    //Create and populate a message to send
    using_markers::robotCommand msg;
    msg.speed0 = dir*1;

    printf("Sending value: %d\n", count);
    chatter_pub.publish(msg);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();
	
    //Reset count every 20 iterations
    if(count >= 20)
    {
      count = 0;
      dir *= -1;
    }else 
      count++;

  }

  return 0;
}
