cmake_minimum_required(VERSION 3.5)
project(pid_controller)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(robot_types REQUIRED)

add_executable(pid_controller src/pid_controller_node.cpp
                              src/pid_controller.cpp
                              src/pid_params.cpp
                              src/scion_pid_controller.cpp)

ament_target_dependencies(pid_controller rclcpp robot_types)

target_include_directories(pid_controller PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

install(TARGETS
  pid_controller
  DESTINATION lib/${PROJECT_NAME})

ament_package()
