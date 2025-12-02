#include "rclcpp/rclcpp.hpp"

class MyFirstNode : public rclcpp::Node
{
    public:
        MyFirstNode() : Node("my_first_node"), counter_(0)
        {
            timer_ = this->create_wall_timer(
                std::chrono::seconds(1),
                std::bind(&MyFirstNode::timer_callback, this)
            );
            RCLCPP_INFO(this->get_logger(), "MyFirstNode has been started.");
        }
    private:
        int counter_;
        rclcpp::TimerBase::SharedPtr timer_;
        void timer_callback()
        {
            RCLCPP_INFO(this->get_logger(), "Timer callback triggered %d", counter_++);
        }
};  
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    // auto node = rclcpp::Node::make_shared("my_first_node");
    // RCLCPP_INFO(node->get_logger(), "Hello, ROS2 World!");
    // rclcpp::spin(node);
    // auto node = rclcpp::Node::make_shared("my_first_node");
    auto node = std::make_shared<MyFirstNode>();
    // RCLCPP_INFO(node->get_logger(), "Hello, ROS2 World!");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}