paum@Ubuntu24:~/NR-Internship/esp_src/pio_ws$ pio run -e delay -t upload
Processing delay (platform: espressif32; board: upesy_wroom; framework: arduino)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Library Manager: Installing git+https://github.com/micro-ROS/micro_ros_platformio
git version 2.43.0
Cloning into '/home/paum/.platformio/.cache/tmp/pkg-installing-p_mxoeif'...
remote: Enumerating objects: 77, done.
remote: Counting objects: 100% (77/77), done.
remote: Compressing objects: 100% (62/62), done.
remote: Total 77 (delta 12), reused 38 (delta 4), pack-reused 0 (from 0)
Receiving objects: 100% (77/77), 132.22 KiB | 764.00 KiB/s, done.
Resolving deltas: 100% (12/12), done.
Library Manager: micro_ros_platformio@0.0.1+sha.cfee17f has been installed!
Verbose mode can be enabled via `-v, --verbose` option
CONFIGURATION: https://docs.platformio.org/page/boards/espressif32/upesy_wroom.html
PLATFORM: Espressif 32 (7.0.1) > uPesy ESP32 Wroom DevKit
HARDWARE: ESP32 240MHz, 320KB RAM, 4MB Flash
DEBUG: Current (cmsis-dap) External (cmsis-dap, esp-bridge, esp-prog, iot-bus-jtag, jlink, minimodule, olimex-arm-usb-ocd, olimex-arm-usb-ocd-h, olimex-arm-usb-tiny-h, olimex-jtag-tiny, tumpa)
PACKAGES: 
 - framework-arduinoespressif32 @ 3.20017.241212+sha.dcc1105b 
 - tool-esptoolpy @ 2.41100.0 (4.11.0) 
 - tool-mkfatfs @ 2.0.1 
 - tool-mklittlefs @ 1.203.210628 (2.3) 
 - tool-mkspiffs @ 2.230.0 (2.30) 
 - toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
LDF: Library Dependency Finder -> https://bit.ly/configure-pio-ldf
LDF Modes: Finder ~ chain, Compatibility ~ soft
WARNING: Skipping /usr/lib/python3/dist-packages/pytest_repeat.egg-info due to invalid metadata entry 'name'
Installing lark-parser with pip at PlatformIO environment
/usr/bin/python3 -m pip install lark-parser
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Debian-packaged Python package,
    create a virtual environment using python3 -m venv path/to/venv.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip. Make
    sure you have python3-full installed.
    
    If you wish to install a non-Debian packaged Python application,
    it may be easiest to use pipx install xyz, which will manage a
    virtual environment for you. Make sure you have pipx installed.
    
    See /usr/share/doc/python3.12/README.venv for more information.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
*** Error 1
Installing importlib-resources with pip at PlatformIO environment
/usr/bin/python3 -m pip install importlib-resources
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Debian-packaged Python package,
    create a virtual environment using python3 -m venv path/to/venv.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip. Make
    sure you have python3-full installed.
    
    If you wish to install a non-Debian packaged Python application,
    it may be easiest to use pipx install xyz, which will manage a
    virtual environment for you. Make sure you have pipx installed.
    
    See /usr/share/doc/python3.12/README.venv for more information.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
*** Error 1
Installing pyyaml with pip at PlatformIO environment
/usr/bin/python3 -m pip install pyyaml
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Debian-packaged Python package,
    create a virtual environment using python3 -m venv path/to/venv.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip. Make
    sure you have python3-full installed.
    
    If you wish to install a non-Debian packaged Python application,
    it may be easiest to use pipx install xyz, which will manage a
    virtual environment for you. Make sure you have pipx installed.
    
    See /usr/share/doc/python3.12/README.venv for more information.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
