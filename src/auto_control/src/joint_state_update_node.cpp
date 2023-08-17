
#include "joint_state_update_node.h"

using namespace std;
float yaw_angle;
float pitch_angle;


void Gimbal_Fdb_Callback(const roborts_msgs::GimbalFdb::ConstPtr& msg){
yaw_angle = msg->yaw_fdb;
pitch_angle = msg->pitch_fdb;

}

int main(int argc, char** argv)
 {
    ros::init(argc, argv, "joint_state_update_node"); //节点的名称
    ros::NodeHandle n;
    ros::Publisher joint_pub = n.advertise<sensor_msgs::JointState>("/auto_car/joint_states", 1);    //设置一个发布者，将消息发布出去,发布到相应的节点中去

    ros::Subscriber joint_odom = n.subscribe<roborts_msgs::GimbalFdb>("/gimbal_fdb",1,&Gimbal_Fdb_Callback);

    ros::Rate loop_rate(100);    
    const double degree = M_PI/180;
    // robot state
    // message declarations
    sensor_msgs::JointState joint_state;

    while (ros::ok()) {
        //update joint_state
        joint_state.header.stamp = ros::Time::now();
        joint_state.name.resize(6);
        joint_state.position.resize(6);
        joint_state.velocity.resize(6);
	joint_state.name[0]="fl_wheel_joint";
        joint_state.position[0] = 0;
	joint_state.name[1] ="fr_wheel_joint";
        joint_state.position[1] = 0 ;
        joint_state.name[2] ="pitch_steering_joint";
        joint_state.position[2] = pitch_angle;//*degree ;
        joint_state.name[3] ="rl_wheel_joint";
        joint_state.position[3] = 0 ;
        joint_state.name[4] ="rr_wheel_joint";
        joint_state.position[4] = 0 ;
        joint_state.name[5] ="yaw_steering_joint";
        joint_state.position[5] = -yaw_angle;//*degree;
        ros::spinOnce();
        //send the joint state and transform
        joint_pub.publish(joint_state);

        // This will adjust as needed per iteration
        loop_rate.sleep();
    }

    return 0;
}

