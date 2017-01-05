## Installing ROS Kinetic
- Follow the steps 1.1 - 1.5 in this guide here: http://wiki.ros.org/kinetic/Installation/Ubuntu

## Build Environment Installation

- Make sure you have clang-format installed: 
     ```
     apt-cache search clang-format
     sudo apt-get install clang-format-<version>
     ```
- `source /opt/ros/kinetic/setup.bash`
- `cd <your robocup directory>/catkin_ws/src`
- `catkin_init_workspace`
- `cd <your robocup directory>/catkin_ws`
- `catkin_make`

### Persistent Evinvironment Setup
- To have ROS initialized everytime you open a terminal window, simply add the `source` line above to the end of your `~/.bashrc` file.

## Running the Rendered, Simulator and Engine
### Renderer
- `rosrun rviz rviz`
### Simulator
- `rosrun using_markers basic_shapes`
### Engine
- `rosrun using_markers basic_shapes_publisher`