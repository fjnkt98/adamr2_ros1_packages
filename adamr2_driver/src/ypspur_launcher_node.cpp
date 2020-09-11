#include "adamr2_driver/ypspur_launcher.h"

#include <ros/ros.h>

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "ypspur_launcher_node");
  ros::NodeHandle nh;

  adamr2::YPSpurLauncher ypspur_launcher;

  ros::spin();
  return 0;
}