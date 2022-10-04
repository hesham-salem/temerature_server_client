#include "rclcpp/rclcpp.hpp"
#include "temp_interfaces/srv/temp.hpp"
#include <thread>
#include <chrono>
#include <cstdlib>
#include <memory>
#include <fmt/core.h>
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono_literals;
using namespace std::chrono;

class client_node : public rclcpp::Node
{
private:
    std::shared_ptr<temp_interfaces::srv::Temp_Request> request;
    std::shared_ptr<rclcpp::Client<temp_interfaces::srv::Temp>> client;

public:
    std::shared_future<std::shared_ptr<temp_interfaces::srv::Temp_Response>> result;

    client_node() noexcept : Node("temp_client")
    {
        client = this->create_client<temp_interfaces::srv::Temp>("temperature_degree");
        request = std::make_shared<temp_interfaces::srv::Temp::Request>();
        client->wait_for_service(1s);
        result = client->async_send_request(request);
    }

    double getTemperature() const
    {
        auto temp = result.get()->temp.temperature;
        if (!temp)
        {
            throw std::runtime_error("can't get temerature from server");
        }

        return temp;
    }
};
using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<client_node>();
    auto count{0};
    double accumulation{0};
    while (1)
    {

        try
        {

            if (rclcpp::spin_until_future_complete(node, node.get()->result) != rclcpp::FutureReturnCode::SUCCESS)
                throw std::runtime_error("can't get temerature from server");

            accumulation += node.get()->getTemperature();
            sleep_for(1s);
            ++count;
            fmt::print("\n");
            count %= 5;
            if (!count)
            {
                fmt::print("the temperature average {}", accumulation / 5.0);
                accumulation = 0;
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what();
        }
        catch (...)
        {
            std::cerr << "Unknown error occured";
        }
    }

    rclcpp::shutdown();
    return 0;
}
