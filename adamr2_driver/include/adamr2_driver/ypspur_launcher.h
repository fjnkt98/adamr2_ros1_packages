#ifndef ADAMR2_YPSPUR_LAUNCHER_H_
#define ADAMR2_YPSPUR_LAUNCHER_H_

#include <ros/ros.h>
#include <string>

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
      std::string ypspur_bin_;
      std::string param_file_;
      std::string device_path_;
  };
} // namespace adamr2

#endif