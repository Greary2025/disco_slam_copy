// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "disco_slam/msg/detail/context_info__rosidl_typesupport_introspection_c.h"
#include "disco_slam/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "disco_slam/msg/detail/context_info__functions.h"
#include "disco_slam/msg/detail/context_info__struct.h"


// Include directives for member types
// Member `robot_id`
// Member `robot_id_receive`
#include "rosidl_runtime_c/string_functions.h"
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `scan_cloud`
#include "sensor_msgs/msg/point_cloud2.h"
// Member `scan_cloud`
#include "sensor_msgs/msg/detail/point_cloud2__rosidl_typesupport_introspection_c.h"
// Member `scan_context_bin`
// Member `ring_key`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  disco_slam__msg__ContextInfo__init(message_memory);
}

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_fini_function(void * message_memory)
{
  disco_slam__msg__ContextInfo__fini(message_memory);
}

size_t disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__size_function__ContextInfo__scan_context_bin(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__scan_context_bin(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__scan_context_bin(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__fetch_function__ContextInfo__scan_context_bin(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__scan_context_bin(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__assign_function__ContextInfo__scan_context_bin(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__scan_context_bin(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__resize_function__ContextInfo__scan_context_bin(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__size_function__ContextInfo__ring_key(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__ring_key(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__ring_key(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__fetch_function__ContextInfo__ring_key(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__ring_key(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__assign_function__ContextInfo__ring_key(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__ring_key(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__resize_function__ContextInfo__ring_key(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_member_array[15] = {
  {
    "robot_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, robot_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "robot_id_receive",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, robot_id_receive),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_ring",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, num_ring),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "num_sector",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT64,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, num_sector),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_z",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_z),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_roll",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_roll),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_pitch",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_pitch),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pose_intensity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, pose_intensity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "scan_cloud",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, scan_cloud),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "scan_context_bin",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, scan_context_bin),  // bytes offset in struct
    NULL,  // default value
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__size_function__ContextInfo__scan_context_bin,  // size() function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__scan_context_bin,  // get_const(index) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__scan_context_bin,  // get(index) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__fetch_function__ContextInfo__scan_context_bin,  // fetch(index, &value) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__assign_function__ContextInfo__scan_context_bin,  // assign(index, value) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__resize_function__ContextInfo__scan_context_bin  // resize(index) function pointer
  },
  {
    "ring_key",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(disco_slam__msg__ContextInfo, ring_key),  // bytes offset in struct
    NULL,  // default value
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__size_function__ContextInfo__ring_key,  // size() function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_const_function__ContextInfo__ring_key,  // get_const(index) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__get_function__ContextInfo__ring_key,  // get(index) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__fetch_function__ContextInfo__ring_key,  // fetch(index, &value) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__assign_function__ContextInfo__ring_key,  // assign(index, value) function pointer
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__resize_function__ContextInfo__ring_key  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_members = {
  "disco_slam__msg",  // message namespace
  "ContextInfo",  // message name
  15,  // number of fields
  sizeof(disco_slam__msg__ContextInfo),
  disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_member_array,  // message members
  disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_type_support_handle = {
  0,
  &disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_disco_slam
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, disco_slam, msg, ContextInfo)() {
  disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_member_array[12].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, sensor_msgs, msg, PointCloud2)();
  if (!disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_type_support_handle.typesupport_identifier) {
    disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &disco_slam__msg__ContextInfo__rosidl_typesupport_introspection_c__ContextInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
