// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_types:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_HPP_
#define ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__robot_types__msg__Position __attribute__((deprecated))
#else
# define DEPRECATED__robot_types__msg__Position __declspec(deprecated)
#endif

namespace robot_types
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Position_
{
  using Type = Position_<ContainerAllocator>;

  explicit Position_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit Position_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _position_vector_type =
    std::vector<double, typename ContainerAllocator::template rebind<double>::other>;
  _position_vector_type position_vector;

  // setters for named parameter idiom
  Type & set__position_vector(
    const std::vector<double, typename ContainerAllocator::template rebind<double>::other> & _arg)
  {
    this->position_vector = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_types::msg::Position_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_types::msg::Position_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_types::msg::Position_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_types::msg::Position_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_types::msg::Position_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_types::msg::Position_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_types::msg::Position_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_types::msg::Position_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_types::msg::Position_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_types::msg::Position_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_types__msg__Position
    std::shared_ptr<robot_types::msg::Position_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_types__msg__Position
    std::shared_ptr<robot_types::msg::Position_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Position_ & other) const
  {
    if (this->position_vector != other.position_vector) {
      return false;
    }
    return true;
  }
  bool operator!=(const Position_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Position_

// alias to use template instance with default allocator
using Position =
  robot_types::msg::Position_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_types

#endif  // ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_HPP_
