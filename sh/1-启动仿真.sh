#!/bin/bash
source /opt/ros/noetic/setup.bash
source ~/auto_infantry_ws/devel/setup.bash


gnome-terminal -x bash -c "roslaunch auto_car gazebo.launch;exec bash"
sleep 3
gnome-terminal -x bash -c "roslaunch auto_control taurus_control.launch;exec bash"
sleep 3
gnome-terminal -x bash -c "roslaunch auto_nav navi_pid_follow_simulink.launch;exec bash"
sleep 3
#gnome-terminal -x bash -c "rosrun auto_nav auto_fsm.py;exec bash"
