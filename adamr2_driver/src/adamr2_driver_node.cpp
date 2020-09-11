#include "adamr2_driver/adamr2_driver.h"
//#include "adamr2_driver/ypspur_launcher.h"
#include <ros/ros.h>
#include <controller_manager/controller_manager.h>

//extern "C" {
#include <ypspur.h>
//}

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

    if (YP_get_error_state() == 0) {
      driver.write(now, dt);
      cm.update(now, dt);

      driver.read(now, dt);
    } else {
      ROS_WARN("T-Frog driver disconnected.");
      driver.stop();

      while (driver.open() < 0) {
        ROS_WARN("Try to connect T-Frog driver...");
        ros::Duration(1).sleep();
      }

      ROS_INFO("T-Frog driver connected.");
    }

    dt.sleep();
  }

  spinner.stop();

  return 0;
}
