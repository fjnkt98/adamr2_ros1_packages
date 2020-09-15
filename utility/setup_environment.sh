#!/bin/bash
set -e

# Giving the file permission to execute.
cd ~/catkin_ws/src/adamr2_ros1_packages/adamr2_control/scripts
chmod +x ypspur_launcher.sh

# Create the directory for some experiments
if [ ! -e ~/adamr2_experiments ]; then
  cd ~/
  mkdir adamr2_experiments
  cd adamr2_experiments
  mkdir simulation
  mkdir real

  echo "The directory succesfully generated!"
else
  echo "The directory already exist."
fi