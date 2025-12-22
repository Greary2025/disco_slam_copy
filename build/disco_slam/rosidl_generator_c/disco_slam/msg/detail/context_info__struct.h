// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_H_
#define DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'robot_id'
// Member 'robot_id_receive'
#include "rosidl_runtime_c/string.h"
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'scan_cloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.h"
// Member 'scan_context_bin'
// Member 'ring_key'
#include "rosidl_runtime_c/primitives_sequence.h"

/// Struct defined in msg/ContextInfo in the package disco_slam.
/**
  * Robot Name
 */
typedef struct disco_slam__msg__ContextInfo
{
  rosidl_runtime_c__String robot_id;
  /// Robot Name Receive
  rosidl_runtime_c__String robot_id_receive;
  /// Cloud Info
  std_msgs__msg__Header header;
  /// Scan context dimension
  int64_t num_ring;
  int64_t num_sector;
  /// Present robot pose
  float pose_x;
  float pose_y;
  float pose_z;
  float pose_roll;
  float pose_pitch;
  float pose_yaw;
  float pose_intensity;
  /// Point cloud messages
  /// extracted feature cloud
  sensor_msgs__msg__PointCloud2 scan_cloud;
  /// Scan context info
  rosidl_runtime_c__float__Sequence scan_context_bin;
  rosidl_runtime_c__float__Sequence ring_key;
} disco_slam__msg__ContextInfo;

// Struct for a sequence of disco_slam__msg__ContextInfo.
typedef struct disco_slam__msg__ContextInfo__Sequence
{
  disco_slam__msg__ContextInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} disco_slam__msg__ContextInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_H_