*** Error 1
Installing markupsafe==2.0.1 with pip at PlatformIO environment
/usr/bin/python3 -m pip install markupsafe==2.0.1
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Debian-packaged Python package,
    create a virtual environment using python3 -m venv path/to/venv.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip. Make
    sure you have python3-full installed.
    
    If you wish to install a non-Debian packaged Python application,
    it may be easiest to use pipx install xyz, which will manage a
    virtual environment for you. Make sure you have pipx installed.
    
    See /usr/share/doc/python3.12/README.venv for more information.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
*** Error 1
Installing empy==3.3.4 with pip at PlatformIO environment
/usr/bin/python3 -m pip install empy==3.3.4
error: externally-managed-environment

× This environment is externally managed
╰─> To install Python packages system-wide, try apt install
    python3-xyz, where xyz is the package you are trying to
    install.
    
    If you wish to install a non-Debian-packaged Python package,
    create a virtual environment using python3 -m venv path/to/venv.
    Then use path/to/venv/bin/python and path/to/venv/bin/pip. Make
    sure you have python3-full installed.
    
    If you wish to install a non-Debian packaged Python application,
    it may be easiest to use pipx install xyz, which will manage a
    virtual environment for you. Make sure you have pipx installed.
    
    See /usr/share/doc/python3.12/README.venv for more information.

note: If you believe this is a mistake, please contact your Python installation or OS distribution provider. You can override this, at the risk of breaking your Python installation or OS, by passing --break-system-packages.
hint: See PEP 668 for the detailed specification.
*** Error 1
Configuring upesy_wroom with transport wifi
Downloading micro-ROS dev dependencies
	 - Downloaded ament_cmake
	 - Downloaded ament_lint
	 - Downloaded ament_package
	 - Downloaded googletest
	 - Downloaded ament_cmake_ros
	 - Downloaded ament_index
Building micro-ROS dev dependencies
Downloading micro-ROS library
	 - Downloaded microcdr
	 - Downloaded microxrcedds_client
	 - Downloaded rcl
	 - Downloaded rcl_action
	 - Downloaded rcl_yaml_param_parser (ignored)
	 - Downloaded rcl_lifecycle
	 - Downloaded rclc_examples (ignored)
	 - Downloaded rclc_parameter
	 - Downloaded rclc_lifecycle
	 - Downloaded rclc
	 - Downloaded micro_ros_utilities
	 - Downloaded rcutils
	 - Downloaded micro_ros_msgs
	 - Downloaded rmw_microxrcedds
	 - Downloaded rosidl_typesupport_cpp (ignored)
	 - Downloaded rosidl_typesupport_c
	 - Downloaded rosidl_typesupport_tests
	 - Downloaded rosidl_typesupport_microxrcedds_cpp_tests
	 - Downloaded rosidl_typesupport_microxrcedds_c_tests
	 - Downloaded rosidl_typesupport_microxrcedds_test_msg
	 - Downloaded rosidl_typesupport_microxrcedds_c
	 - Downloaded rosidl_typesupport_microxrcedds_cpp (ignored)
	 - Downloaded rosidl_generator_cpp (ignored)
	 - Downloaded rosidl_typesupport_interface
	 - Downloaded rosidl_typesupport_introspection_c
	 - Downloaded rosidl_cmake
	 - Downloaded rosidl_generator_tests
	 - Downloaded rosidl_pycommon
	 - Downloaded rosidl_cli
	 - Downloaded rosidl_typesupport_introspection_tests
	 - Downloaded rosidl_runtime_c
	 - Downloaded rosidl_runtime_cpp (ignored)
	 - Downloaded rosidl_parser
	 - Downloaded rosidl_typesupport_introspection_cpp (ignored)
	 - Downloaded rosidl_generator_c
	 - Downloaded rosidl_adapter
	 - Downloaded rosidl_generator_type_description
	 - Downloaded rosidl_dynamic_typesupport
	 - Downloaded rosidl_core_runtime
	 - Downloaded rosidl_core_generators
	 - Downloaded rmw
	 - Downloaded rmw_implementation_cmake
	 - Downloaded action_msgs
	 - Downloaded composition_interfaces
	 - Downloaded rosgraph_msgs
	 - Downloaded lifecycle_msgs
	 - Downloaded builtin_interfaces
	 - Downloaded type_description_interfaces
	 - Downloaded statistics_msgs
	 - Downloaded rcl_interfaces
	 - Downloaded service_msgs
	 - Downloaded test_msgs
	 - Downloaded rosidl_default_generators
	 - Downloaded rosidl_default_runtime
	 - Downloaded unique_identifier_msgs
	 - Downloaded stereo_msgs
	 - Downloaded common_interfaces
	 - Downloaded diagnostic_msgs
	 - Downloaded trajectory_msgs
	 - Downloaded std_srvs
	 - Downloaded actionlib_msgs
	 - Downloaded sensor_msgs
	 - Downloaded shape_msgs
	 - Downloaded std_msgs
	 - Downloaded nav_msgs
	 - Downloaded geometry_msgs
	 - Downloaded visualization_msgs
	 - Downloaded sensor_msgs_py
	 - Downloaded test_interface_files
	 - Downloaded rmw_implementation
	 - Downloaded test_rmw_implementation
	 - Downloaded rcl_logging_interface
	 - Downloaded rcl_logging_noop
	 - Downloaded rcl_logging_spdlog (ignored)
	 - Downloaded lttngpy (ignored)
	 - Downloaded test_tracetools_launch
	 - Downloaded test_ros2trace
	 - Downloaded tracetools_test
	 - Downloaded tracetools_trace
	 - Downloaded ros2trace
	 - Downloaded tracetools_launch
	 - Downloaded tracetools_read
	 - Downloaded tracetools
	 - Downloaded test_tracetools (ignored)
	 - Extra packages folder not found, skipping...
