set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

cmake_minimum_required(VERSION 3.5)
project(disco_slam)

set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_CXX_FLAGS "-std=c++14")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -Wall -g -pthread")

find_package(catkin REQUIRED COMPONENTS
  tf
  roscpp
  rospy
  cv_bridge
  # pcl library
  pcl_conversions
  pcl_ros
  # msgs
  std_msgs
  sensor_msgs
  geometry_msgs
  nav_msgs
  message_generation
)

find_package(OpenMP REQUIRED)
find_package(PCL REQUIRED QUIET)
find_package(OpenCV REQUIRED QUIET)
find_package(Ceres REQUIRED)
find_package(GTSAM REQUIRED QUIET)
find_package(Eigen3 REQUIRED)
find_package(libnabo REQUIRED)

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
  pcl_ros
  message_runtime 
  message_generation
)

# include directories
include_directories(
	include
	${catkin_INCLUDE_DIRS}
	${PCL_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
	${GTSAM_INCLUDE_DIR}
	src/DiSCo-SLAM/third_parties
)

# link directories
link_directories(
	include
	${PCL_LIBRARY_DIRS}
    ${OpenCV_LIBRARY_DIRS}
    ${GTSAM_LIBRARY_DIRS}
)

###########
## Build ##
###########

#for fushion
# Maximum Clique Solver
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


# Range Image Projection
add_executable(${PROJECT_NAME}_imageProjection src/imageProjection.cpp)
add_dependencies(${PROJECT_NAME}_imageProjection ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(${PROJECT_NAME}_imageProjection ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

# Feature Association
add_executable(${PROJECT_NAME}_featureExtraction src/featureExtraction.cpp)
add_dependencies(${PROJECT_NAME}_featureExtraction ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(${PROJECT_NAME}_featureExtraction ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

# SR-LIO frontend for dynamic-point filtering
add_executable(${PROJECT_NAME}_srLioFrontend
	src/dynamic_lio/sr_lio/src/lioOptimization.cpp
	src/dynamic_lio/sr_lio/src/optimize.cpp
	src/dynamic_lio/sr_lio/src/cloudMap.cpp
	src/dynamic_lio/sr_lio/src/cloudProcessing.cpp
	src/dynamic_lio/sr_lio/src/state.cpp
	src/dynamic_lio/sr_lio/src/eskfEstimator.cpp
	src/dynamic_lio/sr_lio/src/utility.cpp
	src/dynamic_lio/sr_lio/src/parameters.cpp)
set_target_properties(${PROJECT_NAME}_srLioFrontend PROPERTIES CXX_STANDARD 17 CXX_STANDARD_REQUIRED YES)
target_include_directories(${PROJECT_NAME}_srLioFrontend BEFORE PRIVATE
	src/dynamic_lio/sr_lio/include
	src/dynamic_lio/sr_lio/thirdLibrary/tessil-src/include)
target_link_libraries(${PROJECT_NAME}_srLioFrontend ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${CERES_LIBRARIES} ${OpenCV_LIBRARIES})

# Bridge SR-LIO dynamic outputs to disco cloud_info
add_executable(${PROJECT_NAME}_srLioDynamicBridge src/srLioDynamicBridge.cpp)
add_dependencies(${PROJECT_NAME}_srLioDynamicBridge ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(${PROJECT_NAME}_srLioDynamicBridge ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES})

# Mapping Optimization
add_executable(${PROJECT_NAME}_mapOptmization src/mapOptmization.cpp)
add_dependencies(${PROJECT_NAME}_mapOptmization ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_compile_options(${PROJECT_NAME}_mapOptmization PRIVATE ${OpenMP_CXX_FLAGS})
target_link_libraries(${PROJECT_NAME}_mapOptmization ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} ${OpenMP_CXX_FLAGS} gtsam)

# IMU Preintegration
add_executable(${PROJECT_NAME}_imuPreintegration src/imuPreintegration.cpp)
target_link_libraries(${PROJECT_NAME}_imuPreintegration ${catkin_LIBRARIES} ${PCL_LIBRARIES} ${OpenCV_LIBRARIES} gtsam)

# Map Fushion
add_executable(${PROJECT_NAME}_mapFusion src/DiSCo-SLAM/mapFusion.cpp)
add_dependencies(${PROJECT_NAME}_mapFusion ${catkin_EXPORTED_TARGETS}  ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(${PROJECT_NAME}_mapFusion ${catkin_LIBRARIES}
		${PCL_LIBRARIES} libnabo::nabo
		gtsam fast_max-clique_finder scan_context)

#catkin_install_python(PROGRAMS scripts/listener.py
#	DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

# Path to TUM recorder
add_executable(${PROJECT_NAME}_path_to_tum src/path_to_tum.cpp)
add_dependencies(${PROJECT_NAME}_path_to_tum ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_generate_messages_cpp)
target_link_libraries(${PROJECT_NAME}_path_to_tum ${catkin_LIBRARIES})
