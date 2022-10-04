
#include "client_base.h"

client_node::client_node() : Node("temp_client")
{
    client = this->create_client<temp_interfaces::srv::Temp>("temperature_degree");
    request = std::make_shared<temp_interfaces::srv::Temp::Request>();
    client->wait_for_service(1s);
    result = client->async_send_request(request);
}

double client_node::getTemperature() const
{
    auto temp = result.get()->temp.temperature;
    if (!temp)
    {
        throw std::runtime_error("can't get temerature from server");
    }

    return temp;
}
