#!/bin/bash
set -e

TODAY=$(date "+%Y%m%d")

if [ ! -e ~/adamr2_experiments/simulation/slam/${TODAY} ]; then
  mkdir -p ~/adamr2_experiments/simulation/slam/${TODAY}
fi

cd ~/adamr2_experiments/simulation/slam/${TODAY}
DIR_NUM=$(ls -l | grep ^d | wc -l)
TITLE_NUM=$((++DIR_NUM))

mkdir exp$((TITLE_NUM))
cd exp$((TITLE_NUM))

mkdir bag
cd bag

rosbag record -O slam_bag /tf /tf_static /clock /scan __name:=slam_bagger