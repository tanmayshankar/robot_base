#!/usr/bin/env python
import rospy
from std_msgs.msg import String
import roslib
from nav_msgs.msg import Odometry
import numpy as npy

trial_element="Hello"

def callback(data):
    # rospy.loginfo(rospy.get_caller_id() + "I heard %s", data.data)
    #rospy.loginfo(rospy.get_caller_id() + "Data read was %s", data.data)
    trial_element=data.pose.pose.position    
    print trial_element
    
def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # node are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique    
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    
    rospy.init_node('listener', anonymous=True)
    # rospy.Subscriber("chatter", String, callback)
    rospy.Subscriber("/az3/base_controller/odom", Odometry, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()

if __name__ == '__main__':
    listener()