import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, GroupAction
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    project_name = 'disco_slam'
    share_dir = get_package_share_directory(project_name)
    
    # Configuration files
    params_file = os.path.join(share_dir, 'config', 'params_ue.yaml')
    mapfusion_config_file = os.path.join(share_dir, 'config', 'mapfusion_ue.yaml')
    # Use the converted ROS 2 RViz config
    rviz_config_file = os.path.join(share_dir, 'launch', 'include', 'config', 'rviz_ros2.rviz')
    # rviz1_config_file = os.path.join(share_dir, 'launch', 'include', 'config', 'rviz1_ros2.rviz')
    # rviz2_config_file = os.path.join(share_dir, 'launch', 'include', 'config', 'rviz2_ros2.rviz')

    # Arguments
    robot0_arg = DeclareLaunchArgument('robot0', default_value='xianfeng')
    robot1_arg = DeclareLaunchArgument('robot1', default_value='gensui')
    robot2_arg = DeclareLaunchArgument('robot2', default_value='jackal2')
    no_arg = DeclareLaunchArgument('no', default_value='1')
    bag_path_arg = DeclareLaunchArgument('discoslam_bag', default_value='/mnt/c/Users/Greary/Documents/rosbag/asynchronous_1014.bag')

    robot0 = LaunchConfiguration('robot0')
    robot1 = LaunchConfiguration('robot1')
    robot2 = LaunchConfiguration('robot2')
    no = LaunchConfiguration('no')
    bag_path = LaunchConfiguration('discoslam_bag')

    def create_robot_nodes(robot_name, id1_name, id2_name):
        return [
            Node(
                package=project_name,
                executable=f'{project_name}_imuPreintegration',
                name=[project_name, '_imuPreintegration_', robot_name],
                parameters=[params_file, mapfusion_config_file, {
                    'robot_id': robot_name,
                    'no': no
                }],
                output='screen',
                respawn=True
            ),
            Node(
                package=project_name,
                executable=f'{project_name}_imageProjection',
                name=[project_name, '_imageProjection_', robot_name],
                parameters=[params_file, mapfusion_config_file, {
                    'robot_id': robot_name,
                    'no': no
                }],
                output='screen',
                respawn=True
            ),
            Node(
                package=project_name,
                executable=f'{project_name}_featureExtraction',
                name=[project_name, '_featureExtraction_', robot_name],
                parameters=[params_file, mapfusion_config_file, {
                    'robot_id': robot_name,
                    'no': no
                }],
                output='screen',
                respawn=True
            ),
            Node(
                package=project_name,
                executable=f'{project_name}_mapOptmization',
                name=[project_name, '_mapOptmization_', robot_name],
                parameters=[params_file, mapfusion_config_file, {
                    'robot_id': robot_name,
                    'no': no
                }],
                output='screen',
                respawn=False
            ),
            Node(
                package=project_name,
                executable=f'{project_name}_mapFusion',
                name=[project_name, '_mapFusion_', robot_name],
                parameters=[params_file, mapfusion_config_file, {
                    'robot_id': robot_name,
                    'id_1': id1_name,
                    'id_2': id2_name,
                    'no': no,
                    'pcm_matrix_folder': os.path.join(share_dir, 'config')
                }],
                output='screen',
                respawn=False
            )
        ]

    # Create nodes for robot0 and robot1
    robot0_nodes = create_robot_nodes(robot0, robot1, robot2)
    robot1_nodes = create_robot_nodes(robot1, robot0, robot2)

    # Rviz (Clean instance, no config)
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        name='rviz2',
        arguments=['-d', rviz_config_file],
        output='screen'
    )

    # rviz1_node = Node(
    #     package='rviz2',
    #     executable='rviz2',
    #     name='rviz2_1',
    #     arguments=['-d', rviz1_config_file],
    #     output='screen'
    # )

    # rviz2_node = Node(
    #     package='rviz2',
    #     executable='rviz2',
    #     name='rviz2_2',
    #     arguments=['-d', rviz2_config_file],
    #     output='screen'
    # )

    # Rosbag Play (ROS 2 version) (注释掉启动)
    # Note: ROS 2 bag play uses different arguments. Assuming the user might need to adjust this.
    # The original was: rosbag play -r 1 -q path
    # ROS 2: ros2 bag play path -r 1
    # However, since the input bag is likely ROS 1 bag (.bag), playing it directly in ROS 2 
    # requires ros2 bag play --ros-args -p storage_id:=rosbag_v2 (if plugin installed).
    # For now, I'll comment this out or use a generic ExecuteProcess, but inform the user.
    # Since the user asked "how to launch", providing the launch file is key.
    
    # We will use ExecuteProcess for bag play to be flexible
    # bag_play = ExecuteProcess(
    #     cmd=['ros2', 'bag', 'play', bag_path, '-s', 'rosbag_v2', '-r', '1'],
    #     output='screen'
    # )

    # Path to TUM (optional, from original launch) (注释掉启动)
    # <include file="$(find disco_slam)/launch/run_path_to_tum.launch" />
    # I'll verify if that launch file exists and needs conversion, but for now I'll skip it to keep it simple
    # or just add the node if I can find it.
    
    return LaunchDescription([
        robot0_arg,
        robot1_arg,
        robot2_arg,
        no_arg,
        bag_path_arg,
        *robot0_nodes,
        *robot1_nodes,
        rviz_node,
        # rviz1_node,
        # rviz2_node,
        # bag_play     # rosbag 播放节点
    ])
