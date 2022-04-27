#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
using std::placeholders::_1;

class testKeyBoard : public rclcpp::Node
{
  public:
    testKeyBoard()
    : Node("minimal_subscriber")
    {
      subscription_speed = this->create_subscription<std_msgs::msg::Float32>(
      "SPEED", 10, std::bind(&testKeyBoard::topic_callback_speed, this, _1));
      subscription_angle = this->create_subscription<std_msgs::msg::Float32>(
      "ANGLE", 10, std::bind(&testKeyBoard::topic_callback_angle, this, _1));
    }

  private:
    void topic_callback_speed(const std_msgs::msg::Float32::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Speed: '%f'", msg->data);
    }
    void topic_callback_angle(const std_msgs::msg::Float32::SharedPtr msg) const
    {
      RCLCPP_INFO(this->get_logger(), "Angle: '%f'", msg->data);
    }
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_speed;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_angle;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<testKeyBoard>());
  rclcpp::shutdown();
  return 0;
}