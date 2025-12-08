cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(cv_bridge REQUIRED)
find_package(OpenCV REQUIRED)

add_executable(cpp_node src/my_first_node.cpp)
ament_target_dependencies(cpp_node rclcpp)
add_executable(image_publisher src/imagepublisher.cpp)
ament_target_dependencies(image_publisher rclcpp sensor_msgs cv_bridge OpenCV)
install(TARGETS
  cpp_node
  image_publisher                                                                                                                     
  DESTINATION lib/${PROJECT_NAME}
)
ament_package()
