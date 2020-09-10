#ifndef ADAMR2_YPSPUR_LAUNCHER_H_
#define ADAMR2_YPSPUR_LAUNCHER_H_

#include <ros/ros.h>

namespace adamr2 {
  class YPSpurLauncher {
    public:
      YPSpurLauncher();
      ~YPSpurLauncher();

    void launch();
    void terminate();
    void relaunch();
    bool processIsAlive();

    private:
      pid_t pid_;
      ros::NodeHandle pnh_;
  };
} // namespace adamr2

#endif