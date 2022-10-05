#include "rclcpp/rclcpp.hpp"
#include "temp_interfaces/srv/temp.hpp"
#include <memory>

class server_node : public rclcpp::Node
{

public:
    std::shared_ptr<rclcpp::Service<temp_interfaces::srv::Temp>> service;
    server_node() noexcept;

    static void add(std::shared_ptr<temp_interfaces::srv::Temp::Request> Request,
                    std::shared_ptr<temp_interfaces::srv::Temp::Response>
                        response);
};