Building micro-ROS library
Build mcu micro-ROS environment failed: 
--- stderr: test_interface_files
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rmw_implementation_cmake
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rosidl_typesupport_interface
CMake Warning:
  Manually-specified variables were not used by the project:

    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: tracetools
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: microcdr
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_TESTING
    Python3_EXECUTABLE
    THIRDPARTY


---
--- stderr: rcutils
CMake Warning:
  Manually-specified variables were not used by the project:

    ENABLE_TESTING
    THIRDPARTY


/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/error_handling.c: In function 'rcutils_get_error_string':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/error_handling.c:240:38: warning: initializer-string for array of chars is too long
     return (rcutils_error_string_t) {"error not set"};  // NOLINT(readability/braces)
                                      ^~~~~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/error_handling.c:240:38: note: (near initialization for '(anonymous).str')
In file included from /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/error_handling.c:35:
At top level:
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/./error_handling_helpers.h:109:1: warning: '__rcutils_convert_uint64_t_into_c_str' defined but not used [-Wunused-function]
 __rcutils_convert_uint64_t_into_c_str(uint64_t number, char * buffer, size_t buffer_size)
 ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/./error_handling_helpers.h:91:1: warning: '__rcutils_reverse_str' defined but not used [-Wunused-function]
 __rcutils_reverse_str(char * string_in, size_t string_len)
 ^~~~~~~~~~~~~~~~~~~~~
In function 'rcutils_strndup',
    inlined from 'rcutils_strdup' at /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/strdup.c:35:10:
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rcutils/src/strdup.c:47:14: warning: 'memchr' specified size 4294967295 exceeds maximum object size 2147483647 [-Wstringop-overflow=]
   char * p = memchr(str, '\0', max_length);
              ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~
---
--- stderr: microxrcedds_client
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_TESTING
    Python3_EXECUTABLE
    THIRDPARTY


