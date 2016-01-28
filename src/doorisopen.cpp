#include <xm_enter_door/doorisopen.h>


doorisopen::doorisopen(ros::NodeHandle nh):
    nh_(nh)
{
    ROS_INFO("start!");
    flag_ = false;
    laser_frequency_ = 40;
    scan_x_ = 0.0;
    scan_y_ = 0.0;
    scan_subscriber_ = nh_.subscribe("scan", 10, &doorisopen::scanCallback, this);
    door_service_ = nh_.advertiseService("door",&doorisopen::serviceCallback,this);
	door_pub_ = nh.advertise<xm_enter_door::door_msg>("doormsg",1000);
}

doorisopen::~doorisopen()
{
    ROS_INFO("destroying scan!!");
}

bool doorisopen::serviceCallback(xm_enter_door::door::Request &req, xm_enter_door::door::Response &rep)
{
    rep.door_is_open = flag_;
    ROS_ERROR("the door is open:%d",rep.door_is_open);
    return true;
}

void doorisopen::scanCallback(const sensor_msgs::LaserScan::ConstPtr &scan_msg)
{
    xm_enter_door::door_msgPtr pdoor = boost::make_shared<xm_enter_door::door_msg>();
	pdoor ->door_open_msg = false;
    scan_x_ = 0.0;
    scan_y_ = 0.0;
    // if count >=5,think the door is open
    int count = 0;
    for (unsigned int i = 0; i < scan_msg->ranges.size(); ++i)
    {
        float range = scan_msg->ranges[i];
        float angle = scan_msg->angle_min + i*scan_msg->angle_increment;
        scan_x_ = range * cos(angle);
        scan_y_ = range * sin(angle);
        if ( (scan_y_ < 0.22 || scan_y_ > - 0.22)&& scan_x_ >1.5 && scan_y_ < 4.0 && scan_y_ >-4.0)
        {
            count++;
//            ROS_INFO("the count is: %d", count);
        }
    }
	ROS_INFO("%d",count);
    if (count > 40)
    {
        flag_ = true;
		pdoor ->door_open_msg = true;
        ROS_INFO("the door is open:%d", pdoor->door_open_msg);
    }
//    door_service_ = nh.advertiseService("door",&doorisopen::serviceCallback,this);
	door_pub_.publish(pdoor);
}
