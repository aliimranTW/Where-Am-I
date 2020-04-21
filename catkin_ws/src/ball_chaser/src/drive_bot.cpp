#include "ros/ros.h"
#include <std_msgs/Float64.h>
#include "ball_chaser/DriveToTarget.h"
#include <geometry_msgs/Twist.h>

ros::Publisher motor_command_publisher;


int main(int argc, char** argv)
{
    ros::init(argc, argv, "drive_bot");
    ros::NodeHandle n;
    
    motor_command_publisher = n.adverstise<geometry_msgs::Twist>("/cmd_vel", 10);
    ros::ServiceServer Service = n.advertiseService("drive_bot/command_robot", handle_drive_request);
    
    

}
