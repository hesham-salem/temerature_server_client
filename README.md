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


```

```c++
Command ControllerBase::compute_stop_command(const State & state) const noexcept;
```

```c++
/* On each call to compute_command(State), the reference index with respect to the trajectory is
updated. The reference index is the last point the given state is past (or equal to).

The reference index can only increase with subsequent calls to compute_command(State)

The reference index is reset to 0 on calls to set_trajectory(Trajectory) variants

Different algorithms work on spatial or temporal references. As such, an API for both tracking
the current state in both the time and space sense is provided.
*/
void ControllerBase::update_reference_indices(const State & new_state) noexcept
{
  // Update spatial index
  const auto space_f =
    [](const State & state, const Point & pt1, const Point & pt2, const Trajectory &) ->bool 		{
      return motion_common::is_past_point(state.state, pt1, pt2);
		};
  using motion_common::update_reference_index;
  m_reference_spatial_index =
    update_reference_index(m_reference_trajectory, new_state, m_reference_spatial_index, space_f);
  // Update temporal index
  const auto time_f =
    [](const State & state, const Point &, const Point & pt, const Trajectory & traj) -> bool {
      using time_utils::from_message;
      const auto t_s = from_message(state.header.stamp);
      const auto t_t = from_message(traj.header.stamp);
      const auto dt = from_message(pt.time_from_start);
      return t_s >= (t_t + dt);
    };
  m_reference_temporal_index =
    update_reference_index(m_reference_trajectory, new_state, m_reference_temporal_index, time_f);
}

```

```c++
bool ControllerBase::is_state_ok(const State & state) const noexcept 
```

check if state and trajectory the same in position and time 

```
bool ControllerBase::is_past_trajectory(const State & state) const noexcept
void ControllerBase::set_trajectory(const Trajectory & trajectory);

```

````c++
Point ControllerBase::predict(const Point & point
std::chrono::nanoseconds dt) noexcept
void ControllerBase::set_trajectory_impl();

```
````
