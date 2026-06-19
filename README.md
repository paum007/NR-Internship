# NR-Internship

aum@Ubuntu24:~/uros_ws$ colcon build
Starting >>> micro_ros_msgs
Starting >>> drive_base_msgs
Starting >>> micro_ros_setup
Finished <<< micro_ros_setup [0.39s]                                                                                              
--- stderr: micro_ros_msgs                                                                       
Traceback (most recent call last):
  File "/home/paum/ros2_ws/install/ament_cmake_core/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py", line 22, in <module>
    from catkin_pkg.package import parse_package_string
ModuleNotFoundError: No module named 'catkin_pkg'
CMake Error at /home/paum/ros2_ws/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package_xml.cmake:95 (message):
  execute_process(/home/paum/.platformio/penv/bin/python3
  /home/paum/ros2_ws/install/ament_cmake_core/share/ament_cmake_core/cmake/core/package_xml_2_cmake.py
  /home/paum/uros_ws/src/uros/micro_ros_msgs/package.xml
  /home/paum/uros_ws/build/micro_ros_msgs/ament_cmake_core/package.cmake)
  returned error code 1
Call Stack (most recent call first):
  /home/paum/ros2_ws/install/ament_cmake_core/share/ament_cmake_core/cmake/core/ament_package_xml.cmake:49 (_ament_package_xml)
  /home/paum/ros2_ws/install/ament_lint_auto/share/ament_lint_auto/cmake/ament_lint_auto_find_test_dependencies.cmake:31 (ament_package_xml)
  CMakeLists.txt:24 (ament_lint_auto_find_test_dependencies)


---
Failed   <<< micro_ros_msgs [1.46s, exited with code 1]
Aborted  <<< drive_base_msgs [11.5s]                                  

Summary: 1 package finished [11.8s]
  1 package failed: micro_ros_msgs
  1 package aborted: drive_base_msgs
  1 package had stderr output: micro_ros_msgs
  1 package not processed
