#include <ros/ros.h>
#include "std_msgs/String.h"
#include "turtlebot_highlevel_controller/TurtlebotHighlevelController.hpp"
#include "sensor_msgs/LaserScan.h"
#include <sstream>
#include <ros/param.h>
#include <iostream>
#include"std_msgs/Float32.h"

ros::Publisher my_pub;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
  //ROS_INFO("I heard: [%s]", msg->data.c_str());
std_msgs::Float32 smallest_range;
float h = sizeof(msg->ranges);
smallest_range.data = msg -> ranges[1];

for (int i=1; i<h-1;i++)
{
  if (msg->ranges[i]<smallest_range.data)
  smallest_range.data=msg->ranges[i];
ROS_INFO("Ausgabe [%f]", smallest_range.data);
}
}


  
  //my_pub.publish(smallest_range);




int main(int argc, char** argv)
{
  ros::init(argc, argv, "scan");
  ros::NodeHandle mynode;

  int queue_size;
  std::string topic;
  if(!mynode.getParam("/queue_size", queue_size))
  {
      ROS_ERROR_STREAM("queue_size wurde nicht gelesen.");
      return 0;
  }
  if(!mynode.getParam("/topic", topic))
  {
      ROS_ERROR_STREAM("topic wurde nicht gelesen.");
      return 0;
  }

  ros::Subscriber subscriber = mynode.subscribe("/scan", queue_size, chatterCallback);
  //turtlebot_highlevel_controller::TurtlebotHighlevelController TurtlebotHighlevelController(nodeHandle);
  my_pub = mynode.advertise<std_msgs::Float32>("/topic",1);
  ros::spin();
  return 0;
}