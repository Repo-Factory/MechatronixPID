// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_types:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_TYPES__MSG__DETAIL__POSITION__BUILDER_HPP_
#define ROBOT_TYPES__MSG__DETAIL__POSITION__BUILDER_HPP_

#include "robot_types/msg/detail/position__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace robot_types
{

namespace msg
{

namespace builder
{

class Init_Position_position_vector
{
public:
  Init_Position_position_vector()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_types::msg::Position position_vector(::robot_types::msg::Position::_position_vector_type arg)
  {
    msg_.position_vector = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_types::msg::Position msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_types::msg::Position>()
{
  return robot_types::msg::builder::Init_Position_position_vector();
}

}  // namespace robot_types

#endif  // ROBOT_TYPES__MSG__DETAIL__POSITION__BUILDER_HPP_
