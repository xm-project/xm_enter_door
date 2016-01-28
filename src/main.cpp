#include <xm_enter_door/doorisopen.h>

int main(int argc, char **argv)
{
    ros::init (argc, argv, "doorisopen");
    ros::NodeHandle nh;
    ros::Rate r(10.0);
    while(ros::ok())
    {
        doorisopen Door(nh);
        ros::spin();
    }
    return 0;
}
