#pragma once
#ifndef _UTILITY_LIDAR_ODOMETRY_H_
#define _UTILITY_LIDAR_ODOMETRY_H_

#include <rclcpp/rclcpp.hpp>

#include <std_msgs/msg/header.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <sensor_msgs/msg/imu.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <sensor_msgs/msg/nav_sat_fix.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <nav_msgs/msg/path.hpp>
#include <visualization_msgs/msg/marker.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/search/impl/search.hpp>
#include <pcl/range_image/range_image.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/common/common.h>
#include <pcl/common/transforms.h>
#include <pcl/registration/icp.h>
#include <pcl/io/pcd_io.h>
#include <pcl/filters/filter.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/crop_box.h> 
#include <pcl_conversions/pcl_conversions.h>

#include <tf2/LinearMath/Quaternion.h>
#include <tf2/LinearMath/Matrix3x3.h>
#include <tf2_ros/buffer.h>
#include <tf2_ros/transform_listener.h>
#include <tf2_ros/transform_broadcaster.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
 
#include <vector>
#include <cmath>
#include <algorithm>
#include <queue>
#include <deque>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cfloat>
#include <iterator>
#include <sstream>
#include <string>
#include <limits>
#include <iomanip>
#include <array>
#include <thread>
#include <mutex>

using namespace std;

// ROS 1 to ROS 2 Type Aliases
namespace std_msgs {
    using Header = msg::Header;
    using Float64MultiArray = msg::Float64MultiArray;
}
namespace sensor_msgs {
    using Imu = msg::Imu;
    using PointCloud2 = msg::PointCloud2;
    using NavSatFix = msg::NavSatFix;
}
namespace nav_msgs {
    using Odometry = msg::Odometry;
    using Path = msg::Path;
}
namespace visualization_msgs {
    using Marker = msg::Marker;
    using MarkerArray = msg::MarkerArray;
}

template<typename T>
double ROS_TIME(const T& msg) {
    return rclcpp::Time(msg->header.stamp).seconds();
}

template<typename T>
sensor_msgs::msg::PointCloud2 publishCloud(const rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr& thisPub, 
                                           const typename pcl::PointCloud<T>::Ptr& thisCloud, 
                                           rclcpp::Time thisStamp, 
                                           std::string thisFrame)
{
    sensor_msgs::msg::PointCloud2 tempCloud;
    pcl::toROSMsg(*thisCloud, tempCloud);
    tempCloud.header.stamp = thisStamp;
    tempCloud.header.frame_id = thisFrame;
    if (thisPub->get_subscription_count() != 0)
        thisPub->publish(tempCloud);
    return tempCloud;
}

template<typename T>
sensor_msgs::msg::PointCloud2 publishCloud(rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr* thisPub, 
                                           const typename pcl::PointCloud<T>::Ptr& thisCloud, 
                                           rclcpp::Time thisStamp, 
                                           std::string thisFrame)
{
    sensor_msgs::msg::PointCloud2 tempCloud;
    pcl::toROSMsg(*thisCloud, tempCloud);
    tempCloud.header.stamp = thisStamp;
    tempCloud.header.frame_id = thisFrame;
    if ((*thisPub)->get_subscription_count() != 0)
        (*thisPub)->publish(tempCloud);
    return tempCloud;
}

void imuRPY2rosRPY(sensor_msgs::msg::Imu* thisImuMsg, double* roll, double* pitch, double* yaw)
{
    tf2::Quaternion orientation;
    tf2::fromMsg(thisImuMsg->orientation, orientation);
    tf2::Matrix3x3(orientation).getRPY(*roll, *pitch, *yaw);
}

void imuAngular2rosAngular(sensor_msgs::msg::Imu* thisImuMsg, double* angular_x, double* angular_y, double* angular_z)
{
    *angular_x = thisImuMsg->angular_velocity.x;
    *angular_y = thisImuMsg->angular_velocity.y;
    *angular_z = thisImuMsg->angular_velocity.z;
}

typedef pcl::PointXYZI PointType;

template<typename T>
float pointDistance(T p1, T p2)
{
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y) + (p1.z-p2.z)*(p1.z-p2.z));
}

