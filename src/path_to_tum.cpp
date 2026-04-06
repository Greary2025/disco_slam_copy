// Node: path_to_tum
// Export multi-robot path, odometry, and fusion transforms into TUM text files.
// Output per line: timestamp tx ty tz qx qy qz qw

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <nav_msgs/Path.h>
#include <geometry_msgs/PoseStamped.h>

#include <boost/bind.hpp>

#include <sys/stat.h>
#include <unistd.h>

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <string>
#include <vector>

class TumRecorder {
public:
	TumRecorder(ros::NodeHandle &nh, ros::NodeHandle &pnh) : nh_(nh), pnh_(pnh) {
		pnh_.param<std::string>("output_dir", output_dir_, std::string("/tmp"));
		pnh_.param<std::string>("fusion_topic", fusion_topic_, std::string("context"));
		pnh_.param<bool>("overwrite", overwrite_, true);
		pnh_.param<bool>("create_dir", create_dir_, true);
		pnh_.param<int>("flush_every", flush_every_, 20);

		if (!pnh_.getParam("robot_ids", robot_ids_)) {
			robot_ids_.push_back("xianfeng");
			robot_ids_.push_back("gensui");
		}

		if (!pnh_.getParam("output_filenames", output_filenames_)) {
			for (const std::string &robot_id : robot_ids_) {
				output_filenames_.push_back(robot_id + "_disco_trajectory.txt");
			}
		}

		if (!pnh_.getParam("output_odom_filenames", output_odom_filenames_)) {
			for (const std::string &robot_id : robot_ids_) {
				output_odom_filenames_.push_back(robot_id + "_disco_odometry.txt");
			}
		}

		if (!pnh_.getParam("output_transform_filenames", output_transform_filenames_)) {
			for (const std::string &robot_id : robot_ids_) {
				output_transform_filenames_.push_back(robot_id + "_fusion_transform.txt");
			}
		}

		normalizeFilenameList(output_filenames_, "_disco_trajectory.txt");
		normalizeFilenameList(output_odom_filenames_, "_disco_odometry.txt");
		normalizeFilenameList(output_transform_filenames_, "_fusion_transform.txt");

		if (create_dir_) ensureDirectory(output_dir_);

		path_recorders_.resize(robot_ids_.size());
		odom_recorders_.resize(robot_ids_.size());
		transform_recorders_.resize(robot_ids_.size());

		for (size_t i = 0; i < robot_ids_.size(); ++i) {
			const std::string &robot_id = robot_ids_[i];

			setupPathRecorder(path_recorders_[i], robot_id,
							  "/" + robot_id + "/disco_slam/mapping/path",
							  output_filenames_[i], i);

			setupOdomRecorder(odom_recorders_[i], robot_id,
							  "/" + robot_id + "/disco_slam/mapping/odometry",
							  output_odom_filenames_[i], i);

			setupOdomRecorder(transform_recorders_[i], robot_id,
							  "/" + robot_id + "/" + fusion_topic_ + "/trans_map",
							  output_transform_filenames_[i], i);
		}
	}

	~TumRecorder() {
		closePathRecorders(path_recorders_);
		closeOdomRecorders(odom_recorders_);
		closeOdomRecorders(transform_recorders_);
	}

private:
	struct PathRecorderState {
		ros::Subscriber sub;
		std::ofstream outfile;
		std::string robot_id;
		std::string topic;
		std::string output_filename;
		std::string file_path;
		size_t written_count{0};
		size_t new_since_flush{0};
	};

	struct OdomRecorderState {
		ros::Subscriber sub;
		std::ofstream outfile;
		std::string robot_id;
		std::string topic;
		std::string output_filename;
		std::string file_path;
		size_t new_since_flush{0};
	};

	void normalizeFilenameList(std::vector<std::string> &files, const std::string &suffix) {
		if (files.size() == robot_ids_.size())
			return;
		ROS_WARN("Filename list size != robot_ids size. Regenerating file names.");
		files.clear();
		for (const std::string &robot_id : robot_ids_) {
			files.push_back(robot_id + suffix);
		}
	}

	void setupPathRecorder(PathRecorderState &state,
						   const std::string &robot_id,
						   const std::string &topic,
						   const std::string &output_filename,
						   size_t index) {
		state.robot_id = robot_id;
		state.topic = topic;
		state.output_filename = output_filename;
		state.file_path = output_dir_ + "/" + output_filename;

		openFile(state.outfile, state.file_path);
		if (state.outfile.is_open()) {
			ROS_INFO_STREAM("Recording " << state.topic << " to " << state.file_path);
		}

		state.sub = nh_.subscribe<nav_msgs::Path>(
			state.topic, 1, boost::bind(&TumRecorder::pathCallback, this, _1, index));
	}

