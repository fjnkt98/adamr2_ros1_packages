#include <string>
#include <cerrno>
#include <cstring>
#include <exception>
#include <stdexcept>

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
  YPSpurLauncher::YPSpurLauncher()
  : pnh_("~") 
  {
    pnh_.param("ypspur_bin", ypspur_bin_, std::string("ypspur-coordinator"));
    pnh_.param("param_file", param_file_, std::string(""));
    pnh_.param("device_path", device_path_, std::string("/dev/ttyACM0"));

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
    } else if (pid_ == 0) {
      execlp(ypspur_bin_.c_str(), ypspur_bin_.c_str(), "-p", param_file_.c_str(), "-d", device_path_.c_str(), NULL);
      throw(std::runtime_error("failed to start ypspur-coordinator."));
    }
  }

  void YPSpurLauncher::terminate() {
    ROS_INFO("Killing ypspur-coordinator: (%d)", static_cast<int>(pid_));

    kill(pid_, SIGINT);
    
    int status = 0;
    pid_t result = waitpid(pid_, &status, 0);

    if (result < 0) {
      throw(std::runtime_error("failed to terminate subprocess"));
    }

    if (WIFEXITED(status)) {
      ROS_INFO("ypspur-coordinator is exited with code: %d)", WEXITSTATUS(status));
    } else {
      ROS_INFO("ypspur-coordinator is terminated with status: %d)", static_cast<int>(status));
    }
  }

  void YPSpurLauncher::relaunch() {
    if (!this->processIsAlive()) {
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