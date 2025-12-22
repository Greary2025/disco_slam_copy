// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice
#include "disco_slam/msg/detail/context_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `robot_id`
// Member `robot_id_receive`
#include "rosidl_runtime_c/string_functions.h"
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `scan_cloud`
#include "sensor_msgs/msg/detail/point_cloud2__functions.h"
// Member `scan_context_bin`
// Member `ring_key`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
disco_slam__msg__ContextInfo__init(disco_slam__msg__ContextInfo * msg)
{
  if (!msg) {
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__init(&msg->robot_id)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  // robot_id_receive
  if (!rosidl_runtime_c__String__init(&msg->robot_id_receive)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  // num_ring
  // num_sector
  // pose_x
  // pose_y
  // pose_z
  // pose_roll
  // pose_pitch
  // pose_yaw
  // pose_intensity
  // scan_cloud
  if (!sensor_msgs__msg__PointCloud2__init(&msg->scan_cloud)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  // scan_context_bin
  if (!rosidl_runtime_c__float__Sequence__init(&msg->scan_context_bin, 0)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  // ring_key
  if (!rosidl_runtime_c__float__Sequence__init(&msg->ring_key, 0)) {
    disco_slam__msg__ContextInfo__fini(msg);
    return false;
  }
  return true;
}

void
disco_slam__msg__ContextInfo__fini(disco_slam__msg__ContextInfo * msg)
{
  if (!msg) {
    return;
  }
  // robot_id
  rosidl_runtime_c__String__fini(&msg->robot_id);
  // robot_id_receive
  rosidl_runtime_c__String__fini(&msg->robot_id_receive);
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // num_ring
  // num_sector
  // pose_x
  // pose_y
  // pose_z
  // pose_roll
  // pose_pitch
  // pose_yaw
  // pose_intensity
  // scan_cloud
  sensor_msgs__msg__PointCloud2__fini(&msg->scan_cloud);
  // scan_context_bin
  rosidl_runtime_c__float__Sequence__fini(&msg->scan_context_bin);
  // ring_key
  rosidl_runtime_c__float__Sequence__fini(&msg->ring_key);
}

bool
disco_slam__msg__ContextInfo__are_equal(const disco_slam__msg__ContextInfo * lhs, const disco_slam__msg__ContextInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_id), &(rhs->robot_id)))
  {
    return false;
  }
  // robot_id_receive
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->robot_id_receive), &(rhs->robot_id_receive)))
  {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // num_ring
  if (lhs->num_ring != rhs->num_ring) {
    return false;
  }
  // num_sector
  if (lhs->num_sector != rhs->num_sector) {
    return false;
  }
  // pose_x
  if (lhs->pose_x != rhs->pose_x) {
    return false;
  }
  // pose_y
  if (lhs->pose_y != rhs->pose_y) {
    return false;
  }
  // pose_z
  if (lhs->pose_z != rhs->pose_z) {
    return false;
  }
  // pose_roll
  if (lhs->pose_roll != rhs->pose_roll) {
    return false;
  }
  // pose_pitch
  if (lhs->pose_pitch != rhs->pose_pitch) {
    return false;
  }
  // pose_yaw
  if (lhs->pose_yaw != rhs->pose_yaw) {
    return false;
  }
  // pose_intensity
  if (lhs->pose_intensity != rhs->pose_intensity) {
    return false;
  }
  // scan_cloud
  if (!sensor_msgs__msg__PointCloud2__are_equal(
      &(lhs->scan_cloud), &(rhs->scan_cloud)))
  {
    return false;
  }
  // scan_context_bin
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->scan_context_bin), &(rhs->scan_context_bin)))
  {
    return false;
  }
  // ring_key
  if (!rosidl_runtime_c__float__Sequence__are_equal(
      &(lhs->ring_key), &(rhs->ring_key)))
  {
    return false;
  }
  return true;
}

bool
disco_slam__msg__ContextInfo__copy(
  const disco_slam__msg__ContextInfo * input,
  disco_slam__msg__ContextInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // robot_id
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_id), &(output->robot_id)))
  {
    return false;
  }
  // robot_id_receive
  if (!rosidl_runtime_c__String__copy(
      &(input->robot_id_receive), &(output->robot_id_receive)))
  {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // num_ring
  output->num_ring = input->num_ring;
  // num_sector
  output->num_sector = input->num_sector;
  // pose_x
  output->pose_x = input->pose_x;
  // pose_y
  output->pose_y = input->pose_y;
  // pose_z
  output->pose_z = input->pose_z;
  // pose_roll
  output->pose_roll = input->pose_roll;
  // pose_pitch
  output->pose_pitch = input->pose_pitch;
  // pose_yaw
  output->pose_yaw = input->pose_yaw;
  // pose_intensity
  output->pose_intensity = input->pose_intensity;
  // scan_cloud
  if (!sensor_msgs__msg__PointCloud2__copy(
      &(input->scan_cloud), &(output->scan_cloud)))
  {
    return false;
  }
  // scan_context_bin
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->scan_context_bin), &(output->scan_context_bin)))
  {
    return false;
  }
  // ring_key
  if (!rosidl_runtime_c__float__Sequence__copy(
      &(input->ring_key), &(output->ring_key)))
  {
    return false;
  }
  return true;
}

disco_slam__msg__ContextInfo *
disco_slam__msg__ContextInfo__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  disco_slam__msg__ContextInfo * msg = (disco_slam__msg__ContextInfo *)allocator.allocate(sizeof(disco_slam__msg__ContextInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(disco_slam__msg__ContextInfo));
  bool success = disco_slam__msg__ContextInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
disco_slam__msg__ContextInfo__destroy(disco_slam__msg__ContextInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    disco_slam__msg__ContextInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
disco_slam__msg__ContextInfo__Sequence__init(disco_slam__msg__ContextInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  disco_slam__msg__ContextInfo * data = NULL;

  if (size) {
    data = (disco_slam__msg__ContextInfo *)allocator.zero_allocate(size, sizeof(disco_slam__msg__ContextInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = disco_slam__msg__ContextInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        disco_slam__msg__ContextInfo__fini(&data[i - 1]);
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
disco_slam__msg__ContextInfo__Sequence__fini(disco_slam__msg__ContextInfo__Sequence * array)
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
      disco_slam__msg__ContextInfo__fini(&array->data[i]);
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

disco_slam__msg__ContextInfo__Sequence *
disco_slam__msg__ContextInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  disco_slam__msg__ContextInfo__Sequence * array = (disco_slam__msg__ContextInfo__Sequence *)allocator.allocate(sizeof(disco_slam__msg__ContextInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = disco_slam__msg__ContextInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
disco_slam__msg__ContextInfo__Sequence__destroy(disco_slam__msg__ContextInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    disco_slam__msg__ContextInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
disco_slam__msg__ContextInfo__Sequence__are_equal(const disco_slam__msg__ContextInfo__Sequence * lhs, const disco_slam__msg__ContextInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!disco_slam__msg__ContextInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
disco_slam__msg__ContextInfo__Sequence__copy(
  const disco_slam__msg__ContextInfo__Sequence * input,
  disco_slam__msg__ContextInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(disco_slam__msg__ContextInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    disco_slam__msg__ContextInfo * data =
      (disco_slam__msg__ContextInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!disco_slam__msg__ContextInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          disco_slam__msg__ContextInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!disco_slam__msg__ContextInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
