// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from disco_slam:msg/ContextInfo.idl
// generated code does not contain a copyright notice

#ifndef DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__TRAITS_HPP_
#define DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "disco_slam/msg/detail/context_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'scan_cloud'
#include "sensor_msgs/msg/detail/point_cloud2__traits.hpp"

namespace disco_slam
{

namespace msg
{

inline void to_flow_style_yaml(
  const ContextInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: robot_id
  {
    out << "robot_id: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id, out);
    out << ", ";
  }

  // member: robot_id_receive
  {
    out << "robot_id_receive: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id_receive, out);
    out << ", ";
  }

  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: num_ring
  {
    out << "num_ring: ";
    rosidl_generator_traits::value_to_yaml(msg.num_ring, out);
    out << ", ";
  }

  // member: num_sector
  {
    out << "num_sector: ";
    rosidl_generator_traits::value_to_yaml(msg.num_sector, out);
    out << ", ";
  }

  // member: pose_x
  {
    out << "pose_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_x, out);
    out << ", ";
  }

  // member: pose_y
  {
    out << "pose_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_y, out);
    out << ", ";
  }

  // member: pose_z
  {
    out << "pose_z: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_z, out);
    out << ", ";
  }

  // member: pose_roll
  {
    out << "pose_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_roll, out);
    out << ", ";
  }

  // member: pose_pitch
  {
    out << "pose_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_pitch, out);
    out << ", ";
  }

  // member: pose_yaw
  {
    out << "pose_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_yaw, out);
    out << ", ";
  }

  // member: pose_intensity
  {
    out << "pose_intensity: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_intensity, out);
    out << ", ";
  }

  // member: scan_cloud
  {
    out << "scan_cloud: ";
    to_flow_style_yaml(msg.scan_cloud, out);
    out << ", ";
  }

  // member: scan_context_bin
  {
    if (msg.scan_context_bin.size() == 0) {
      out << "scan_context_bin: []";
    } else {
      out << "scan_context_bin: [";
      size_t pending_items = msg.scan_context_bin.size();
      for (auto item : msg.scan_context_bin) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: ring_key
  {
    if (msg.ring_key.size() == 0) {
      out << "ring_key: []";
    } else {
      out << "ring_key: [";
      size_t pending_items = msg.ring_key.size();
      for (auto item : msg.ring_key) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ContextInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: robot_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_id: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id, out);
    out << "\n";
  }

  // member: robot_id_receive
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_id_receive: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id_receive, out);
    out << "\n";
  }

  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: num_ring
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_ring: ";
    rosidl_generator_traits::value_to_yaml(msg.num_ring, out);
    out << "\n";
  }

  // member: num_sector
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "num_sector: ";
    rosidl_generator_traits::value_to_yaml(msg.num_sector, out);
    out << "\n";
  }

  // member: pose_x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_x: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_x, out);
    out << "\n";
  }

  // member: pose_y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_y: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_y, out);
    out << "\n";
  }

  // member: pose_z
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_z: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_z, out);
    out << "\n";
  }

  // member: pose_roll
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_roll: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_roll, out);
    out << "\n";
  }

  // member: pose_pitch
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_pitch: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_pitch, out);
    out << "\n";
  }

  // member: pose_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_yaw, out);
    out << "\n";
  }

  // member: pose_intensity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "pose_intensity: ";
    rosidl_generator_traits::value_to_yaml(msg.pose_intensity, out);
    out << "\n";
  }

  // member: scan_cloud
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "scan_cloud:\n";
    to_block_style_yaml(msg.scan_cloud, out, indentation + 2);
  }

  // member: scan_context_bin
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.scan_context_bin.size() == 0) {
      out << "scan_context_bin: []\n";
    } else {
      out << "scan_context_bin:\n";
      for (auto item : msg.scan_context_bin) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: ring_key
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.ring_key.size() == 0) {
      out << "ring_key: []\n";
    } else {
      out << "ring_key:\n";
      for (auto item : msg.ring_key) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ContextInfo & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace disco_slam

namespace rosidl_generator_traits
{

[[deprecated("use disco_slam::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const disco_slam::msg::ContextInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  disco_slam::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use disco_slam::msg::to_yaml() instead")]]
inline std::string to_yaml(const disco_slam::msg::ContextInfo & msg)
{
  return disco_slam::msg::to_yaml(msg);
}

template<>
inline const char * data_type<disco_slam::msg::ContextInfo>()
{
  return "disco_slam::msg::ContextInfo";
}

template<>
inline const char * name<disco_slam::msg::ContextInfo>()
{
  return "disco_slam/msg/ContextInfo";
}

template<>
struct has_fixed_size<disco_slam::msg::ContextInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<disco_slam::msg::ContextInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<disco_slam::msg::ContextInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DISCO_SLAM__MSG__DETAIL__CONTEXT_INFO__TRAITS_HPP_
