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
