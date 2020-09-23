#!/bin/bash
set -e

TODAY=$(date "+%Y%m%d")

TARGET_DIR="~/adamr2_experiments/real/slam/${TODAY}"

if [ ! -e ~/adamr2_experiments/real/slam/${TODAY} ]; then
  mkdir -p ~/adamr2_experiments/real/slam/${TODAY}
fi

cd ~/adamr2_experiments/real/slam/${TODAY}

DIR_NUM=$(ls -l | grep ^d | wc -l)
TITLE_NUM=$((++DIR_NUM))

mkdir exp$((TITLE_NUM))
cd exp$((TITLE_NUM))

mkdir bag && cd bag

rosbag record /tf \
              /tf_static \
              /adamr2/camera/depth/color/points \
              /adamr2/camera/color/image_raw \
              /adamr2/scan \
              /adamr2/diff_drive_controller/odom \
