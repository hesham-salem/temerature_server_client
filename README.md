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


