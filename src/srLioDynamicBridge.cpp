#include <deque>

#include "utility.h"
#include "disco_slam/cloud_info.h"

class SrLioDynamicBridge : public ParamServer
{
public:
    ros::Subscriber subCloudInfo;
    ros::Subscriber subDynamicPoints;

    ros::Publisher pubFilteredCloudInfo;
    ros::Publisher pubStaticCloud;
    ros::Publisher pubDynamicRemovedCloud;

    struct BufferedDynamicCloud
    {
        ros::Time stamp;
        pcl::PointCloud<PointType>::Ptr cloud;
    };

    std::mutex bufferMutex;
    std::mutex processMutex;
    std::deque<BufferedDynamicCloud> dynamicCloudBuffer;
    std::deque<disco_slam::cloud_info> pendingCloudInfos;

    std::string inputCloudInfoTopic;
    std::string inputDynamicTopic;
    std::string outputCloudInfoTopic;
    std::string outputStaticCloudTopic;
    std::string outputDynamicRemovedTopic;

    double dynamicMatchRadius;
    double timeSyncTolerance;
    int logInterval;
    int frameCount;
    int bufferSize;

    SrLioDynamicBridge()
        : dynamicMatchRadius(0.5), timeSyncTolerance(0.15), logInterval(0), frameCount(0),
          bufferSize(30)
    {
        ros::NodeHandle pnh("~");

        inputCloudInfoTopic = robot_id + "/disco_slam/deskew/cloud_info";
        inputDynamicTopic = robot_id + "/sr_lio/dynamic_points_sampled";
        outputCloudInfoTopic = robot_id + "/disco_slam/deskew/cloud_info_filtered";
        outputStaticCloudTopic = robot_id + "/disco_slam/deskew/cloud_static_filtered";
        outputDynamicRemovedTopic = robot_id + "/disco_slam/deskew/cloud_dynamic_removed";

        pnh.param<std::string>("input_cloud_info_topic", inputCloudInfoTopic, inputCloudInfoTopic);
        pnh.param<std::string>("input_dynamic_points_topic", inputDynamicTopic, inputDynamicTopic);
        pnh.param<std::string>("output_cloud_info_topic", outputCloudInfoTopic, outputCloudInfoTopic);
        pnh.param<std::string>("output_static_cloud_topic", outputStaticCloudTopic, outputStaticCloudTopic);
        pnh.param<std::string>("output_dynamic_removed_topic", outputDynamicRemovedTopic, outputDynamicRemovedTopic);
        pnh.param<double>("dynamic_match_radius", dynamicMatchRadius, dynamicMatchRadius);
        pnh.param<double>("time_sync_tolerance", timeSyncTolerance, timeSyncTolerance);
        pnh.param<int>("log_interval", logInterval, logInterval);
        pnh.param<int>("buffer_size", bufferSize, bufferSize);

        subCloudInfo = nh.subscribe<disco_slam::cloud_info>(
            inputCloudInfoTopic, 5, &SrLioDynamicBridge::cloudInfoHandler, this,
            ros::TransportHints().tcpNoDelay());
        subDynamicPoints = nh.subscribe<sensor_msgs::PointCloud2>(
            inputDynamicTopic, 5, &SrLioDynamicBridge::dynamicPointsHandler, this,
            ros::TransportHints().tcpNoDelay());

        pubFilteredCloudInfo = nh.advertise<disco_slam::cloud_info>(outputCloudInfoTopic, 5);
        pubStaticCloud = nh.advertise<sensor_msgs::PointCloud2>(outputStaticCloudTopic, 5);
        pubDynamicRemovedCloud = nh.advertise<sensor_msgs::PointCloud2>(outputDynamicRemovedTopic, 5);
    }

    void dynamicPointsHandler(const sensor_msgs::PointCloud2ConstPtr& msg)
    {
        BufferedDynamicCloud bufferedCloud;
        bufferedCloud.stamp = msg->header.stamp;
        bufferedCloud.cloud.reset(new pcl::PointCloud<PointType>());
        pcl::fromROSMsg(*msg, *bufferedCloud.cloud);

        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            dynamicCloudBuffer.push_back(bufferedCloud);
            trimBufferLocked(dynamicCloudBuffer);
        }

