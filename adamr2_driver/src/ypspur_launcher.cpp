#include <cerrno>
#include <cstring>
#include <exception>

#include <ros/ros.h>
#include <ypspur.h>

extern "C" {
  #include <unistd.h>
  #include <sys/types.h>
  #include <sys/wait.h>
  #include <signal.h>
}

#include "adamr2_driver/ypspur_launcher.h"

namespace adamr2 {
  YPSpurLauncher::YPSpurLauncher() {
    try {
      this->launch();
    }
    catch(std::runtime_error& e) {
      ROS_ERROR("%s", e.what());
    }
  }

  YPSpurLauncher::~YPSpurLauncher() {
    if (pid_ > 0 && YP_get_error_state() == 0) {
      this->terminate();
    }
  }

  void YPSpurLauncher::launch() {
    pid_ = fork();

    if (pid_ < 0) {
      const int err = errno;
      throw(std::runtime_error(std::string("failed to fork process: ") + std::strerror(err)));
    } else if (pid_ = 0) {
      //execlp();
      throw(std::runtime_error("failed to start ypspur-coordinator."));
    }
  }

  void YPSpurLauncher::terminate() {
    ROS_INFO("Killing ypspur-coordinator: (%d)", static_cast<int>(pid_));
    kill(pid_, SIGINT);
    int status = 0;
    waitpid(pid_, &status, 0);
    ROS_INFO("ypspur-coordinator is killed. (status: %d)", status);
  }

  void YPSpurLauncher::relaunch() {
    if (!this->procesIsAlive()) {
      this->terminate();
      this->launch();
    }
  }

  bool YPSpurLauncher::processIsAlive() {
    // シグナル番号0を送ることでプロセスが存在するか確認する
    int result = (pid_, 0);

    if (result == 0) {
      // プロセスが存在する
      return true;
    }
    
    if (EPERM == errno) {
      // プロセスは存在するがシグナルを送る権限が無い
      return true;
    }

    // プロセスは存在しない
    return false;
  }
} // namespace adamr2