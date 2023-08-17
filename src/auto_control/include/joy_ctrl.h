#ifndef JOY_CTRL_H
#define JOY_CTRL_H

#include <cmath>
#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <std_msgs/Float64.h>
#include <tf2/utils.h>
#include <iostream>
#include"geometry_msgs/Twist.h"
#include "sensor_msgs/JointState.h"
#include "sensor_msgs/Joy.h"
#include "std_msgs/Float64MultiArray.h"

   typedef struct
   {
       float left_axes[2];// l f 
       float right_axes[2];// l f
       float up_axes[2];// r l
       float axes_button[2];// l-r f-b
       uint8_t button[4]; //ABXY
   } joy_info_t;


class RobotCtrl {
    public:
    RobotCtrl();
    ~RobotCtrl() = default;
    void ImuCallback(const sensor_msgs::Imu &msg);
    void CmdVelCallback(const geometry_msgs::TwistConstPtr &msg);
    void JointstateCallback(const sensor_msgs::JointStateConstPtr &msg);
    void JoyCallback(const sensor_msgs::Joy::ConstPtr& msg);
 
    void BaseSolve();
    void PubControlCmd();

private:
    ros::Publisher gimbal_yaw_position_cmd_;
    ros::Publisher gimbal_pitch_position_cmd_;
    ros::Publisher base_vel_pub;

    ros::Subscriber cmd_vel_sub_;
    ros::Subscriber joy_state_sub_;    
    ros::Subscriber imu_sub_;
    ros::Subscriber jointstate_sub;

    double a_gimbal_yaw_position;  //
    double a_gimbal_pitch_position;  //

    double cur_gimbal_yaw_position;
    double cur_gimbal_pitch_position;

    double VX_;   //设定的全局坐标系线速度
    double VY_;   //设定的全局坐标系线速度
    double VW_;

    double vx_;   // 车身坐标系x方向线速度
    double vy_;   // 车身坐标系y方向线速度
    double vw_;   // 角速度

    double yaw_;  //机器人航向角

    joy_info_t joy_info_; //手柄数据



};
#endif 
