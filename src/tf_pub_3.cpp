#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

int main(int argc, char** argv){
  ros::init(argc, argv, "robot_tf_publisher");
  ros::NodeHandle n;

  ros::Rate r(100);

  tf::TransformBroadcaster broadcaster;
  tf::Quaternion quar_1, quar_2; 
  tf::Vector3 vect_1(0.1905, 0.0, 1.1176), vect_2(0.0,0.0,0.0);
  quar_1.setRPY(0.0, 0.0, 0.0);
  quar_2.setRPY(0.0*0.0174,0.0,0.0);
  while(n.ok()){
    broadcaster.sendTransform(
      tf::StampedTransform(
        // tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.2)),
        tf::Transform(quar_1,vect_1),
        ros::Time::now(),"base_link", "camera_link"));
    // broadcaster.sendTransform(
    //   tf::StampedTransform(
    //     // tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.0, 0.0, 0.0)),        
    //     tf::Transform(quar_2,vect_2),
    //     ros::Time::now(),"camera_link", "camera_rgb_optical_frame"));
    r.sleep();
  }
}