#!/bin/bash
set -e

echo "Bring up the usb devices connection..."

sudo cp 70-adamr2-devices.rules /etc/udev/rules.d/

echo "Restarting udev..."

sudo udevadm control --reload

echo "Done."