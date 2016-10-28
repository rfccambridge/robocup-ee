
#include "ros/ros.h"
#include "std_msgs/Int8.h"

int main(int argc, char **argv)
{
  //Initialize our ROS system
  ros::init(argc, argv, "int8_publisher");

  ros::NodeHandle n;

  //TODO: Make this publish float64 instead, as per what the pose.position variables are spec'd to
  ros::Publisher chatter_pub = n.advertise<std_msgs::Int8>("chatter", 1000);
  ros::Rate loop_rate(10);

  int count = 0, dir = 1;
  while(ros::ok())
  {
    //Create and populate a message to send
    std_msgs::Int8 msg;
    msg.data = count += dir;

    printf("Sending value: %d\n", msg.data);
    chatter_pub.publish(msg);

    //Process all of the callbacks and sleep a bit between loops
    ros::spinOnce();
    loop_rate.sleep();

    //Bounce count within -3 and 3
    if(count == -3)
      dir = 1;
    else if(count == 3)
      dir = -1;

  }

  return 0;
}