enum class SensorType { VELODYNE, OUSTER };

class ParamServer : public rclcpp::Node
{
public:
    std::string robot_id;

    //Topics
    string pointCloudTopic;
    string imuTopic;
    string odomTopic;
    string gpsTopic;

    //Frames
    string lidarFrame;
    string baselinkFrame;
    string odometryFrame;
    string mapFrame;

    // GPS Settings
    bool useImuHeadingInitialization;
    bool useGpsElevation;
    float gpsCovThreshold;
    float poseCovThreshold;

    // Save pcd
    bool savePCD;
    string savePCDDirectory;

    // Lidar Sensor Configuration
    SensorType sensor;
    int N_SCAN;
    int Horizon_SCAN;
    int downsampleRate;
    float lidarMinRange;
    float lidarMaxRange;

    // IMU
    float imuAccNoise;
    float imuGyrNoise;
    float imuAccBiasN;
    float imuGyrBiasN;
    float imuGravity;
    float imuRPYWeight;
    vector<double> extRotV;
    vector<double> extRPYV;
    vector<double> extTransV;
    Eigen::Matrix3d extRot;
    Eigen::Matrix3d extRPY;
    Eigen::Vector3d extTrans;
    Eigen::Quaterniond extQRPY;

    // LOAM
    float edgeThreshold;
    float surfThreshold;
    int edgeFeatureMinValidNum;
    int surfFeatureMinValidNum;

    // voxel filter paprams
    float odometrySurfLeafSize;
    float mappingCornerLeafSize;
    float mappingSurfLeafSize ;

    float z_tollerance; 
    float rotation_tollerance;

    // CPU Params
    int numberOfCores;
    double mappingProcessInterval;

    // Surrounding map
    float surroundingkeyframeAddingDistThreshold; 
    float surroundingkeyframeAddingAngleThreshold; 
    float surroundingKeyframeDensity;
    float surroundingKeyframeSearchRadius;
    
    // Loop closure
    bool  loopClosureEnableFlag;
    float loopClosureFrequency;
    int   surroundingKeyframeSize;
    float historyKeyframeSearchRadius;
    float historyKeyframeSearchTimeDiff;
    int   historyKeyframeSearchNum;
    float historyKeyframeFitnessScore;

    // global map visualization radius
    float globalMapVisualizationSearchRadius;
    float globalMapVisualizationPoseDensity;
    float globalMapVisualizationLeafSize;

    int number_print;

    // Lidar vertical channel handling when 'ring' field is absent
    bool hasRing;
    float angBottom; // degrees
    float angResY;   // degrees per channel

