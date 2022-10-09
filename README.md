## temerature_server_client

the system base on ROS2 which is based on dds protocol 
which provide us real time server client commuincation and flexability to add more nodes to dds
also provide standard massage for example temperature msg

```
 # Single temperature reading.

 Header header           # timestamp is the time the temperature was measured
                         # frame_id is the location of the temperature reading

 float64 temperature     # Measurement of the Temperature in Degrees Celsius

 float64 variance        # 0 is interpreted as variance unknown
```

- it prefer to run the system from the container to avoid Dependency erorrs
- every node has its cmakelists
- run all nodes from launch.yaml file in script


![ros2 architecture ](https://automaticaddison.com/wp-content/uploads/2021/11/ros-architecture.jpg)

## the Purpose

The purpose of this base class is to encapsulate common functionality of a controller.
This common functionality is then intended to ease the implementation of specific controller
algorithms.

## Implementing by Child Classes

```c++
compute_command_impl(State)=0;
virtual check_new_trajectory(Trajectory);
virtual handle_new_trajectory(Trajectory)

```

## Implementing by base Classes

```
class BehaviorConfig;
ControllerBase::ControllerBase(const BehaviorConfig & config);
```

```c++
Command ControllerBase::compute_command(const State & state)
{
  if (m_reference_trajectory.points.empty()) {
    return compute_stop_command(state);
  }
  if (state.header.frame_id != m_reference_trajectory.header.frame_id) {
    throw std::domain_error{"Vehicle state is not in same frame as reference trajectory"};
  }
  update_reference_indices(state);
  if (!is_state_ok(state)) {
    return compute_stop_command(state);
  }
  auto ret = compute_command_impl(state);
  // Ensure you're properly populating the stamp
  ret.stamp = state.header.stamp;
  return ret;
}


