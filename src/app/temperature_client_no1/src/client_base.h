#include "rclcpp/rclcpp.hpp"
#include "temp_interfaces/srv/temp.hpp"
#include <thread>
#include <chrono>
#include <memory>

using namespace std::chrono_literals;
using namespace std::this_thread; // sleep_for, sleep_until

class client_node : public rclcpp::Node
{
private:
    std::shared_ptr<temp_interfaces::srv::Temp_Request> request;
    std::shared_ptr<rclcpp::Client<temp_interfaces::srv::Temp>> client;

public:
    client_node();

    std::shared_future<std::shared_ptr<temp_interfaces::srv::Temp_Response>> result;

    double getTemperature() const;
};