        processPendingCloudInfos();
    }

    void cloudInfoHandler(const disco_slam::cloud_infoConstPtr& msgIn)
    {
        {
            std::lock_guard<std::mutex> lock(bufferMutex);
            pendingCloudInfos.push_back(*msgIn);
            trimBufferLocked(pendingCloudInfos);
        }

        processPendingCloudInfos();
    }

private:
    template <typename T>
    void trimBufferLocked(std::deque<T>& buffer)
    {
        while (static_cast<int>(buffer.size()) > bufferSize)
            buffer.pop_front();
    }

    void processPendingCloudInfos()
    {
        std::lock_guard<std::mutex> processLock(processMutex);

        while (true)
        {
            disco_slam::cloud_info cloudInfo;
            pcl::PointCloud<PointType>::Ptr matchedDynamicCloud(new pcl::PointCloud<PointType>());

            {
                std::lock_guard<std::mutex> lock(bufferMutex);

                int cloudInfoIndex = -1;
                int dynamicCloudIndex = -1;
                if (!findMatchedPairLocked(cloudInfoIndex, dynamicCloudIndex))
                    return;

                cloudInfo = pendingCloudInfos[cloudInfoIndex];
                *matchedDynamicCloud = *dynamicCloudBuffer[dynamicCloudIndex].cloud;

                pendingCloudInfos.erase(pendingCloudInfos.begin() + cloudInfoIndex);
                dynamicCloudBuffer.erase(dynamicCloudBuffer.begin() + dynamicCloudIndex);
            }

            processMatchedCloudInfo(cloudInfo, matchedDynamicCloud);
        }
    }

    bool findMatchedPairLocked(int& cloudInfoIndex, int& dynamicCloudIndex) const
    {
        if (pendingCloudInfos.empty() || dynamicCloudBuffer.empty())
            return false;

        double bestDelta = timeSyncTolerance;
        bool foundMatch = false;

        for (int infoIdx = 0; infoIdx < static_cast<int>(pendingCloudInfos.size()); ++infoIdx)
        {
            const ros::Time& infoStamp = pendingCloudInfos[infoIdx].header.stamp;
            for (int dynamicIdx = 0; dynamicIdx < static_cast<int>(dynamicCloudBuffer.size()); ++dynamicIdx)
            {
                const double delta = std::abs((infoStamp - dynamicCloudBuffer[dynamicIdx].stamp).toSec());
                if (delta <= bestDelta)
                {
                    bestDelta = delta;
                    cloudInfoIndex = infoIdx;
                    dynamicCloudIndex = dynamicIdx;
                    foundMatch = true;
                }
            }
        }

        return foundMatch;
    }

    void processMatchedCloudInfo(
        const disco_slam::cloud_info& msgIn,
        const pcl::PointCloud<PointType>::Ptr& matchedDynamicCloud)
    {
        pcl::PointCloud<PointType>::Ptr inputCloud(new pcl::PointCloud<PointType>());
        pcl::fromROSMsg(msgIn.cloud_deskewed, *inputCloud);

        if (inputCloud->empty())
        {
            pcl::PointCloud<PointType>::Ptr emptyCloud(new pcl::PointCloud<PointType>());
            publishCloud(&pubStaticCloud, emptyCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);
            publishCloud(&pubDynamicRemovedCloud, emptyCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);
            pubFilteredCloudInfo.publish(msgIn);
            return;
        }

        if (!matchedDynamicCloud || matchedDynamicCloud->empty())
        {
            publishCloud(&pubStaticCloud, inputCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);

            pcl::PointCloud<PointType>::Ptr emptyCloud(new pcl::PointCloud<PointType>());
            publishCloud(&pubDynamicRemovedCloud, emptyCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);

            pubFilteredCloudInfo.publish(msgIn);
            return;
        }

        pcl::KdTreeFLANN<PointType> dynamicTree;
        dynamicTree.setInputCloud(matchedDynamicCloud);

        disco_slam::cloud_info filteredInfo = msgIn;
        filteredInfo.startRingIndex.assign(N_SCAN, 0);
        filteredInfo.endRingIndex.assign(N_SCAN, 0);
        filteredInfo.pointColInd.assign(N_SCAN * Horizon_SCAN, 0);
        filteredInfo.pointRange.assign(N_SCAN * Horizon_SCAN, 0);

        pcl::PointCloud<PointType>::Ptr keptCloud(new pcl::PointCloud<PointType>());
        pcl::PointCloud<PointType>::Ptr removedCloud(new pcl::PointCloud<PointType>());

        const std::vector<int> ringBegin = recoverRingBegin(msgIn, static_cast<int>(inputCloud->size()));

        int outputCount = 0;
        for (int ring = 0; ring < N_SCAN; ++ring)
        {
            filteredInfo.startRingIndex[ring] = outputCount - 1 + 5;

            const int begin = ringBegin[ring];
            const int end = (ring + 1 < N_SCAN) ? ringBegin[ring + 1] - 1 : static_cast<int>(inputCloud->size()) - 1;

            if (begin > end || begin >= static_cast<int>(inputCloud->size()))
            {
                filteredInfo.endRingIndex[ring] = outputCount - 1 - 5;
                continue;
            }

            for (int idx = begin; idx <= end; ++idx)
            {
                if (idx < 0 || idx >= static_cast<int>(inputCloud->size()))
                    continue;

                if (isDynamicPoint(dynamicTree, inputCloud->points[idx]))
                {
                    removedCloud->push_back(inputCloud->points[idx]);
                    continue;
                }

                keptCloud->push_back(inputCloud->points[idx]);
                if (outputCount < static_cast<int>(filteredInfo.pointColInd.size()) &&
                    idx < static_cast<int>(msgIn.pointColInd.size()) &&
                    idx < static_cast<int>(msgIn.pointRange.size()))
                {
                    filteredInfo.pointColInd[outputCount] = msgIn.pointColInd[idx];
                    filteredInfo.pointRange[outputCount] = msgIn.pointRange[idx];
                }
                ++outputCount;
            }

            filteredInfo.endRingIndex[ring] = outputCount - 1 - 5;
        }

        filteredInfo.cloud_deskewed = publishCloud(
            &pubStaticCloud, keptCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);
        publishCloud(&pubDynamicRemovedCloud, removedCloud, msgIn.header.stamp, robot_id + "/" + lidarFrame);
        pubFilteredCloudInfo.publish(filteredInfo);

        frameCount++;
        if (logInterval > 0 && frameCount % logInterval == 0)
        {
            ROS_INFO_STREAM(robot_id << ": SR-LIO bridge kept " << keptCloud->size()
                                     << " points, removed " << removedCloud->size()
                                     << " dynamic points.");
        }
    }

    std::vector<int> recoverRingBegin(const disco_slam::cloud_info& msg, int cloudSize) const
    {
        std::vector<int> ringBegin(N_SCAN, cloudSize);
        if (N_SCAN <= 0)
            return ringBegin;

        ringBegin[0] = 0;
        for (int ring = 1; ring < N_SCAN; ++ring)
        {
            int begin = cloudSize;
            if (ring < static_cast<int>(msg.startRingIndex.size()))
                begin = std::max(0, msg.startRingIndex[ring] - 4);

            begin = std::min(begin, cloudSize);
            begin = std::max(begin, ringBegin[ring - 1]);
            ringBegin[ring] = begin;
        }
        return ringBegin;
    }

    bool isDynamicPoint(pcl::KdTreeFLANN<PointType>& dynamicTree, const PointType& point) const
    {
        std::vector<int> pointSearchInd(1);
        std::vector<float> pointSearchSqDis(1);
        if (dynamicTree.nearestKSearch(point, 1, pointSearchInd, pointSearchSqDis) <= 0)
            return false;

        return pointSearchSqDis[0] <= dynamicMatchRadius * dynamicMatchRadius;
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "disco_slam_sr_lio_dynamic_bridge");

    SrLioDynamicBridge bridge;

    ros::spin();

    return 0;
}
