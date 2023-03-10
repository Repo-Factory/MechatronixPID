// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from robot_types:msg/Position.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_H_
#define ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'position_vector'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/Position in the package robot_types.
typedef struct robot_types__msg__Position
{
  rosidl_runtime_c__double__Sequence position_vector;
} robot_types__msg__Position;

// Struct for a sequence of robot_types__msg__Position.
typedef struct robot_types__msg__Position__Sequence
{
  robot_types__msg__Position * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} robot_types__msg__Position__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROBOT_TYPES__MSG__DETAIL__POSITION__STRUCT_H_
