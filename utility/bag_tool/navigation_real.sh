#!/bin/bash
set -e

TODAY=$(date "+%Y%m%d")

TARGET_DIR="/home/${USER}/adamr2_experiments/real/navigation/${TODAY}"

if [ ! -e $TARGET_DIR ]; then
  mkdir -p $TARGET_DIR
  echo "-- Target directory was successfully generated. --"
fi

cd $TARGET_DIR

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
              /amcl_pose \
              /particlecloud \
              /map \
              /move_base/TrajectoryPlannerROS/global_plan \
              /move_base/TrajectoryPlannerROS/local_plan \
              /move_base/GlobalPlanner/plan \
              /move_base/current_goal \
              /move_base/global_costmap/costmap \
              /move_base/global_costmap/costmap_updates \
              /move_base/global_costmap/footprint \
              /move_base/goal \
              /move_base_simple/goal \
              /move_base/local_costmap/costmap \
              /move_base/local_costmap/costmap_updates \
              /move_base/local_costmap/footprint