---
--- stderr: rcl_logging_interface
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_runtime_c
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_get_field_map':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:141:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:152:30: warning: unused variable 'error_string' [-Wunused-variable]
       rcutils_error_string_t error_string = rcutils_get_error_string();
                              ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_prune_referenced_type_descriptions_in_place':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:524:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:534:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:544:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_individual_type_description_is_valid':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:668:30: warning: unused variable 'error_string' [-Wunused-variable]
       rcutils_error_string_t error_string = rcutils_get_error_string();
                              ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:684:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:694:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_type_description_is_valid':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:738:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:758:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:770:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:790:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:800:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:821:30: warning: unused variable 'error_string' [-Wunused-variable]
       rcutils_error_string_t error_string = rcutils_get_error_string();
                              ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:835:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:845:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:855:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:865:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_coerce_to_valid_type_description_in_place':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:904:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:915:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:926:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_append_referenced_individual_type_description':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:1191:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_append_referenced_type_description':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:1277:30: warning: unused variable 'error_string' [-Wunused-variable]
       rcutils_error_string_t error_string = rcutils_get_error_string();
                              ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c: In function 'rosidl_runtime_c_type_description_utils_repl_all_type_description_type_names_in_place':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:1438:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl/rosidl_runtime_c/src/type_description_utils.c:1456:32: warning: unused variable 'error_string' [-Wunused-variable]
         rcutils_error_string_t error_string = rcutils_get_error_string();
                                ^~~~~~~~~~~~
---
--- stderr: rosidl_adapter
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rcl_logging_noop
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_dynamic_typesupport
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl_dynamic_typesupport/src/api/dynamic_type.c: In function 'rosidl_dynamic_typesupport_dynamic_type_builder_init_from_description':
/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/src/rosidl_dynamic_typesupport/src/api/dynamic_type.c:318:28: warning: unused variable 'error_string' [-Wunused-variable]
     rcutils_error_string_t error_string = rcutils_get_error_string();
                            ^~~~~~~~~~~~
---
--- stderr: rosidl_parser
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rmw
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_generator_type_description
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_cmake
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rosidl_generator_c
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_typesupport_introspection_c
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_typesupport_microxrcedds_c
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: micro_ros_utilities
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_typesupport_c
CMake Warning:
  Manually-specified variables were not used by the project:

    THIRDPARTY


---
--- stderr: rosidl_core_generators
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: rosidl_core_runtime
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_SHARED_LIBS
    CMAKE_POSITION_INDEPENDENT_CODE
    THIRDPARTY


---
--- stderr: builtin_interfaces
CMake Error at /home/paum/ros2_ws/install/rosidl_typesupport_fastrtps_c/share/rosidl_typesupport_fastrtps_c/cmake/rosidl_typesupport_fastrtps_c-extras.cmake:5 (find_package):
  Could not find a configuration file for package "fastcdr" that is
  compatible with requested version "2".

  The following configuration files were considered but not accepted:

    /home/paum/ros2_ws/install/fastcdr/lib/cmake/fastcdr/fastcdr-config.cmake, version: 2.2.7 (64bit)

Call Stack (most recent call first):
  /home/paum/ros2_ws/install/rosidl_typesupport_fastrtps_c/share/rosidl_typesupport_fastrtps_c/cmake/rosidl_typesupport_fastrtps_cConfig.cmake:41 (include)
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/install/share/rosidl_typesupport_c/cmake/rosidl_typesupport_c-extras.cmake:13 (find_package)
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/install/share/rosidl_typesupport_c/cmake/rosidl_typesupport_cConfig.cmake:41 (include)
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/install/share/rosidl_core_generators/cmake/rosidl_core_generators-extras.cmake:21 (find_package)
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/mcu/install/share/rosidl_core_generators/cmake/rosidl_core_generatorsConfig.cmake:41 (include)
  CMakeLists.txt:17 (find_package)


---
Failed   <<< builtin_interfaces [2.46s, exited with code 1]

============================================================================= [FAILED] Took 203.73 seconds =============================================================================

Environment    Status    Duration
-------------  --------  ------------
delay          FAILED    00:03:23.734
======================================================================== 1 failed, 0 succeeded in 00:03:23.734 ========================================================================
paum@Ubuntu24:~/NR-Internship/esp_src/pio_ws$ 