    ParamServer(std::string node_name, const rclcpp::NodeOptions & options = rclcpp::NodeOptions())
        : Node(node_name, options)
    {
        // ROS 2 Parameter Declaration and Retrieval
        
        number_print = this->declare_parameter<int>("no", 100);
        robot_id = this->declare_parameter<std::string>("robot_id", "jackal0");

        pointCloudTopic = this->declare_parameter<std::string>("disco_slam/pointCloudTopic", "points_raw");
        imuTopic = this->declare_parameter<std::string>("disco_slam/imuTopic", "imu_correct");
        odomTopic = this->declare_parameter<std::string>("disco_slam/odomTopic", "odometry/imu");
        gpsTopic = this->declare_parameter<std::string>("disco_slam/gpsTopic", "odometry/gps");

        lidarFrame = this->declare_parameter<std::string>("disco_slam/lidarFrame", "base_link");
        baselinkFrame = this->declare_parameter<std::string>("disco_slam/baselinkFrame", "base_link");
        odometryFrame = this->declare_parameter<std::string>("disco_slam/odometryFrame", "odom");
        mapFrame = this->declare_parameter<std::string>("disco_slam/mapFrame", "map");

        useImuHeadingInitialization = this->declare_parameter<bool>("disco_slam/useImuHeadingInitialization", false);
        useGpsElevation = this->declare_parameter<bool>("disco_slam/useGpsElevation", false);
        gpsCovThreshold = this->declare_parameter<float>("disco_slam/gpsCovThreshold", 2.0);
        poseCovThreshold = this->declare_parameter<float>("disco_slam/poseCovThreshold", 25.0);

        savePCD = this->declare_parameter<bool>("disco_slam/savePCD", false);
        savePCDDirectory = this->declare_parameter<std::string>("disco_slam/savePCDDirectory", "/Downloads/LOAM/");

        std::string sensorStr = this->declare_parameter<std::string>("disco_slam/sensor", "");
        if (sensorStr == "velodyne")
        {
            sensor = SensorType::VELODYNE;
        }
        else if (sensorStr == "ouster")
        {
            sensor = SensorType::OUSTER;
        }
        else
        {
            if (sensorStr != "") {
                RCLCPP_ERROR(this->get_logger(), "Invalid sensor type (must be either 'velodyne' or 'ouster'): %s", sensorStr.c_str());
                rclcpp::shutdown();
            }
        }

        N_SCAN = this->declare_parameter<int>("disco_slam/N_SCAN", 16);
        Horizon_SCAN = this->declare_parameter<int>("disco_slam/Horizon_SCAN", 1800);
        downsampleRate = this->declare_parameter<int>("disco_slam/downsampleRate", 1);
        lidarMinRange = this->declare_parameter<float>("disco_slam/lidarMinRange", 1.0);
        lidarMaxRange = this->declare_parameter<float>("disco_slam/lidarMaxRange", 1000.0);

        imuAccNoise = this->declare_parameter<float>("disco_slam/imuAccNoise", 0.01);
        imuGyrNoise = this->declare_parameter<float>("disco_slam/imuGyrNoise", 0.001);
        imuAccBiasN = this->declare_parameter<float>("disco_slam/imuAccBiasN", 0.0002);
        imuGyrBiasN = this->declare_parameter<float>("disco_slam/imuGyrBiasN", 0.00003);
        imuGravity = this->declare_parameter<float>("disco_slam/imuGravity", 9.80511);
        imuRPYWeight = this->declare_parameter<float>("disco_slam/imuRPYWeight", 0.01);
        
        extRotV = this->declare_parameter<vector<double>>("disco_slam/extrinsicRot", vector<double>());
        extRPYV = this->declare_parameter<vector<double>>("disco_slam/extrinsicRPY", vector<double>());
        extTransV = this->declare_parameter<vector<double>>("disco_slam/extrinsicTrans", vector<double>());

        if(!extRotV.empty())
            extRot = Eigen::Map<const Eigen::Matrix<double, -1, -1, Eigen::RowMajor>>(extRotV.data(), 3, 3);
        else 
            extRot = Eigen::Matrix3d::Identity();

        if(!extRPYV.empty())
        {
            extRPY = Eigen::Map<const Eigen::Matrix<double, -1, -1, Eigen::RowMajor>>(extRPYV.data(), 3, 3);
            extQRPY = Eigen::Quaterniond(extRPY);
        }
        else
        {
            extRPY = Eigen::Matrix3d::Identity();
            extQRPY = Eigen::Quaterniond::Identity();
        }

        if(!extTransV.empty())
            extTrans = Eigen::Map<const Eigen::Matrix<double, -1, -1, Eigen::RowMajor>>(extTransV.data(), 3, 1);
        else
            extTrans = Eigen::Vector3d::Zero();


        edgeThreshold = this->declare_parameter<float>("disco_slam/edgeThreshold", 0.1);
        surfThreshold = this->declare_parameter<float>("disco_slam/surfThreshold", 0.1);
        edgeFeatureMinValidNum = this->declare_parameter<int>("disco_slam/edgeFeatureMinValidNum", 10);
        surfFeatureMinValidNum = this->declare_parameter<int>("disco_slam/surfFeatureMinValidNum", 100);

        odometrySurfLeafSize = this->declare_parameter<float>("disco_slam/odometrySurfLeafSize", 0.2);
        mappingCornerLeafSize = this->declare_parameter<float>("disco_slam/mappingCornerLeafSize", 0.2);
        mappingSurfLeafSize = this->declare_parameter<float>("disco_slam/mappingSurfLeafSize", 0.2);

        z_tollerance = this->declare_parameter<float>("disco_slam/z_tollerance", FLT_MAX);
        rotation_tollerance = this->declare_parameter<float>("disco_slam/rotation_tollerance", FLT_MAX);

        numberOfCores = this->declare_parameter<int>("disco_slam/numberOfCores", 2);
        mappingProcessInterval = this->declare_parameter<double>("disco_slam/mappingProcessInterval", 0.15);

        surroundingkeyframeAddingDistThreshold = this->declare_parameter<float>("disco_slam/surroundingkeyframeAddingDistThreshold", 1.0);
        surroundingkeyframeAddingAngleThreshold = this->declare_parameter<float>("disco_slam/surroundingkeyframeAddingAngleThreshold", 0.2);
        surroundingKeyframeDensity = this->declare_parameter<float>("disco_slam/surroundingKeyframeDensity", 1.0);
        surroundingKeyframeSearchRadius = this->declare_parameter<float>("disco_slam/surroundingKeyframeSearchRadius", 50.0);

        loopClosureEnableFlag = this->declare_parameter<bool>("disco_slam/loopClosureEnableFlag", false);
        loopClosureFrequency = this->declare_parameter<float>("disco_slam/loopClosureFrequency", 1.0);
        surroundingKeyframeSize = this->declare_parameter<int>("disco_slam/surroundingKeyframeSize", 50);
        historyKeyframeSearchRadius = this->declare_parameter<float>("disco_slam/historyKeyframeSearchRadius", 10.0);
        historyKeyframeSearchTimeDiff = this->declare_parameter<float>("disco_slam/historyKeyframeSearchTimeDiff", 30.0);
        historyKeyframeSearchNum = this->declare_parameter<int>("disco_slam/historyKeyframeSearchNum", 25);
        historyKeyframeFitnessScore = this->declare_parameter<float>("disco_slam/historyKeyframeFitnessScore", 0.3);

        globalMapVisualizationSearchRadius = this->declare_parameter<float>("disco_slam/globalMapVisualizationSearchRadius", 1e3);
        globalMapVisualizationPoseDensity = this->declare_parameter<float>("disco_slam/globalMapVisualizationPoseDensity", 10.0);
        globalMapVisualizationLeafSize = this->declare_parameter<float>("disco_slam/globalMapVisualizationLeafSize", 1.0);

        hasRing = this->declare_parameter<bool>("disco_slam/has_ring", true);
        angBottom = this->declare_parameter<float>("disco_slam/ang_bottom", 15.0);
        angResY = this->declare_parameter<float>("disco_slam/ang_res_y", 2.0);

        usleep(100);
    }

