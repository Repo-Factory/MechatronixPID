// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from robot_types:msg/Position.idl
// generated code does not contain a copyright notice
#include "robot_types/msg/detail/position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `position_vector`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
robot_types__msg__Position__init(robot_types__msg__Position * msg)
{
  if (!msg) {
    return false;
  }
  // position_vector
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->position_vector, 0)) {
    robot_types__msg__Position__fini(msg);
    return false;
  }
  return true;
}

void
robot_types__msg__Position__fini(robot_types__msg__Position * msg)
{
  if (!msg) {
    return;
  }
  // position_vector
  rosidl_runtime_c__int32__Sequence__fini(&msg->position_vector);
}

bool
robot_types__msg__Position__are_equal(const robot_types__msg__Position * lhs, const robot_types__msg__Position * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // position_vector
  if (!rosidl_runtime_c__int32__Sequence__are_equal(
      &(lhs->position_vector), &(rhs->position_vector)))
  {
    return false;
  }
  return true;
}

bool
robot_types__msg__Position__copy(
  const robot_types__msg__Position * input,
  robot_types__msg__Position * output)
{
  if (!input || !output) {
    return false;
  }
  // position_vector
  if (!rosidl_runtime_c__int32__Sequence__copy(
      &(input->position_vector), &(output->position_vector)))
  {
    return false;
  }
  return true;
}

robot_types__msg__Position *
robot_types__msg__Position__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_types__msg__Position * msg = (robot_types__msg__Position *)allocator.allocate(sizeof(robot_types__msg__Position), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(robot_types__msg__Position));
  bool success = robot_types__msg__Position__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
robot_types__msg__Position__destroy(robot_types__msg__Position * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    robot_types__msg__Position__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
robot_types__msg__Position__Sequence__init(robot_types__msg__Position__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_types__msg__Position * data = NULL;

  if (size) {
    data = (robot_types__msg__Position *)allocator.zero_allocate(size, sizeof(robot_types__msg__Position), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = robot_types__msg__Position__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        robot_types__msg__Position__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
robot_types__msg__Position__Sequence__fini(robot_types__msg__Position__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      robot_types__msg__Position__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

robot_types__msg__Position__Sequence *
robot_types__msg__Position__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  robot_types__msg__Position__Sequence * array = (robot_types__msg__Position__Sequence *)allocator.allocate(sizeof(robot_types__msg__Position__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = robot_types__msg__Position__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
robot_types__msg__Position__Sequence__destroy(robot_types__msg__Position__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    robot_types__msg__Position__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
robot_types__msg__Position__Sequence__are_equal(const robot_types__msg__Position__Sequence * lhs, const robot_types__msg__Position__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!robot_types__msg__Position__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
robot_types__msg__Position__Sequence__copy(
  const robot_types__msg__Position__Sequence * input,
  robot_types__msg__Position__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(robot_types__msg__Position);
    robot_types__msg__Position * data =
      (robot_types__msg__Position *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!robot_types__msg__Position__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          robot_types__msg__Position__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!robot_types__msg__Position__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
