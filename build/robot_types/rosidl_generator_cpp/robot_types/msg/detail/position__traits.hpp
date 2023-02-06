// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_types:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_TYPES__MSG__DETAIL__POSITION__TRAITS_HPP_
#define ROBOT_TYPES__MSG__DETAIL__POSITION__TRAITS_HPP_

#include "robot_types/msg/detail/position__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<robot_types::msg::Position>()
{
  return "robot_types::msg::Position";
}

template<>
inline const char * name<robot_types::msg::Position>()
{
  return "robot_types/msg/Position";
}

template<>
struct has_fixed_size<robot_types::msg::Position>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<robot_types::msg::Position>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<robot_types::msg::Position>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_TYPES__MSG__DETAIL__POSITION__TRAITS_HPP_
