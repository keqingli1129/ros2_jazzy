#! /usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
class MyFirstNode(Node):
    def __init__(self):
        super().__init__('my_first_node')
        self.publisher_ = self.create_publisher(String, 'my_topic', 10)
        timer_period = 1.0  # seconds
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = f'Hello, world! {self.i}'
        self.publisher_.publish(msg)
        self.get_logger().info(f'Publishing: "{msg.data}"')
        self.i += 1

def main(args=None):
    rclpy.init(args=args)
    my_first_node = MyFirstNode()
    rclpy.spin(my_first_node)
    my_first_node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()