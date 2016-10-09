## Build Environment Installation

- `source /opt/ros/kinetic/setup.bash`
- `cd <your robocup directory>/catkin_ws/src`
- `catkin_init_workspace`
- `cd <your robocup directory>/catkin_ws`
- `catkin_make`
- `source devel/setup.bash`
- Make sure running `echo $ROS_PACKAGE_PATH` prints something similar to `/home/<your_user>/catkin_ws/src:/opt/ros/kinetic/share:/opt/ros/kinetic/stacks`
