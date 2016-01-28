#include <ros/ros.h>
#include <xm_enter_door/door.h>
#include <cstdlib>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "door_client");

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<xm_enter_door::door>("door");
  xm_enter_door::door srv;
  if (client.call(srv))
  {
    ROS_INFO("response: %d", srv.response.door_is_open);
  }
  else
  {
    ROS_ERROR("Failed to call service ");
    return 1;
  }

  return 0;
}
