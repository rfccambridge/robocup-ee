## Installing ROS Kinetic
- Follow the steps 1.1 - 1.5 in this guide here: http://wiki.ros.org/kinetic/Installation/Ubuntu

## Build Environment Installation

- Make sure you have clang-format installed: 

        apt-cache search clang-format
        sudo apt-get install clang-format-<version>
    
- `source /opt/ros/kinetic/setup.bash`
- `cd <your robocup directory>/catkin_ws/src`
- `catkin_init_workspace`
- `cd <your robocup directory>/catkin_ws`
- `catkin_make`
- `rosrun using_markers brain`
- `source <your robocup directory>/catkin_ws/devel/setup.bash`

### Persistent Evinvironment Setup
- To have ROS initialized everytime you open a terminal window, simply add the `source` line above to the end of your `~/.bashrc` file.

## Running the Rendered, Simulator and Engine
### Renderer
- `roscore`
- `rosrun rviz rviz`

### Simulator
- `rosrun using_markers simulator`

### Engine
- Make sure running `echo $ROS_PACKAGE_PATH` prints something similar to `/home/<your_user>/catkin_ws/src:/opt/ros/kinetic/share:/opt/ros/kinetic/stacks`

## Setting Up Your Own Branch To Work In

- `git checkout -b <your name>_branch`
- Now, all changes you make will affect only your environment and no one else's.
