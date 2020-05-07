#ifndef ADAMR2_ADAMR2_DRIVER_H_
#define ADAMR2_ADAMR2_DRIVER_H_

#include <ros/ros.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/robot_hw.h>

namespace adamr2 {
  class Adamr2Driver : public hardware_interface::RobotHW {
    public:
      Adamr2Driver();
      ~Adamr2Driver();

      ros::Time getTime() const {
        return ros::Time::now();
      }

      ros::Duration getPeriod() const {
        return ros::Duration(0.01);
      }

      void reopen();
      void read(ros::Time, ros::Duration);
      void write(ros::Time, ros::Duration);

    protected:
      hardware_interface::JointStateInterface joint_state_interface;
      hardware_interface::VelocityJointInterface joint_vel_interface;
      double cmd_[2];
      double pos_[2];
      double vel_[2];
      double eff_[2];
  };
} // namespace adamr2

#endif
