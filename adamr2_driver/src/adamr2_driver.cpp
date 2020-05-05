#include "adamr2_driver/adamr2_driver.h"
#include <ros/ros.h>

namespace adamr2 {
  Adamr2Driver::Adamr2Driver() {
		pos_[0] = 0.0;
    pos_[1] = 0.0;
    vel_[0] = 0.0;
    vel_[1] = 0.0;
    eff_[0] = 0.0;
    eff_[1] = 0.0;
    cmd_[0] = 0.0;
    cmd_[1] = 0.0;

    // Joint state setting for right-wheel-joint
    hardware_interface::JointStateHandle state_handle_1("right_wheel_joint", &pos_[0], &vel_[0], &eff_[0]);
    joint_state_interface.registerHandle(state_handle_1);
    // Joint state setting for left-wheel-joint
    hardware_interface::JointStateHandle state_handle_2("left_wheel_joint", &pos_[1], &vel_[0], &eff_[0]);
    joint_state_interface.registerHandle(state_handle_2);

    registerInterface(&joint_state_interface);

    // Joint handle setting for right-wheel-joint
    hardware_interface::JointHandle vel_handle_1(joint_state_interface.getHandle("right_wheel_joint"), &cmd_[0]);
    joint_vel_interface.registerHandle(vel_handle_1);
    // Joint handle setting for left-wheel-joint
    hardware_interface::JointHandle vel_handle_2(joint_state_interface.getHandle("left_wheel_joint"), &cmd_[1]);
    joint_vel_interface.registerHandle(vel_handle_2);

    registerInterface(&joint_vel_interface);
  }

  void Adamr2Driver::read(ros::Time time, ros::Duration period) {
    ROS_INFO("read read read...");
  }

  void Adamr2Driver::write(ros::Time time, ros::Duration period) {
    ROS_INFO("write write write...");
  }
} // namespace adamr2
