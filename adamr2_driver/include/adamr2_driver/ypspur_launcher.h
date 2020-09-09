#ifndef ADAMR2_YPSPUR_LAUNCHER_H_
#define ADAMR2_YPSPUR_LAUNCHER_H_

#include <ros/ros.h>
#include <ypspur.h>

namespace unistd {
  #include <unistd.h>
} // namespace unistd

namespace sys {
  #include <sys/types.h>
  #include <sys/wait.h>
} // namespace sys

namespace adamr2 {
  class YPSpurLauncher {
    public:
      YPSpurLauncher();
      ~YPSpurLauncher();

    int launch();
    int kill();
    int relaunch();
    bool isAlive();

    private:
      unistd::pid_t pid_;
      ros::NodeHandle pnh_;
  }
} // namespace adamr2

#endif