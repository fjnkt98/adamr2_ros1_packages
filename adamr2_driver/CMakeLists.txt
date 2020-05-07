cmake_minimum_required(VERSION 2.8.3)
project(adamr2_driver)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  hardware_interface
  transmission_interface
  controller_manager
)

catkin_package()

find_library(ypspur_LIBRARIES ypspur)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${ypspur_INCLUDE_DIRS}
)

add_executable(adamr2_driver_node
  src/adamr2_driver_node.cpp
  src/adamr2_driver.cpp
)

target_link_libraries(adamr2_driver_node
  ${catkin_LIBRARIES}
  ${ypspur_LIBRARIES}
)
