import os

# Define the mapping from ROS 1 RViz classes to ROS 2 RViz classes
replacements = {
    'rviz/Displays': 'rviz_common/Displays',
    'rviz/Selection': 'rviz_common/Selection',
    'rviz/Views': 'rviz_common/Views',
    'rviz/Tool Properties': 'rviz_common/Tool Properties',
    'rviz/Group': 'rviz_default_plugins/Group',
    'rviz/TF': 'rviz_default_plugins/TF',
    'rviz/Axes': 'rviz_default_plugins/Axes',
    'rviz/Odometry': 'rviz_default_plugins/Odometry',
    'rviz/PointCloud2': 'rviz_default_plugins/PointCloud2',
    'rviz/Path': 'rviz_default_plugins/Path',
    'rviz/Grid': 'rviz_default_plugins/Grid',
    'rviz/RobotModel': 'rviz_default_plugins/RobotModel',
    'rviz/Interact': 'rviz_default_plugins/Interact',
    'rviz/FocusCamera': 'rviz_default_plugins/FocusCamera',
    'rviz/Measure': 'rviz_default_plugins/Measure',
    'rviz/SetInitialPose': 'rviz_default_plugins/SetInitialPose',
    'rviz/SetGoal': 'rviz_default_plugins/SetGoal',
    'rviz/Orbit': 'rviz_default_plugins/Orbit',
    'rviz/XYOrbit': 'rviz_default_plugins/XYOrbit',
    'rviz/ThirdPersonFollower': 'rviz_default_plugins/ThirdPersonFollower',
    'rviz/FPS': 'rviz_default_plugins/FPS',
}

input_path = '/home/john22/disco_origin/src/disco_slam_copy/launch/include/config/rviz.rviz'
output_path = '/home/john22/disco_origin/src/disco_slam_copy/launch/include/config/rviz2.rviz'

try:
    with open(input_path, 'r') as f:
        content = f.read()

    # Perform replacements
    for old, new in replacements.items():
        content = content.replace(f'Class: {old}', f'Class: {new}')

    # Also check for View controllers which might be under "Current" or "Saved"
    # The pattern is usually "Class: rviz/Orbit" which is covered above.

    with open(output_path, 'w') as f:
        f.write(content)

    print(f"Successfully created {output_path}")

except Exception as e:
    print(f"Error converting rviz file: {e}")
