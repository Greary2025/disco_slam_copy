#!/bin/bash
set -e

echo "Starting ROS 2 Humble installation for Ubuntu 22.04..."

# 1. Set locale
echo "Setting up locale..."
sudo apt update && sudo apt install -y locales
sudo locale-gen en_US en_US.UTF-8
sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
export LANG=en_US.UTF-8

# 2. Setup Sources
echo "Setting up sources..."
sudo apt install -y software-properties-common
sudo add-apt-repository universe -y

sudo apt update && sudo apt install -y curl gnupg lsb-release
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg

echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(source /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# 3. Install ROS 2 packages
echo "Installing ROS 2 Humble..."
sudo apt update
sudo apt install -y ros-humble-desktop
sudo apt install -y ros-dev-tools

# 4. Initialize rosdep (Using rosdepc for better connectivity)
echo "Installing python3-pip and rosdepc..."
sudo apt install -y python3-pip
sudo pip3 install -U rosdepc

echo "Initializing rosdepc..."
if [ ! -f /etc/ros/rosdep/sources.list.d/20-default.list ]; then
    sudo rosdepc init
fi
rosdepc update

# 5. Install dependencies for the project (mapped from ROS 1 to ROS 2)
echo "Installing project dependencies..."
sudo apt install -y ros-humble-navigation2 ros-humble-nav2-bringup
sudo apt install -y ros-humble-robot-localization
sudo apt install -y ros-humble-robot-state-publisher
sudo apt install -y ros-humble-pcl-conversions
sudo apt install -y ros-humble-cv-bridge
sudo apt install -y ros-humble-tf2-geometry-msgs
sudo apt install -y ros-humble-xacro

# Install GTSAM
echo "Installing ros-humble-gtsam..."
sudo apt install -y ros-humble-gtsam

# Install libnabo
echo "Installing ros-humble-libnabo..."
sudo apt install -y ros-humble-libnabo

# 6. Environment setup
echo "Sourcing setup script..."
source /opt/ros/humble/setup.bash

echo "Installation complete!"
echo "Please add 'source /opt/ros/humble/setup.bash' to your ~/.bashrc if you haven't already."
