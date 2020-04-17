#!/bin/bash

# Execute yp-spur in background
# Argument 1 is the path of parameter file
# Argument 2 is the device file of the motor driver
ypspur-coordinator -p $1 -d $2 &
echo "Robot parameters [$1] loaded."

# If yp-spur is dead, reboot it.
while true
  do
    isAlive=`ps -ef | grep " ypspur-coordinator " | \
    grep -v grep | wc -l`

    if [ $isAlive = 1 ]; then
      : #pass
    else
      ypspur-coordinator -p $1 -d $2 &
      echo "ypspur restarted."
    fi

    sleep 1
  done