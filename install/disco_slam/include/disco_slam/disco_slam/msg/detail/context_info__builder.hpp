// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__BUILDER_HPP_
#define DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "disco_slam/msg/detail/context_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace disco_slam
{

namespace msg
{

namespace builder
{

class Init_ContextInfo_ring_key
{
public:
  explicit Init_ContextInfo_ring_key(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  ::disco_slam::msg::ContextInfo ring_key(::disco_slam::msg::ContextInfo::_ring_key_type arg)
  {
    msg_.ring_key = std::move(arg);
    return std::move(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_scan_context_bin
{
public:
  explicit Init_ContextInfo_scan_context_bin(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_ring_key scan_context_bin(::disco_slam::msg::ContextInfo::_scan_context_bin_type arg)
  {
    msg_.scan_context_bin = std::move(arg);
    return Init_ContextInfo_ring_key(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_scan_cloud
{
public:
  explicit Init_ContextInfo_scan_cloud(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_scan_context_bin scan_cloud(::disco_slam::msg::ContextInfo::_scan_cloud_type arg)
  {
    msg_.scan_cloud = std::move(arg);
    return Init_ContextInfo_scan_context_bin(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_intensity
{
public:
  explicit Init_ContextInfo_pose_intensity(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_scan_cloud pose_intensity(::disco_slam::msg::ContextInfo::_pose_intensity_type arg)
  {
    msg_.pose_intensity = std::move(arg);
    return Init_ContextInfo_scan_cloud(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_yaw
{
public:
  explicit Init_ContextInfo_pose_yaw(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_intensity pose_yaw(::disco_slam::msg::ContextInfo::_pose_yaw_type arg)
  {
    msg_.pose_yaw = std::move(arg);
    return Init_ContextInfo_pose_intensity(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_pitch
{
public:
  explicit Init_ContextInfo_pose_pitch(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_yaw pose_pitch(::disco_slam::msg::ContextInfo::_pose_pitch_type arg)
  {
    msg_.pose_pitch = std::move(arg);
    return Init_ContextInfo_pose_yaw(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_roll
{
public:
  explicit Init_ContextInfo_pose_roll(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_pitch pose_roll(::disco_slam::msg::ContextInfo::_pose_roll_type arg)
  {
    msg_.pose_roll = std::move(arg);
    return Init_ContextInfo_pose_pitch(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_z
{
public:
  explicit Init_ContextInfo_pose_z(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_roll pose_z(::disco_slam::msg::ContextInfo::_pose_z_type arg)
  {
    msg_.pose_z = std::move(arg);
    return Init_ContextInfo_pose_roll(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_y
{
public:
  explicit Init_ContextInfo_pose_y(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_z pose_y(::disco_slam::msg::ContextInfo::_pose_y_type arg)
  {
    msg_.pose_y = std::move(arg);
    return Init_ContextInfo_pose_z(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_pose_x
{
public:
  explicit Init_ContextInfo_pose_x(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_y pose_x(::disco_slam::msg::ContextInfo::_pose_x_type arg)
  {
    msg_.pose_x = std::move(arg);
    return Init_ContextInfo_pose_y(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_num_sector
{
public:
  explicit Init_ContextInfo_num_sector(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_pose_x num_sector(::disco_slam::msg::ContextInfo::_num_sector_type arg)
  {
    msg_.num_sector = std::move(arg);
    return Init_ContextInfo_pose_x(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_num_ring
{
public:
  explicit Init_ContextInfo_num_ring(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_num_sector num_ring(::disco_slam::msg::ContextInfo::_num_ring_type arg)
  {
    msg_.num_ring = std::move(arg);
    return Init_ContextInfo_num_sector(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_header
{
public:
  explicit Init_ContextInfo_header(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_num_ring header(::disco_slam::msg::ContextInfo::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_ContextInfo_num_ring(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_robot_id_receive
{
public:
  explicit Init_ContextInfo_robot_id_receive(::disco_slam::msg::ContextInfo & msg)
  : msg_(msg)
  {}
  Init_ContextInfo_header robot_id_receive(::disco_slam::msg::ContextInfo::_robot_id_receive_type arg)
  {
    msg_.robot_id_receive = std::move(arg);
    return Init_ContextInfo_header(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

class Init_ContextInfo_robot_id
{
public:
  Init_ContextInfo_robot_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ContextInfo_robot_id_receive robot_id(::disco_slam::msg::ContextInfo::_robot_id_type arg)
  {
    msg_.robot_id = std::move(arg);
    return Init_ContextInfo_robot_id_receive(msg_);
  }

private:
  ::disco_slam::msg::ContextInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::disco_slam::msg::ContextInfo>()
{
  return disco_slam::msg::builder::Init_ContextInfo_robot_id();
}

}  // namespace disco_slam

#endif  // DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__BUILDER_HPP_
