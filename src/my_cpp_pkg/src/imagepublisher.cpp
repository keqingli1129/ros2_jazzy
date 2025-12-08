#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.hpp>

class ImagePublisher : public rclcpp::Node {
public:
    ImagePublisher()
    : Node("image_publisher"), cap(0) {
        publisher_ = this->create_publisher<sensor_msgs::msg::Image>("image_topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&ImagePublisher::timer_callback, this)
        );
    }

private:
    void timer_callback() {
        cv::Mat frame;
        if (cap.read(frame)) {
            std_msgs::msg::Header header;
            header.stamp = this->now();
            header.frame_id = "camera";
            sensor_msgs::msg::Image::SharedPtr msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();
            publisher_->publish(*msg);
            RCLCPP_INFO(this->get_logger(), "Publishing image");
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to capture image from camera");
        }
    }

    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    cv::VideoCapture cap;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImagePublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
