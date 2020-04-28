#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("Sending requested joint velocities");
    
    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;
    
    //call the service
    if(!client.call(srv))
        ROS_ERROR("Failed to call service 'command_move'");
}

void process_image_callback(const sensor_msgs::Image img)
{
    int image_height = img.height;
    int image_width = img.step;
    int image_size = image_height * image_width;
    int left_col = 0;
    int right_col = 0;
    int front_col = 0;

    for(int i = 0; i < (image_size - 3); i += 3)
    {
        //check if it is a white pixel
        if(img.data[i] == 255 && img.data[i+1] == 255 && img.data[i+2] == 255)
        {
            //locate the position of the pixel
            if((i % image_width) < (image_width / 3))
                left_col += 1;
            else if((i % image_width) > ((image_width * 2) / 3))
                right_col += 1;
            else
                front_col += 1;
        }        
    }
    drive_robot(0.0, 0.0);
    ROS_INFO("left front right %d %d %d", left_col, front_col, right_col);

    if(left_col > 1 || right_col > 1 || front_col > 1)
    {
        // the location having containing the maximum amout of white pixels indicate the presence of the white ball
        if(left_col > front_col && left_col > right_col)
            drive_robot(0.0, 1);
        
        else if(right_col > front_col && right_col > left_col)
            drive_robot(0.0, -1);
        
        else if(front_col > left_col && front_col > right_col)
            drive_robot(1, 0.0);
        else
            drive_robot(1.0, 0.0);
    }
    else
    	drive_robot(0.0, 0.0); 
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
    ros::Subscriber sub1 = n.subscribe("camera/rgb/image_raw", 10, process_image_callback);
    
    ros::spin();
    
    return 0;
}