    sensor_msgs::Imu imuConverter(const sensor_msgs::Imu& imu_in)
    {
        sensor_msgs::Imu imu_out = imu_in;
        // rotate acceleration
        Eigen::Vector3d acc(imu_in.linear_acceleration.x, imu_in.linear_acceleration.y, imu_in.linear_acceleration.z);
        acc = extRot * acc;
        imu_out.linear_acceleration.x = acc.x();
        imu_out.linear_acceleration.y = acc.y();
        imu_out.linear_acceleration.z = acc.z();
        // rotate gyroscope
        Eigen::Vector3d gyr(imu_in.angular_velocity.x, imu_in.angular_velocity.y, imu_in.angular_velocity.z);
        gyr = extRot * gyr;
        imu_out.angular_velocity.x = gyr.x();
        imu_out.angular_velocity.y = gyr.y();
        imu_out.angular_velocity.z = gyr.z();
        // rotate roll pitch yaw
        Eigen::Quaterniond q_from(imu_in.orientation.w, imu_in.orientation.x, imu_in.orientation.y, imu_in.orientation.z);
        Eigen::Quaterniond q_final = q_from * extQRPY;
        imu_out.orientation.x = q_final.x();
        imu_out.orientation.y = q_final.y();
        imu_out.orientation.z = q_final.z();
        imu_out.orientation.w = q_final.w();

        if (sqrt(q_final.x()*q_final.x() + q_final.y()*q_final.y() + q_final.z()*q_final.z() + q_final.w()*q_final.w()) < 0.1)
        {
            RCLCPP_ERROR(this->get_logger(), "Invalid quaternion, please use a 9-axis IMU!");
            rclcpp::shutdown();
        }

        return imu_out;
    }
};
#endif
