#!/usr/bin/env python
import rospy
import tf
import math
from geometry_msgs.msg import Pose, Point, Quaternion, Twist #导入四个消息数据类型，姿态，目标点，四元数，运动消息Twist
import threading

x = 0
y = 0 

def callbackmove_vel(msg):
    global x 
    global y 
    x +=msg.linear.x * 0.1
    y +=msg.linear.y * 0.1
    # br = tf.TransformBroadcaster()
    # br.sendTransform((x, y, 0.0),(0.0, 0.0, 0.0, 1.0),rospy.Time.now(),"map","enemy_link")

def spin_th():
    while not rospy.is_shutdown():
        rospy.spin()

if __name__ == '__main__':
    rospy.init_node('my_tf_broadcaster')
    rospy.Subscriber("move_vel",Twist,callbackmove_vel)
    thread_spin = threading.Thread(target = spin_th)
    thread_spin.start()
    rate_tf = rospy.Rate(20)
    
    while not rospy.is_shutdown():
        br = tf.TransformBroadcaster()
        br.sendTransform((x, y, 0.0),(0.0, 0.0, 0.0, 1.0),rospy.Time.now(),"map","enemy_link")
        rate_tf.sleep()
    