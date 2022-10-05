FROM ros:foxy
ENV HOME=/temerature_ws
WORKDIR $HOME
SHELL ["/bin/bash", "-c"]
COPY . /$HOME/
RUN sudo apt-get update
RUN sudo apt-get install libfmt-dev
RUN source /opt/ros/foxy/setup.bash &&colcon build
CMD  source install/setup.bash && ros2 launch scripts/launch.yaml 