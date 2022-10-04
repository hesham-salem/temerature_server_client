#include "rclcpp/rclcpp.hpp"
#include "temp_interfaces/srv/temp.hpp"
#include <memory>
#include <iostream>

class server_node : public rclcpp::Node
{

public:
    std::shared_ptr<rclcpp::Service<temp_interfaces::srv::Temp>> service;
    server_node() : Node("server_node")
    {
    }
    static void add(std::shared_ptr<temp_interfaces::srv::Temp::Request> Request,
                    std::shared_ptr<temp_interfaces::srv::Temp::Response>
                        response)
    {
        response->temp.temperature = 50.0;
    }
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<server_node>();
    auto service = node->create_service<temp_interfaces::srv::Temp>("temperature_degree", &server_node::add);
    rclcpp::spin(node);
    rclcpp::shutdown();
}
