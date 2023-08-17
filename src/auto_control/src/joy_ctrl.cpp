#include "joy_ctrl.h"


//弧度制归一化
double normalizeRadian(const double angle)
{
   double n_angle = std::fmod(angle, 2 * M_PI);
   n_angle = n_angle > M_PI ? n_angle - 2 * M_PI : n_angle < -M_PI ? 2 * M_PI + n_angle : n_angle;
   return n_angle;
}

double ABS_limit(double value,double limit)
{
  if(value<limit && value>-limit)
  {
    return 0;
  }
  else
  {
    return value;
  }

}

RobotCtrl::RobotCtrl()
{
    ros::NodeHandle nh;

    gimbal_yaw_position_cmd_ = nh.advertise<std_msgs::Float64>("/auto_car/yaw_steering_position_controller/command",10);
    gimbal_pitch_position_cmd_ = nh.advertise<std_msgs::Float64>("/auto_car/pitch_steering_position_controller/command",10);

    base_vel_pub = nh.advertise<geometry_msgs::Twist>("/base_vel",10);

    imu_sub_ = nh.subscribe("/imu", 1, &RobotCtrl::ImuCallback, this);
    joy_state_sub_ = nh.subscribe("/joy",1,&RobotCtrl::JoyCallback,this);
    jointstate_sub = nh.subscribe("/joint_states",10, &RobotCtrl::JointstateCallback,this);

    VX_ = 0.0;
    VY_ = 0.0;
    VW_ = 0.0;

}

void RobotCtrl::CmdVelCallback(const geometry_msgs::TwistConstPtr &msg)
{
  VX_ = msg->linear.x ;
  VY_ = msg->linear.y ;
  VW_ = msg->angular.z;
}

void RobotCtrl::ImuCallback(const sensor_msgs::Imu &msg)
{
  yaw_ = tf2::getYaw(msg.orientation);
  ROS_INFO("imu_yaw:%f",yaw_);
}

void RobotCtrl::JoyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
  joy_info_.left_axes[0] = ABS_limit(msg->axes[0],0.1);
  joy_info_.left_axes[1] = ABS_limit(msg->axes[1],0.1);
  joy_info_.right_axes[0] = ABS_limit(msg->axes[2],0.1);
  joy_info_.right_axes[1] = ABS_limit(msg->axes[3],0.1);
  joy_info_.up_axes[0] = ABS_limit(msg->axes[4],0.1);
  joy_info_.up_axes[1] = ABS_limit(msg->axes[5],0.1);
  joy_info_.axes_button[0] = ABS_limit(msg->axes[6],0.1);
  joy_info_.axes_button[1] = ABS_limit(msg->axes[7],0.1);

  joy_info_.button[0] = msg->buttons[0];
  joy_info_.button[1] = msg->buttons[1];
  joy_info_.button[2] = msg->buttons[3];
  joy_info_.button[3] = msg->buttons[4];
}

void RobotCtrl::BaseSolve()
{

  //if(joy_info_.up_axes[0]<0)
 // {
  VX_ =  joy_info_.right_axes[1];
  VY_ =  joy_info_.right_axes[0];
  a_gimbal_pitch_position = 0;
  a_gimbal_yaw_position = yaw_;
  //set prev diff_time
  vx_ = VX_ * cos(-yaw_) - VY_ * sin(-yaw_);
  vy_ = VX_ * sin(-yaw_) + VY_ * cos(-yaw_);
  vw_ = 2.5;
  //}
//   else
//   {
//  // vx_ =  joy_info_.right_axes[1];
//   // vy_ =  joy_info_.right_axes[0];
//   // vw_ =  joy_info_.left_axes[0];
//   // a_gimbal_pitch_position = 0;
//   // a_gimbal_yaw_position = 0;
//   //a_gimbal_yaw_position = -yaw_;
//   }
  PubControlCmd();
}

void RobotCtrl::PubControlCmd()
{
  std_msgs::Float64 cmd;
  cmd.data = a_gimbal_pitch_position;
  gimbal_pitch_position_cmd_.publish(cmd);
  cmd.data = a_gimbal_yaw_position;
  gimbal_yaw_position_cmd_.publish(cmd);

  geometry_msgs::Twist twist_cmd;
  twist_cmd.linear.x = vx_;
  twist_cmd.linear.y = vy_;
  twist_cmd.angular.z = vw_;
  base_vel_pub.publish(twist_cmd);


}


void RobotCtrl::JointstateCallback(const sensor_msgs::JointStateConstPtr &msg){
  cur_gimbal_yaw_position = msg->position.at(0);
  cur_gimbal_pitch_position = msg->position.at(1);

}

int main(int argc,char **argv)
{
  ros::init(argc, argv, "joy_ctrl");
  RobotCtrl robotctrl;
  ros::Rate loop_rate(10);

  while(ros::ok()){
    ros::spinOnce();
    robotctrl.BaseSolve();
    loop_rate.sleep();

  } 
}