#!/bin/bash

# Default to ROS 2 if not specified
VERSION=${1:-2}

if [ "$VERSION" -eq "1" ]; then
    echo "Switching to ROS 1 configuration..."
    ln -sf package_ros1.xml package.xml
    echo "Done. You can now build with 'catkin_make'."
elif [ "$VERSION" -eq "2" ]; then
    echo "Switching to ROS 2 configuration..."
    ln -sf package_ros2.xml package.xml
    echo "Done. You can now build with 'colcon build'."
else
    echo "Invalid version. Use 1 or 2."
    exit 1
fi
