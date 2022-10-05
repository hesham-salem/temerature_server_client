#include "server_base.h"
#include "server.h"

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<server_node>();
    auto service = node->create_service<temp_interfaces::srv::Temp>("temperature_degree", &server_node::add);
    rclcpp::spin(node);
    rclcpp::shutdown();
}
