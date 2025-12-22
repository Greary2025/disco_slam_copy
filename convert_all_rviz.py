import os
import glob

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

config_dir = '/home/john22/disco_origin/src/disco_slam_copy/launch/include/config'

# Find all .rviz files
rviz_files = glob.glob(os.path.join(config_dir, '*.rviz'))

for input_path in rviz_files:
    # Skip if it's already converted (heuristic: ends with 2.rviz unless it's the one I made)
    # Actually, I should just overwrite or create new ones.
    # The user mentioned "3 rviz", likely referring to rviz.rviz, rviz1.rviz, and maybe another one if I missed it.
    
    filename = os.path.basename(input_path)
    
    # If the file is already a converted one (I created rviz2.rviz), skip or update it.
    # But let's look at rviz.rviz and rviz1.rviz
    
    output_path = input_path # Overwrite in place? Or create _ros2 version?
    # To be safe and avoid confusion, let's update them in place if they are old format, 
    # OR create a new one and point the launch file to it.
    # Since I don't want to break things if the user wants to revert, I'll create `_ros2.rviz` suffix.
    
    if filename.endswith('_ros2.rviz'):
        continue
        
    # Special handling for my previous creation 'rviz2.rviz' which might be partial? 
    # No, I'll just re-process everything.
    
    output_filename = filename.replace('.rviz', '_ros2.rviz')
    # If filename is rviz.rviz -> rviz_ros2.rviz
    # If filename is rviz1.rviz -> rviz1_ros2.rviz
    
    output_path = os.path.join(config_dir, output_filename)
    
    try:
        with open(input_path, 'r') as f:
            content = f.read()

        # Check if already converted (simple check)
        if 'rviz_common' in content or 'rviz_default_plugins' in content:
            print(f"Skipping {filename} as it seems to be already compatible (or partially converted).")
            # But wait, rviz2.rviz I created IS converted.
            if filename == 'rviz2.rviz':
                 # Re-run just in case I missed something
                 pass
            else:
                 # It might be that I want to enforce conversion
                 pass

        # Perform replacements
        for old, new in replacements.items():
            content = content.replace(f'Class: {old}', f'Class: {new}')

        with open(output_path, 'w') as f:
            f.write(content)

        print(f"Successfully converted {filename} to {output_filename}")

    except Exception as e:
        print(f"Error converting {filename}: {e}")
