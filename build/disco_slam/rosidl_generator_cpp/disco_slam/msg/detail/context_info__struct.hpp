// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_HPP_
#define DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'scan_cloud'
#include "sensor_msgs/msg/detail/point_cloud2__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__disco_slam__msg__ContextInfo __attribute__((deprecated))
#else
# define DEPRECATED__disco_slam__msg__ContextInfo __declspec(deprecated)
#endif

namespace disco_slam
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ContextInfo_
{
  using Type = ContextInfo_<ContainerAllocator>;

  explicit ContextInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    scan_cloud(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_id = "";
      this->robot_id_receive = "";
      this->num_ring = 0ll;
      this->num_sector = 0ll;
      this->pose_x = 0.0f;
      this->pose_y = 0.0f;
      this->pose_z = 0.0f;
      this->pose_roll = 0.0f;
      this->pose_pitch = 0.0f;
      this->pose_yaw = 0.0f;
      this->pose_intensity = 0.0f;
    }
  }

  explicit ContextInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : robot_id(_alloc),
    robot_id_receive(_alloc),
    header(_alloc, _init),
    scan_cloud(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->robot_id = "";
      this->robot_id_receive = "";
      this->num_ring = 0ll;
      this->num_sector = 0ll;
      this->pose_x = 0.0f;
      this->pose_y = 0.0f;
      this->pose_z = 0.0f;
      this->pose_roll = 0.0f;
      this->pose_pitch = 0.0f;
      this->pose_yaw = 0.0f;
      this->pose_intensity = 0.0f;
    }
  }

  // field types and members
  using _robot_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_id_type robot_id;
  using _robot_id_receive_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_id_receive_type robot_id_receive;
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _num_ring_type =
    int64_t;
  _num_ring_type num_ring;
  using _num_sector_type =
    int64_t;
  _num_sector_type num_sector;
  using _pose_x_type =
    float;
  _pose_x_type pose_x;
  using _pose_y_type =
    float;
  _pose_y_type pose_y;
  using _pose_z_type =
    float;
  _pose_z_type pose_z;
  using _pose_roll_type =
    float;
  _pose_roll_type pose_roll;
  using _pose_pitch_type =
    float;
  _pose_pitch_type pose_pitch;
  using _pose_yaw_type =
    float;
  _pose_yaw_type pose_yaw;
  using _pose_intensity_type =
    float;
  _pose_intensity_type pose_intensity;
  using _scan_cloud_type =
    sensor_msgs::msg::PointCloud2_<ContainerAllocator>;
  _scan_cloud_type scan_cloud;
  using _scan_context_bin_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _scan_context_bin_type scan_context_bin;
  using _ring_key_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _ring_key_type ring_key;

  // setters for named parameter idiom
  Type & set__robot_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_id = _arg;
    return *this;
  }
  Type & set__robot_id_receive(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_id_receive = _arg;
    return *this;
  }
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__num_ring(
    const int64_t & _arg)
  {
    this->num_ring = _arg;
    return *this;
  }
  Type & set__num_sector(
    const int64_t & _arg)
  {
    this->num_sector = _arg;
    return *this;
  }
  Type & set__pose_x(
    const float & _arg)
  {
    this->pose_x = _arg;
    return *this;
  }
  Type & set__pose_y(
    const float & _arg)
  {
    this->pose_y = _arg;
    return *this;
  }
  Type & set__pose_z(
    const float & _arg)
  {
    this->pose_z = _arg;
    return *this;
  }
  Type & set__pose_roll(
    const float & _arg)
  {
    this->pose_roll = _arg;
    return *this;
  }
  Type & set__pose_pitch(
    const float & _arg)
  {
    this->pose_pitch = _arg;
    return *this;
  }
  Type & set__pose_yaw(
    const float & _arg)
  {
    this->pose_yaw = _arg;
    return *this;
  }
  Type & set__pose_intensity(
    const float & _arg)
  {
    this->pose_intensity = _arg;
    return *this;
  }
  Type & set__scan_cloud(
    const sensor_msgs::msg::PointCloud2_<ContainerAllocator> & _arg)
  {
    this->scan_cloud = _arg;
    return *this;
  }
  Type & set__scan_context_bin(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->scan_context_bin = _arg;
    return *this;
  }
  Type & set__ring_key(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->ring_key = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    disco_slam::msg::ContextInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const disco_slam::msg::ContextInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      disco_slam::msg::ContextInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      disco_slam::msg::ContextInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__disco_slam__msg__ContextInfo
    std::shared_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__disco_slam__msg__ContextInfo
    std::shared_ptr<disco_slam::msg::ContextInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ContextInfo_ & other) const
  {
    if (this->robot_id != other.robot_id) {
      return false;
    }
    if (this->robot_id_receive != other.robot_id_receive) {
      return false;
    }
    if (this->header != other.header) {
      return false;
    }
    if (this->num_ring != other.num_ring) {
      return false;
    }
    if (this->num_sector != other.num_sector) {
      return false;
    }
    if (this->pose_x != other.pose_x) {
      return false;
    }
    if (this->pose_y != other.pose_y) {
      return false;
    }
    if (this->pose_z != other.pose_z) {
      return false;
    }
    if (this->pose_roll != other.pose_roll) {
      return false;
    }
    if (this->pose_pitch != other.pose_pitch) {
      return false;
    }
    if (this->pose_yaw != other.pose_yaw) {
      return false;
    }
    if (this->pose_intensity != other.pose_intensity) {
      return false;
    }
    if (this->scan_cloud != other.scan_cloud) {
      return false;
    }
    if (this->scan_context_bin != other.scan_context_bin) {
      return false;
    }
    if (this->ring_key != other.ring_key) {
      return false;
    }
    return true;
  }
  bool operator!=(const ContextInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ContextInfo_

// alias to use template instance with default allocator
using ContextInfo =
  disco_slam::msg::ContextInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace disco_slam

#endif  // DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__STRUCT_HPP_
