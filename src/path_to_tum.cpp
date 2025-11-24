// Node: path_to_tum
// Subscribes to a nav_msgs/Path topic and writes incremental poses
// to a TUM trajectory text file compatible with evo tools.
// Format per line: timestamp tx ty tz qx qy qz qw
// Avoids duplicate writing by tracking previously written pose count.

#include <ros/ros.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>
#include <tf/transform_datatypes.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class PathToTumRecorder {
public:
	PathToTumRecorder(ros::NodeHandle &nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh) {
		// Parameters
		pnh_.param<std::string>("path_topic", path_topic_, "/xianfeng/disco_slam/mapping/path");
		pnh_.param<std::string>("output_dir", output_dir_, std::string("/tmp"));
		pnh_.param<std::string>("output_filename", output_filename_, std::string("trajectory.txt"));
		pnh_.param<bool>("overwrite", overwrite_, true);
		pnh_.param<bool>("create_dir", create_dir_, true);
		pnh_.param<int>("flush_every", flush_every_, 20); // flush every N new poses

		// Ensure directory exists
		if (create_dir_) ensureDirectory(output_dir_);

		std::string full_path = output_dir_ + "/" + output_filename_;
		file_path_ = full_path;

		std::ios_base::openmode mode = std::ios::out;
		if (!overwrite_) mode |= std::ios::app; // append mode
		else mode |= std::ios::trunc;

		outfile_.open(full_path.c_str(), mode);
		if (!outfile_.is_open()) {
			ROS_ERROR_STREAM("Failed to open output file: " << full_path);
		} else {
			ROS_INFO_STREAM("Recording path to TUM file: " << full_path);
			if (overwrite_) ROS_INFO("Overwrite enabled: starting fresh file");
		}

		sub_ = nh_.subscribe(path_topic_, 1, &PathToTumRecorder::pathCallback, this);
	}

	~PathToTumRecorder() {
		if (outfile_.is_open()) {
			outfile_.flush();
			outfile_.close();
		}
	}

private:
	void pathCallback(const nav_msgs::Path::ConstPtr &msg) {
		if (!outfile_.is_open()) return;
		size_t total = msg->poses.size();
		if (total == 0) return;
		if (written_count_ > total) {
			// Path reset scenario; rewrite from scratch if overwrite_ else just continue.
			ROS_WARN("Path size decreased; assuming reset. Not rewriting old data.");
		}
		// Write only new poses
		for (size_t i = written_count_; i < total; ++i) {
			const geometry_msgs::PoseStamped &ps = msg->poses[i];
			double t = toTimestamp(ps.header.stamp);
			double tx = ps.pose.position.x;
			double ty = ps.pose.position.y;
			double tz = ps.pose.position.z;
			double qx = ps.pose.orientation.x;
			double qy = ps.pose.orientation.y;
			double qz = ps.pose.orientation.z;
			double qw = ps.pose.orientation.w;
			outfile_ << std::fixed << std::setprecision(9)
							 << t << " " << tx << " " << ty << " " << tz << " "
							 << qx << " " << qy << " " << qz << " " << qw << "\n";
			++new_since_flush_;
		}
		written_count_ = total;
		if (new_since_flush_ >= static_cast<size_t>(flush_every_)) {
			outfile_.flush();
			new_since_flush_ = 0;
		}
	}

	static double toTimestamp(const ros::Time &stamp) {
		// Convert ROS time to double seconds with high precision
		return static_cast<double>(stamp.sec) + static_cast<double>(stamp.nsec) * 1e-9;
	}

	void ensureDirectory(const std::string &dir) {
		struct stat st;
		if (stat(dir.c_str(), &st) == 0) {
			if (!S_ISDIR(st.st_mode)) {
				ROS_ERROR_STREAM("Path exists but is not a directory: " << dir);
			}
			return;
		}
		// Attempt recursive creation using system mkdir -p (simpler without extra deps)
		std::string cmd = std::string("mkdir -p ") + dir;
		int ret = ::system(cmd.c_str());
		if (ret != 0) {
			ROS_ERROR_STREAM("Failed to create directory: " << dir << " (ret=" << ret << ")");
		} else {
			ROS_INFO_STREAM("Created directory: " << dir);
		}
	}

	ros::NodeHandle nh_;
	ros::NodeHandle pnh_;
	ros::Subscriber sub_;
	std::ofstream outfile_;
	std::string path_topic_;
	std::string output_dir_;
	std::string output_filename_;
	std::string file_path_;
	bool overwrite_{true};
	bool create_dir_{true};
	int flush_every_{20};
	size_t written_count_{0};
	size_t new_since_flush_{0};
};

int main(int argc, char **argv) {
	ros::init(argc, argv, "path_to_tum");
	ros::NodeHandle nh;
	ros::NodeHandle pnh("~");
	PathToTumRecorder recorder(nh, pnh);
	ros::spin();
	return 0;
}