	void setupOdomRecorder(OdomRecorderState &state,
						   const std::string &robot_id,
						   const std::string &topic,
						   const std::string &output_filename,
						   size_t index) {
		state.robot_id = robot_id;
		state.topic = topic;
		state.output_filename = output_filename;
		state.file_path = output_dir_ + "/" + output_filename;

		openFile(state.outfile, state.file_path);
		if (state.outfile.is_open()) {
			ROS_INFO_STREAM("Recording " << state.topic << " to " << state.file_path);
		}

		state.sub = nh_.subscribe<nav_msgs::Odometry>(
			state.topic, 100, boost::bind(&TumRecorder::odometryCallback, this, _1, index, &state));
	}

	void openFile(std::ofstream &outfile, const std::string &file_path) {
		std::ios_base::openmode mode = std::ios::out;
		if (!overwrite_)
			mode |= std::ios::app;
		else
			mode |= std::ios::trunc;

		outfile.open(file_path.c_str(), mode);
		if (!outfile.is_open()) {
			ROS_ERROR_STREAM("Failed to open output file: " << file_path);
		}
	}

	void pathCallback(const nav_msgs::Path::ConstPtr &msg, size_t index) {
		if (index >= path_recorders_.size())
			return;
		PathRecorderState &rec = path_recorders_[index];
		if (!rec.outfile.is_open())
			return;

		size_t total = msg->poses.size();
		if (total == 0)
			return;
		if (rec.written_count > total) {
			ROS_WARN_STREAM("Path size decreased for " << rec.robot_id << ". Resetting write cursor.");
			rec.written_count = 0;
		}

		for (size_t i = rec.written_count; i < total; ++i) {
			const geometry_msgs::PoseStamped &ps = msg->poses[i];
			ros::Time stamp = ps.header.stamp;
			if (stamp.isZero())
				stamp = msg->header.stamp;
			writeTumLine(rec.outfile, stamp, ps.pose.position.x, ps.pose.position.y, ps.pose.position.z,
						 ps.pose.orientation.x, ps.pose.orientation.y, ps.pose.orientation.z, ps.pose.orientation.w);
			++rec.new_since_flush;
		}

		rec.written_count = total;
		if (rec.new_since_flush >= static_cast<size_t>(flush_every_)) {
			rec.outfile.flush();
			rec.new_since_flush = 0;
		}
	}

	void odometryCallback(const nav_msgs::Odometry::ConstPtr &msg, size_t /*index*/, OdomRecorderState *state) {
		if (state == nullptr)
			return;
		if (!state->outfile.is_open())
			return;
		writeTumLine(state->outfile, msg->header.stamp, msg->pose.pose.position.x, msg->pose.pose.position.y,
					 msg->pose.pose.position.z, msg->pose.pose.orientation.x, msg->pose.pose.orientation.y,
					 msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
		++state->new_since_flush;
		if (state->new_since_flush >= static_cast<size_t>(flush_every_)) {
			state->outfile.flush();
			state->new_since_flush = 0;
		}
	}

	static void writeTumLine(std::ofstream &outfile,
							  const ros::Time &stamp,
							  double tx,
							  double ty,
							  double tz,
							  double qx,
							  double qy,
							  double qz,
							  double qw) {
		outfile << std::fixed << std::setprecision(9) << toTimestamp(stamp) << " " << tx << " " << ty << " " << tz
				<< " " << qx << " " << qy << " " << qz << " " << qw << "\n";
	}

	static double toTimestamp(const ros::Time &stamp) {
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
		std::string cmd = std::string("mkdir -p ") + dir;
		int ret = ::system(cmd.c_str());
		if (ret != 0) {
			ROS_ERROR_STREAM("Failed to create directory: " << dir << " (ret=" << ret << ")");
		}
	}

	void closePathRecorders(std::vector<PathRecorderState> &recorders) {
		for (PathRecorderState &rec : recorders) {
			if (rec.outfile.is_open()) {
				rec.outfile.flush();
				rec.outfile.close();
			}
		}
	}

	void closeOdomRecorders(std::vector<OdomRecorderState> &recorders) {
		for (OdomRecorderState &rec : recorders) {
			if (rec.outfile.is_open()) {
				rec.outfile.flush();
				rec.outfile.close();
			}
		}
	}

	ros::NodeHandle nh_;
	ros::NodeHandle pnh_;
	std::vector<std::string> robot_ids_;
	std::vector<std::string> output_filenames_;
	std::vector<std::string> output_odom_filenames_;
	std::vector<std::string> output_transform_filenames_;
	std::vector<PathRecorderState> path_recorders_;
	std::vector<OdomRecorderState> odom_recorders_;
	std::vector<OdomRecorderState> transform_recorders_;
	std::string output_dir_;
	std::string fusion_topic_;
	bool overwrite_{true};
	bool create_dir_{true};
	int flush_every_{20};
};

int main(int argc, char **argv) {
	ros::init(argc, argv, "path_to_tum");
	ros::NodeHandle nh;
	ros::NodeHandle pnh("~");
	TumRecorder recorder(nh, pnh);
	ros::spin();
	return 0;
}
