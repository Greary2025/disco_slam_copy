cmake_minimum_required(VERSION 3.8)
project(disco_slam)

# ==============================================================================
# Configuration: Toggle ROS Version
# Usage: cmake -DBUILD_ROS2=ON .. (for ROS 2) or cmake -DBUILD_ROS2=OFF .. (for ROS 1)
# Default behavior: Autodetect based on environment
# ==============================================================================
if(DEFINED ENV{ROS_VERSION})
  if("$ENV{ROS_VERSION}" STREQUAL "2")
    set(DEFAULT_BUILD_ROS2 ON)
  else()
    set(DEFAULT_BUILD_ROS2 OFF)
  endif()
else()
  # Default to ROS 2 if ROS_VERSION is not set but we are likely in a ROS 2 env
  # or force it for now since the user wants ROS 2
  set(DEFAULT_BUILD_ROS2 ON)
endif()

# Force check if we are in colcon build environment to override any misconfiguration
# if(DEFINED ENV{COLCON_PREFIX_PATH} OR DEFINED ENV{AMENT_PREFIX_PATH})
#   message(STATUS "Detected Colcon/Ament environment, forcing ROS 2 build mode.")
#   set(DEFAULT_BUILD_ROS2 ON)
# endif()
# HARD FORCE ROS 2 for debugging
set(DEFAULT_BUILD_ROS2 ON)

option(BUILD_ROS2 "Build for ROS 2" ${DEFAULT_BUILD_ROS2})

# FORCE ROS 2 MODE REGARDLESS OF OPTION (Temporary Debug)
set(BUILD_ROS2 ON)

if(BUILD_ROS2)
  message(STATUS "Configuring for ROS 2...")
  add_compile_definitions(ROS2_BUILD)
  
  if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
  endif()

  # find dependencies
  find_package(ament_cmake REQUIRED)
  find_package(rclcpp REQUIRED)
  find_package(rclpy REQUIRED)
  find_package(tf2 REQUIRED)
  find_package(tf2_ros REQUIRED)
  find_package(tf2_geometry_msgs REQUIRED)
  find_package(tf2_eigen REQUIRED)
  find_package(cv_bridge REQUIRED)
  find_package(pcl_conversions REQUIRED)
  find_package(std_msgs REQUIRED)
  find_package(sensor_msgs REQUIRED)
  find_package(geometry_msgs REQUIRED)
  find_package(nav_msgs REQUIRED)
  find_package(visualization_msgs REQUIRED)
  find_package(rosidl_default_generators REQUIRED)

else()
  message(STATUS "Configuring for ROS 1...")
  
  set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_BUILD_TYPE "Release")
  set(CMAKE_CXX_FLAGS "-std=c++14")
  set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -pthread")

  find_package(catkin REQUIRED COMPONENTS
    tf
    roscpp
    rospy
    cv_bridge
    pcl_conversions
    std_msgs
    sensor_msgs
    geometry_msgs
    nav_msgs
    message_generation
  )
endif()

# Common Dependencies
find_package(OpenMP REQUIRED)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)
find_package(GTSAM REQUIRED QUIET)
find_package(Eigen3 REQUIRED)
find_package(libnabo REQUIRED)

# Include directories
if(BUILD_ROS2)
    include_directories(
      include
      ${PCL_INCLUDE_DIRS}
      ${OpenCV_INCLUDE_DIRS}
      ${GTSAM_INCLUDE_DIR}
      src/DiSCo-SLAM/third_parties
    )
else()
    include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${PCL_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
        ${GTSAM_INCLUDE_DIR}
        src/DiSCo-SLAM/third_parties
    )
endif()

# Libraries
add_library(fast_max-clique_finder
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/findClique.h
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/graphIO.h
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/findClique.cpp
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/findCliqueHeu.cpp
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/utils.cpp
  src/DiSCo-SLAM/third_parties/fast_max-clique_finder/src/graphIO.cpp
)
target_compile_options(fast_max-clique_finder PRIVATE -w)

