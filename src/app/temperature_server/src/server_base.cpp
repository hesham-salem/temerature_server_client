#include "server_base.h"

server_node::server_node() noexcept : Node("server_node")
{
}
void server_node::add(std::shared_ptr<temp_interfaces::srv::Temp::Request> Request,
                      std::shared_ptr<temp_interfaces::srv::Temp::Response>
                          response)
{
    response->temp.temperature = 50.0;
}