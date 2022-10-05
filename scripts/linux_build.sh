#!/bin/sh
colcon build
source ../install/setup.bash
ros2 launch launch.yaml 
 