add_library(scan_context
  src/DiSCo-SLAM/third_parties/scanContext/scanContext.h
  src/DiSCo-SLAM/third_parties/scanContext/scanContext.cpp
)
target_link_libraries(scan_context PUBLIC Eigen3::Eigen ${PCL_LIBRARIES})

if(BUILD_ROS2)
  # ROS 2 Message Generation
    rosidl_generate_interfaces(${PROJECT_NAME}
      "msg/CloudInfo.msg"
      "msg/ContextInfo.msg"
      DEPENDENCIES geometry_msgs std_msgs nav_msgs sensor_msgs
    )

  # --- Executables for ROS 2 ---
  
  # Image Projection
  add_executable(${PROJECT_NAME}_imageProjection src/imageProjection.cpp)
  target_include_directories(${PROJECT_NAME}_imageProjection PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)
  ament_target_dependencies(${PROJECT_NAME}_imageProjection
    rclcpp cv_bridge pcl_conversions std_msgs sensor_msgs tf2 tf2_ros visualization_msgs tf2_geometry_msgs)
  target_link_libraries(${PROJECT_NAME}_imageProjection ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})
  rosidl_get_typesupport_target(cpp_typesupport_target
    ${PROJECT_NAME} "rosidl_typesupport_cpp")
  target_link_libraries(${PROJECT_NAME}_imageProjection "${cpp_typesupport_target}")

  # Feature Extraction
  add_executable(${PROJECT_NAME}_featureExtraction src/featureExtraction.cpp)
  ament_target_dependencies(${PROJECT_NAME}_featureExtraction
    rclcpp cv_bridge pcl_conversions std_msgs sensor_msgs visualization_msgs tf2 tf2_ros tf2_geometry_msgs)
  target_link_libraries(${PROJECT_NAME}_featureExtraction ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})
  target_link_libraries(${PROJECT_NAME}_featureExtraction "${cpp_typesupport_target}")

  # Map Optimization
  add_executable(${PROJECT_NAME}_mapOptmization src/mapOptmization.cpp)
  target_compile_options(${PROJECT_NAME}_mapOptmization PRIVATE ${OpenMP_CXX_FLAGS})
  ament_target_dependencies(${PROJECT_NAME}_mapOptmization
    rclcpp cv_bridge pcl_conversions std_msgs sensor_msgs nav_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs tf2_eigen visualization_msgs)
  target_link_libraries(${PROJECT_NAME}_mapOptmization ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenMP_CXX_FLAGS} gtsam)
  target_link_libraries(${PROJECT_NAME}_mapOptmization "${cpp_typesupport_target}")

  # IMU Preintegration
  add_executable(${PROJECT_NAME}_imuPreintegration src/imuPreintegration.cpp)
  ament_target_dependencies(${PROJECT_NAME}_imuPreintegration
    rclcpp cv_bridge pcl_conversions std_msgs sensor_msgs nav_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs tf2_eigen visualization_msgs)
  target_link_libraries(${PROJECT_NAME}_imuPreintegration ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam)
  target_link_libraries(${PROJECT_NAME}_imuPreintegration "${cpp_typesupport_target}")

  # Map Fusion
  add_executable(${PROJECT_NAME}_mapFusion src/DiSCo-SLAM/mapFusion.cpp)
  target_compile_options(${PROJECT_NAME}_mapFusion PRIVATE ${OpenMP_CXX_FLAGS})
  ament_target_dependencies(${PROJECT_NAME}_mapFusion
    rclcpp cv_bridge pcl_conversions std_msgs sensor_msgs nav_msgs geometry_msgs visualization_msgs tf2 tf2_ros tf2_geometry_msgs tf2_eigen)
  target_link_libraries(${PROJECT_NAME}_mapFusion
    ${PCL_LIBRARIES} libnabo::nabo gtsam fast_max-clique_finder scan_context ${OpenMP_CXX_FLAGS})
  target_link_libraries(${PROJECT_NAME}_mapFusion "${cpp_typesupport_target}")

  # Path to TUM
  add_executable(${PROJECT_NAME}_path_to_tum src/path_to_tum.cpp)
  ament_target_dependencies(${PROJECT_NAME}_path_to_tum
    rclcpp nav_msgs geometry_msgs tf2 tf2_ros tf2_geometry_msgs)
  target_link_libraries(${PROJECT_NAME}_path_to_tum ${PCL_LIBRARIES})
  target_link_libraries(${PROJECT_NAME}_path_to_tum "${cpp_typesupport_target}")

  # Install rules
  install(TARGETS
    ${PROJECT_NAME}_imageProjection
    ${PROJECT_NAME}_featureExtraction
    ${PROJECT_NAME}_mapOptmization
    ${PROJECT_NAME}_imuPreintegration
    ${PROJECT_NAME}_mapFusion
    ${PROJECT_NAME}_path_to_tum
    fast_max-clique_finder
    scan_context
    DESTINATION lib/${PROJECT_NAME}
  )
  install(DIRECTORY launch/
    DESTINATION share/${PROJECT_NAME}/launch
  )
  install(DIRECTORY config/
    DESTINATION share/${PROJECT_NAME}/config
  )
  install(DIRECTORY src/DiSCo-SLAM/config/
    DESTINATION share/${PROJECT_NAME}/config
  )

  ament_package()

