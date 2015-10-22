//converting the cmd_vel commands from move_base into quaternion and publishing them to motormsg. 
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Quaternion.h>

class TeleopTurtle
{
    public:
        TeleopTurtle();
    private:
        void joyCallback(const geometry_msgs::Twist cmd);
        ros::NodeHandle nh_;
        int linear_, angular_;
        double l_scale_, a_scale_;
        ros::Publisher vel_pub_;
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

    joy_sub_ = nh_.subscribe<geometry_msgs::Twist>("/cmd_vel", 10, &TeleopTurtle::joyCallback, this);

    bot_pub_ = nh_.advertise<geometry_msgs::Quaternion>("fair/cmd_vel", 1);
}

void TeleopTurtle::joyCallback(const geometry_msgs::Twist cmd)
{
    // geometry_msgs::Twist twist;
    // twist.linear.x = l_scale_*joy->axes[linear_];
    // twist.angular.z = a_scale_*joy->axes[angular_];
    // vel_pub_.publish(twist);
    geometry_msgs::Quaternion quart;
    //axis up means linear>0 -----x
    //axis down means linear<0 -----y
    //axis left means angular>0 -----z
    //axis right means angular<0 -----w

    if (cmd.linear.x>0)
        {
            quart.x=130 * cmd.linear.x;
            quart.y=0;
            quart.z=130 * cmd.linear.x;
            quart.w=0;
            quart.x -= 120 * cmd.angular.z;
            quart.z += 120 * cmd.angular.z;
            if(quart.x<0)
                quart.x=0;
            if(quart.z<0)
                quart.z=0;
        }
    if (cmd.linear.x<0)
        {
            quart.x=0;
            quart.y= 130 * cmd.linear.x;
            quart.z=0;
            quart.w= 130 * cmd.linear.x;
            quart.y += 120 * cmd.angular.z;
            quart.w -= 120 * cmd.angular.z;
            if(quart.y<0)
                quart.x=0;
            if(quart.w<0)
                quart.z=0;
        }
    if (cmd.linear.x==0)
        {
            if (cmd.angular.z>0)
                {
                    quart.y = (-120) * cmd.angular.z;
                    quart.z = 120 * cmd.angular.z;
                }
            if (cmd.angular.z<0)
            {
                quart.x = 120 * cmd.angular.z * (-1);
                quart.w = (-120) * cmd.angular.z * (-1);
            }
        }
    bot_pub_.publish(quart);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "teleop_turtle");
    TeleopTurtle teleop_turtle;
    ros::spin();
}