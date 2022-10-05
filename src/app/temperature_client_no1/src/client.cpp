#include "client_base.h"
#include "temperature_client_no1.h"
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