else()
  # --- ROS 1 Logic ---

  add_message_files(
    DIRECTORY msg
    FILES
    cloud_info.msg
    context_info.msg
  )

  generate_messages(
    DEPENDENCIES
    geometry_msgs
    std_msgs
    nav_msgs
    sensor_msgs
  )

  catkin_package(
    INCLUDE_DIRS include
    DEPENDS PCL GTSAM
    CATKIN_DEPENDS 
    std_msgs
    nav_msgs
    geometry_msgs
    sensor_msgs
    message_runtime 
    message_generation
  )

  link_directories(
    include
    ${PCL_LIBRARY_DIRS}
    ${OpenCV_LIBRARY_DIRS}
    ${GTSAM_LIBRARY_DIRS}
  )

  # Range Image Projection
  add_executable(${PROJECT_NAME}_imageProjection src/imageProjection.cpp)
  add_dependencies(${PROJECT_NAME}_imageProjection ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
  target_link_libraries(${PROJECT_NAME}_imageProjection ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

  # Feature Association
  add_executable(${PROJECT_NAME}_featureExtraction src/featureExtraction.cpp)
  add_dependencies(${PROJECT_NAME}_featureExtraction ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
  target_link_libraries(${PROJECT_NAME}_featureExtraction ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

  # Mapping Optimization
  add_executable(${PROJECT_NAME}_mapOptmization src/mapOptmization.cpp)
  add_dependencies(${PROJECT_NAME}_mapOptmization ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
  target_compile_options(${PROJECT_NAME}_mapOptmization PRIVATE ${OpenMP_CXX_FLAGS})
  target_link_libraries(${PROJECT_NAME}_mapOptmization ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenMP_CXX_FLAGS} gtsam)

  # IMU Preintegration
  add_executable(${PROJECT_NAME}_imuPreintegration src/imuPreintegration.cpp)
  target_link_libraries(${PROJECT_NAME}_imuPreintegration ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam)

  # Map Fusion
  add_executable(${PROJECT_NAME}_mapFusion src/DiSCo-SLAM/mapFusion.cpp)
  add_dependencies(${PROJECT_NAME}_mapFusion ${catkin_EXPORTED_TARGETS}  ${PROJECT_NAME}_generate_messages_cpp)
  target_link_libraries(${PROJECT_NAME}_mapFusion ${catkin_LIBRARIES}
      ${PCL_LIBRARIES} libnabo::nabo
      gtsam fast_max-clique_finder scan_context)

  # Path to TUM recorder
  add_executable(${PROJECT_NAME}_path_to_tum src/path_to_tum.cpp)
  add_dependencies(${PROJECT_NAME}_path_to_tum ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
  target_link_libraries(${PROJECT_NAME}_path_to_tum ${catkin_LIBRARIES})

endif()
