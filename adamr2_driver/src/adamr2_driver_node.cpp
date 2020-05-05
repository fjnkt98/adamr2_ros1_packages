#include "adamr2_driver/adamr2_driver.h"
#include <ros/ros.h>
#include <controller_manager/controller_manager.h>

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "adamr2_driver_node");
  ros::NodeHandle nh;

  adamr2::Adamr2Driver driver;
  controller_manager::ControllerManager cm(&driver);

  ros::AsyncSpinner spinner(1);
  spinner.start();

  while(ros::ok()) {
    ros::Time now = driver.getTime();
    ros::Duration dt = driver.getPeriod();

    driver.write(now, dt);
    cm.update(now, dt);

    driver.read(now, dt);
    dt.sleep();
  }

  spinner.stop();

  return 0;
}
