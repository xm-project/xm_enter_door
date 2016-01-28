#ifndef DOOR_IS_OPEN_H
#define DOOR_IS_OPEN_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <limits>
#include <cmath>
#include <xm_enter_door/door.h>
#include <xm_enter_door/door_msg.h>

class doorisopen
{
private:
    ros::NodeHandle nh_;
    ros::ServiceServer door_service_;
    ros::Subscriber scan_subscriber_;
    ros::Publisher door_pub_;
    // the door is open?
    bool flag_;
    double laser_frequency_;
    double scan_x_;
    double scan_y_;
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan_msg);
    bool serviceCallback(xm_enter_door::door::Request &req,
                         xm_enter_door::door::Response &rep);
public:
    doorisopen(ros::NodeHandle nh);
    ~doorisopen();
};

#endif // DOOR_IS_OPEN_H
