#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
// #include <tf/Quaternion.h>
// #include <tf/Vector3.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/Quaternion.h>
#include <std_msgs/Float64.h> 

ros::Subscriber angle_sub;
double pitch=0; 

void angle_callback(std_msgs::Float64::ConstPtr & angle_msg)
  {   pitch = angle_msg.data;      
  }

int main(int argc, char** argv)
  {
      ros::init(argc, argv, "robot_tf_publisher");
      ros::NodeHandle n;

      ros::Rate r(100);
      kinect_angle_sub = nh_.subscribe<std_msgs::Float64>("cur_tilt_angle",10,&angle_callback,this);
      tf::TransformBroadcaster broadcaster;

      while(n.ok())
        {   
            tf::Quaternion quar; 
            quar.setRPY(0.0,pitch,0.0);
            tf::Vector3 vect(0.1905,0.0,1.1176);

            // broadcaster.sendTransform(
            //             tf::StampedTransform(
            //                 tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.1905, 0.0, 1.1176)),
            //                 ros::Time::now(),"base_link", "camera_link"));

            tf::StampedTransform 
            broadcaster.sendTransform( 
                        tf::StampedTransform(
                            tf::Transform(quar,vect),
                            ros::Time::now(),"base_link", "camera_link"));            
            r.sleep();
        }
  }




