#include "generator.hpp"


int main(int argc, char**argv) 
{
    ros::init(argc, argv, "dino_generator");
    DinoGenerator dg;
    ROS_INFO_STREAM("Dino_generator is ready!");
    while(ros::ok())
        ros::spin();
    return 0;
}


