#include "adamr2_driver/adamr2_driver.h"
#include <ros/ros.h>
#include <controller_manager/controller_manager.h>
#include <diagnostic_updater/diagnostic_updater.h>
#include <diagnostic_updater/DiagnosticStatusWrapper.h>

//extern "C" {
#include <ypspur.h>
//}

int main(int argc, char *argv[]) {
  ros::init(argc, argv, "adamr2_driver_node");
  ros::NodeHandle nh;

  // Controller Configuration
  adamr2::Adamr2Driver driver;
  controller_manager::ControllerManager cm(&driver);

  // Diagnostics Configuration
  diagnostic_updater::Updater updater;
  updater.setHardwareID("T-Frog Driver");
  updater.add("Board Status", &driver, &adamr2::Adamr2Driver::updateDiagnostics);

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

    updater.update();

    dt.sleep();
  }

  spinner.stop();

  return 0;
}
