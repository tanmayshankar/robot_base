//Publisher node that takes in messages from the joystick and then publishes them to a topic called "motormsg" which has messages of the type 
//quaternion 
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Quaternion.h>

class TeleopTurtle
{
    public:
        TeleopTurtle();
    private:
        void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
        ros::NodeHandle nh_;
        int linear_, angular_;
        double l_scale_, a_scale_;
        ros::Publisher vel_pub_, vel_pub_2, vel_pub_3;
        ros::Subscriber joy_sub_;
        ros::Publisher bot_pub_;
};

TeleopTurtle::TeleopTurtle():
linear_(1),
angular_(2)
{
    nh_.param("axis_linear", linear_, linear_);
    nh_.param("axis_angular", angular_, angular_);
    nh_.param("scale_angular", a_scale_, a_scale_);
    nh_.param("scale_linear", l_scale_, l_scale_);

    vel_pub_ = nh_.advertise<geometry_msgs::Twist>("turtle1/cmd_vel", 1);
    // vel_pub_2 = nh_.advertise<geometry_msgs::Twist>("fair/cmd_vel",1);

    joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopTurtle::joyCallback, this);

    bot_pub_ = nh_.advertise<geometry_msgs::Quaternion>("motormsg", 1);
    vel_pub_2 = nh_.advertise<geometry_msgs::Quaternion>("fair/cmd_vel",1);
    vel_pub_3 = nh_.advertise<geometry_msgs::Quaternion>("fair/joy_cmd_vel",1);
}

void TeleopTurtle::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
    geometry_msgs::Twist twist;
    twist.linear.x = l_scale_*joy->axes[linear_];
    twist.angular.z = a_scale_*joy->axes[angular_];
    vel_pub_.publish(twist);

    // vel_pub_2.publish(twist);
    geometry_msgs::Quaternion quart;
    //axis up means linear>0 -----x
    //axis down means linear<0 -----y
    //axis left means angular>0 -----z
    //axis right means angular<0 -----w
    if (joy->axes[linear_]>0)
        {
            quart.x=130 * joy->axes[linear_];
            quart.y=0;
            quart.z=130 * joy->axes[linear_];
            quart.w=0;
            quart.x -= 120 * joy->axes[angular_];
            quart.z += 120 * joy->axes[angular_];
            if(quart.x<0)
                quart.x=0;
            if(quart.z<0)
                quart.z=0;
        }
    if (joy->axes[linear_]<0)
        {
            quart.x=0;
            quart.y=130 * joy->axes[linear_];
            quart.z=0;
            quart.w=130 * joy->axes[linear_];
            quart.y -= 120 * joy->axes[angular_];
            quart.w += 120 * joy->axes[angular_];
            if(quart.y<0)
                quart.x=0;
            if(quart.w<0)
                quart.z=0;
        }
    if (joy->axes[linear_]==0)
        {
            if (joy->axes[angular_]>0)
                {
                    quart.y = 120 * joy->axes[angular_];
                    quart.z = 120 * joy->axes[angular_];
                }
            if (joy->axes[angular_]<0)
            {
                quart.x = 120 * joy->axes[angular_] * (-1);
                quart.w = 120 * joy->axes[angular_] * (-1);
            }
        }
    bot_pub_.publish(quart);
    vel_pub_2.publish(quart);
    vel_pub_3.publish(quart);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teleop_turtle");
    TeleopTurtle teleop_turtle;
    ros::spin();
}
