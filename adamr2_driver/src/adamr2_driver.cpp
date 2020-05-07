#include "adamr2_driver/adamr2_driver.h"
#include <ros/ros.h>

//extern "C" {
#include <ypspur.h>
//}

namespace adamr2 {
  Adamr2Driver::Adamr2Driver() {
    // YP-Spur initialization.
    if (this->open() < 0) {
      ROS_WARN_STREAM("Error: Couldn't open spur.\n");
    }

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

  Adamr2Driver::~Adamr2Driver() {
    this->stop();
  }

  int Adamr2Driver::open() const {
    int ret = Spur_init();

    // Set the maximum angular velocity and acceleration.
    // unit is [rad/s] and [rad/s^2] in tire axis.
    YP_set_wheel_vel(13.0, 13.0);
    YP_set_wheel_accel(13.0, 13.0);

    return ret;
  }

  void Adamr2Driver::stop() const {
    YP_wheel_vel(0, 0);
    Spur_stop();
    ros::Duration(1).sleep();
    Spur_free();
  }

  void Adamr2Driver::read(ros::Time time, ros::Duration period) {
    // yp_vel[0] is right wheel velocity, yp_vel[1] is left wheel velocity.
    double yp_vel[2] = {0.0, 0.0};
    YP_get_wheel_vel(&yp_vel[0], &yp_vel[1]);

    // Reverse the velocity of the right wheel.
    // This is due to the coordinate system of the right wheel.
    yp_vel[0] = -yp_vel[0];

    for (unsigned int i = 0; i < 2; i++) {
      pos_[i] += yp_vel[i] * period.toSec();
      vel_[i] = yp_vel[i];
    }
  }

  void Adamr2Driver::write(ros::Time time, ros::Duration period) {
    YP_wheel_vel(-cmd_[0], cmd_[1]);
  }
} // namespace adamr2
