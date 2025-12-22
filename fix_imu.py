import sys
import os

file_path = '/home/john22/disco_origin/src/disco_slam_copy/src/imageProjection.cpp'
search_str = 'imuRPY2rosRPY(&thisImuMsg, &cloudInfo.imu_roll_init, &cloudInfo.imu_pitch_init, &cloudInfo.imu_yaw_init);'
replace_str = '''{
                double imuRoll, imuPitch, imuYaw;
                imuRPY2rosRPY(&thisImuMsg, &imuRoll, &imuPitch, &imuYaw);
                cloudInfo.imu_roll_init = imuRoll;
                cloudInfo.imu_pitch_init = imuPitch;
                cloudInfo.imu_yaw_init = imuYaw;
            }'''

if not os.path.exists(file_path):
    print(f"Error: File not found at {file_path}")
    sys.exit(1)

with open(file_path, 'r') as f:
    content = f.read()

if search_str in content:
    content = content.replace(search_str, replace_str)
    with open(file_path, 'w') as f:
        f.write(content)
    print("Replaced successfully")
else:
    # Try finding it with stripped spaces just in case indentation varies
    print("Exact string not found, trying fuzzy match...")
    lines = content.splitlines()
    found = False
    for i, line in enumerate(lines):
        if 'imuRPY2rosRPY(&thisImuMsg, &cloudInfo.imu_roll_init, &cloudInfo.imu_pitch_init, &cloudInfo.imu_yaw_init);' in line:
            lines[i] = replace_str
            found = True
            break
    
    if found:
        with open(file_path, 'w') as f:
            f.write('\n'.join(lines))
        print("Replaced successfully (fuzzy)")
    else:
        print("Search string not found even with fuzzy match")
