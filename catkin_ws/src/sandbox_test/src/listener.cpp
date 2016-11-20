#include "ros/ros.h"
#include "std_msgs/String.h"
#include <visualization_msgs/Marker.h>

#include <cmath>

float ball_x = 0.0;
float ball_y = 0.0;

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  switch(msg->data.c_str()[0]) {
    case 'd': {
      ball_x += 0.1;
      ROS_INFO("I heard: [%s]", msg->data.c_str());
      break;
    }
    case 'a': {
      ball_x -= 0.1;
      ROS_INFO("I heard: [%s]", msg->data.c_str());
      break;
    }
    case 'w': {
      ball_y += 0.1;
      ROS_INFO("I heard: [%s]", msg->data.c_str());
      break;
    }
    case 's': {
      ball_y -= 0.1;
      ROS_INFO("I heard: [%s]", msg->data.c_str());
      break;
    }
  }
}

int main(int argc, char **argv)
{
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "listener");

  /**
   * NodeHandle is the main access point to communications with the ROS system.
   * The first NodeHandle constructed will fully initialize this node, and the last
   * NodeHandle destructed will close down the node.
   */
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);
  ros::Rate r(30);

  uint32_t sphere = visualization_msgs::Marker::SPHERE;


  /**
   * The subscribe() call is how you tell ROS that you want to receive messages
   * on a given topic.  This invokes a call to the ROS
   * master node, which keeps a registry of who is publishing and who
   * is subscribing.  Messages are passed to a callback function, here
   * called chatterCallback.  subscribe() returns a Subscriber object that you
   * must hold on to until you want to unsubscribe.  When all copies of the Subscriber
   * object go out of scope, this callback will automatically be unsubscribed from
   * this topic.
   *
   * The second parameter to the subscribe() function is the size of the message
   * queue.  If messages are arriving faster than they are being processed, this
   * is the number of messages that will be buffered up before beginning to throw
   * away the oldest ones.
   */

  while(ros::ok()) {
    visualization_msgs::Marker ball;
    ball.header.frame_id = "/my_frame";
    ball.header.stamp = ros::Time::now();
    ball.ns = "basic_shapes";
    ball.action = visualization_msgs::Marker::ADD;
    ball.pose.orientation.w = 1.0;

    ball.id = 0;
    ball.type = sphere;

    ball.pose.position.x = ball_x;
    ball.pose.position.y = ball_y;
    ball.pose.position.z = 0;
    ball.pose.orientation.x = 0.0;
    ball.pose.orientation.y = 0.0;
    ball.pose.orientation.z = 0.0;
    ball.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    ball.scale.x = 1.0;
    ball.scale.y = 1.0;
    ball.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    ball.color.r = 0.0f;
    ball.color.g = 1.0f;
    ball.color.b = 0.0f;
    ball.color.a = 1.0;

    ball.lifetime = ros::Duration();

    marker_pub.publish(ball);

    ros::spinOnce();
    r.sleep();

  }
  

  /**
   * ros::spin() will enter a loop, pumping callbacks.  With this version, all
   * callbacks will be called from within this thread (the main one).  ros::spin()
   * will exit when Ctrl-C is pressed, or the node is shutdown by the master.
   */
  //ros::spin();

  return 0;
}