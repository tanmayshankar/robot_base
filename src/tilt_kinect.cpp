//Publisher node that takes in messages from the joystick and then publishes them to a topic called "motormsg" which has messages of the type 
//quaternion 
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Float64.h> 
// std_msgs::Float64 current_angle; 
double current_angle;
class tilt_kinect_class
{
    public:
        // TeleopTurtle();
        tilt_kinect_class();

    private:       
        void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
        void angle_callback(const std_msgs::Float64::ConstPtr& ang);
        ros::NodeHandle nh_;        
        ros::Publisher kinect_pub;
        ros::Subscriber joy_sub_;
        ros::Subscriber kinect_angle_sub;
};

tilt_kinect_class::tilt_kinect_class()
{
    kinect_pub = nh_.advertise<std_msgs::Float64>("/tilt_angle",1);
    kinect_angle_sub = nh_.subscribe<std_msgs::Float64>("cur_tilt_angle",10,&tilt_kinect_class::angle_callback,this);
    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &tilt_kinect_class::joyCallback, this);
}

void tilt_kinect_class::angle_callback(const std_msgs::Float64::ConstPtr& ang)
{// {   current_angle=ang->data;
}

void tilt_kinect_class::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{    
    // std_msgs::Float64 kinect_angle=current_angle; 

    if (joy->buttons[5]==1)
        if (current_angle<30)
            // kinect_angle=kinect_angle+1;
            current_angle++;
    if (joy->buttons[7]==1)
        if (current_angle>-30)
            // kinect_angle==kinect_angle-1;
            current_angle--;

    std::cout<<"Value of current angle is: "<<current_angle<<std::endl;
    
    std_msgs::Float64 kinect_angle; 
    kinect_angle.data=current_angle;
    kinect_pub.publish(kinect_angle);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tilt_kinect");
    // TeleopTurtle teleop_turtle;

    tilt_kinect_class tilt;
    ros::spin();
}
