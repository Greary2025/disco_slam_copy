// Node: path_to_tum
// Subscribes to a nav_msgs/Path topic and writes incremental poses
// to a TUM trajectory text file compatible with evo tools.
// Format per line: timestamp tx ty tz qx qy qz qw
// Avoids duplicate writing by tracking previously written pose count.

#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/path.hpp>
#include <geometry_msgs/msg/pose_stamped.hpp>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class PathToTumRecorder : public rclcpp::Node {
public:
	PathToTumRecorder(const rclcpp::NodeOptions & options) : Node("path_to_tum", options) {
		// Parameters
		this->declare_parameter<std::string>("path_topic", "/xianfeng/disco_slam/mapping/path");
		this->declare_parameter<std::string>("output_dir", "/tmp");
		this->declare_parameter<std::string>("output_filename", "trajectory.txt");
		this->declare_parameter<bool>("overwrite", true);
		this->declare_parameter<bool>("create_dir", true);
		this->declare_parameter<int>("flush_every", 20);

		this->get_parameter("path_topic", path_topic_);
		this->get_parameter("output_dir", output_dir_);
		this->get_parameter("output_filename", output_filename_);
		this->get_parameter("overwrite", overwrite_);
		this->get_parameter("create_dir", create_dir_);
		this->get_parameter("flush_every", flush_every_);

		// Ensure directory exists
		if (create_dir_) ensureDirectory(output_dir_);

		std::string full_path = output_dir_ + "/" + output_filename_;
		file_path_ = full_path;

		std::ios_base::openmode mode = std::ios::out;
		if (!overwrite_) mode |= std::ios::app; // append mode
		else mode |= std::ios::trunc;

		outfile_.open(full_path.c_str(), mode);
		if (!outfile_.is_open()) {
			RCLCPP_ERROR_STREAM(this->get_logger(), "Failed to open output file: " << full_path);
		} else {
			RCLCPP_INFO_STREAM(this->get_logger(), "Recording path to TUM file: " << full_path);
			if (overwrite_) RCLCPP_INFO(this->get_logger(), "Overwrite enabled: starting fresh file");
		}

		sub_ = this->create_subscription<nav_msgs::msg::Path>(
			path_topic_, 1, std::bind(&PathToTumRecorder::pathCallback, this, std::placeholders::_1));
	}

	~PathToTumRecorder() {
		if (outfile_.is_open()) {
			outfile_.flush();
			outfile_.close();
		}
	}

private:
	void pathCallback(const nav_msgs::msg::Path::SharedPtr msg) {
		if (!outfile_.is_open()) return;
		size_t total = msg->poses.size();
		if (total == 0) return;
		if (written_count_ > total) {
			// Path reset scenario; rewrite from scratch if overwrite_ else just continue.
			RCLCPP_WARN(this->get_logger(), "Path size decreased; assuming reset. Not rewriting old data.");
		}
		// Write only new poses
		for (size_t i = written_count_; i < total; ++i) {
			const geometry_msgs::msg::PoseStamped &ps = msg->poses[i];
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

	static double toTimestamp(const builtin_interfaces::msg::Time &stamp) {
		// Convert ROS time to double seconds with high precision
		return static_cast<double>(stamp.sec) + static_cast<double>(stamp.nanosec) * 1e-9;
	}

	void ensureDirectory(const std::string &dir) {
		struct stat st;
		if (stat(dir.c_str(), &st) == 0) {
			if (!S_ISDIR(st.st_mode)) {
				RCLCPP_ERROR_STREAM(this->get_logger(), "Path exists but is not a directory: " << dir);
			}
			return;
		}
		// Attempt recursive creation using system mkdir -p (simpler without extra deps)
		std::string cmd = std::string("mkdir -p ") + dir;
		int ret = ::system(cmd.c_str());
		if (ret != 0) {
			RCLCPP_ERROR_STREAM(this->get_logger(), "Failed to create directory: " << dir << " (ret=" << ret << ")");
		} else {
			RCLCPP_INFO_STREAM(this->get_logger(), "Created directory: " << dir);
		}
	}

	rclcpp::Subscription<nav_msgs::msg::Path>::SharedPtr sub_;
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
	rclcpp::init(argc, argv);
	rclcpp::NodeOptions options;
	auto node = std::make_shared<PathToTumRecorder>(options);
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}

