FROM ros:foxy
ENV HOME=/av_ws
WORKDIR $HOME
SHELL ["/bin/bash", "-c"]
COPY . /temperature_ws/
RUN sudo apt-get update
RUN sudo apt-get install libfmt-dev
RUN source /opt/ros/foxy/setup.bash &&colcon build
CMD  source install/setup.bash && ros2 launch script/launch.yaml 