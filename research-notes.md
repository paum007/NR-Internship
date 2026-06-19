## Robot Hand → Herny
## Sensorised Glove → Will

The operator is the one commanding the motion. Their finger position is the input. This means that when Henry makes contact with something, the break system will stop the user from being able to move their finger. This will make it so that Henry's finger position matches Will's anyways since the user is the one that controls the fingers.

You actually don't need encoders or anything on Will since the clamp will resist you at that position. So technically the servos from Will and the servos in Henry don't need to be connected. The real calibration will be between the flex resistors on Will and the servos on Henry.

So the two directions are not symmetric, and that's the whole resolution:

- Forward (command): will bend → mapped (calibrated, because kinematics differ) → henry servo target. Angle translation lives here.
- Return (feedback): henry fingertip force → one bit (contact / no contact) → will brake locks at current position. No angle translation at all.

Start instead of doing a full build, do it so that you can test that the haptics work with using only one finger on the sensorised glove.

NEW DESIGN OF THE HAND: https://arxiv.org/pdf/2509.03690

I think it would be good to make the CAD for the servos yourself since it would be quite hard to make it without.

USE CHUNKING FOR THE ESP_NOW.
[esp_now chunking](https://www.digikey.sg/zh/maker/tutorials/2024/how-to-transmit-messages-to-unlimited-receivers-in-esp-now)

[MLX90393 DATASHEET](https://uk.store.bambulab.com/products/tpu-for-ams?id=532448685015678999)
[MLX90393 VISUALISATION](https://github.com/notvenky/eFlesh/tree/main/visualizer)

![This is what I found on the 3D printer settings for the TPU](image.png)


paum@Ubuntu24:~/NR-Internship/esp_src/pio_ws$ pio run -e delay -t upload
Processing delay (platform: espressif32; board: upesy_wroom; framework: arduino)
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Platform Manager: Installing espressif32
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Platform Manager: espressif32@7.0.1 has been installed!
Tool Manager: Installing espressif/toolchain-xtensa-esp32 @ 8.4.0+2021r2-patch5
Downloading  [####################################]  100%          
Unpacking  [####################################]  100%          
Tool Manager: toolchain-xtensa-esp32@8.4.0+2021r2-patch5 has been installed!
Tool Manager: Installing platformio/framework-arduinoespressif32 @ ~3.20017.0
Downloading  [####################################]  100%          
Unpacking  [####################################]  100%          
Tool Manager: framework-arduinoespressif32@3.20017.241212+sha.dcc1105b has been installed!
Tool Manager: Installing platformio/tool-esptoolpy @ ~2.41100.0
Downloading  [####################################]  100%          
Unpacking  [####################################]  100%
WARNING: Skipping /usr/lib/python3/dist-packages/pytest_repeat.egg-info due to invalid metadata entry 'name'
Collecting cryptography~=45.0.3
  Downloading cryptography-45.0.7-cp311-abi3-manylinux_2_34_x86_64.whl.metadata (5.7 kB)
Collecting ecdsa~=0.19.1
  Downloading ecdsa-0.19.2-py2.py3-none-any.whl.metadata (29 kB)
Collecting bitstring~=4.3.1
  Downloading bitstring-4.3.1-py3-none-any.whl.metadata (5.3 kB)
Collecting reedsolo~=1.7.0
  Downloading reedsolo-1.7.0-py3-none-any.whl.metadata (23 kB)
Collecting intelhex~=2.3.0
  Downloading intelhex-2.3.0-py2.py3-none-any.whl.metadata (2.7 kB)
Collecting cffi>=1.14 (from cryptography~=45.0.3)
  Downloading cffi-2.0.0-cp312-cp312-manylinux2014_x86_64.manylinux_2_17_x86_64.whl.metadata (2.6 kB)
Collecting six>=1.9.0 (from ecdsa~=0.19.1)
  Using cached six-1.17.0-py2.py3-none-any.whl.metadata (1.7 kB)
Collecting bitarray<4.0,>=3.0.0 (from bitstring~=4.3.1)
  Downloading bitarray-3.8.2-cp312-cp312-manylinux2014_x86_64.manylinux_2_17_x86_64.manylinux_2_28_x86_64.whl.metadata (34 kB)
Collecting pycparser (from cffi>=1.14->cryptography~=45.0.3)
  Downloading pycparser-3.0-py3-none-any.whl.metadata (8.2 kB)
Downloading cryptography-45.0.7-cp311-abi3-manylinux_2_34_x86_64.whl (4.5 MB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 4.5/4.5 MB 12.1 MB/s eta 0:00:00
Downloading ecdsa-0.19.2-py2.py3-none-any.whl (150 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 150.8/150.8 kB 14.1 MB/s eta 0:00:00
Downloading bitstring-4.3.1-py3-none-any.whl (71 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 71.9/71.9 kB 6.9 MB/s eta 0:00:00
Downloading reedsolo-1.7.0-py3-none-any.whl (32 kB)
Downloading intelhex-2.3.0-py2.py3-none-any.whl (50 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 50.9/50.9 kB 5.0 MB/s eta 0:00:00
Downloading bitarray-3.8.2-cp312-cp312-manylinux2014_x86_64.manylinux_2_17_x86_64.manylinux_2_28_x86_64.whl (343 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 344.0/344.0 kB 14.9 MB/s eta 0:00:00
Downloading cffi-2.0.0-cp312-cp312-manylinux2014_x86_64.manylinux_2_17_x86_64.whl (219 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 219.6/219.6 kB 18.9 MB/s eta 0:00:00
Using cached six-1.17.0-py2.py3-none-any.whl (11 kB)
Downloading pycparser-3.0-py3-none-any.whl (48 kB)
   ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━ 48.2/48.2 kB 7.7 MB/s eta 0:00:00
WARNING: Skipping /usr/lib/python3/dist-packages/pytest_repeat.egg-info due to invalid metadata entry 'name'
Installing collected packages: reedsolo, intelhex, bitarray, six, pycparser, bitstring, ecdsa, cffi, cryptography
Successfully installed bitarray-3.8.2 bitstring-4.3.1 cffi-2.0.0 cryptography-45.0.7 ecdsa-0.19.2 intelhex-2.3.0 pycparser-3.0 reedsolo-1.7.0 six-1.17.0
Tool Manager: tool-esptoolpy@2.41100.0 has been installed!
Tool Manager: Installing platformio/tool-mkspiffs @ ~2.230.0
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Tool Manager: tool-mkspiffs@2.230.0 has been installed!
Tool Manager: Installing platformio/tool-mklittlefs @ ~1.203.0
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Tool Manager: tool-mklittlefs@1.203.210628 has been installed!
Tool Manager: Installing platformio/tool-mkfatfs @ ~2.0.0
Downloading  [####################################]  100%
Unpacking  [####################################]  100%
Tool Manager: tool-mkfatfs@2.0.1 has been installed!
Tool Manager: Installing platformio/tool-scons @ ~4.40801.0
Downloading  [####################################]  100%          
Unpacking  [####################################]  100%
Tool Manager: tool-scons@4.40801.0 has been installed!
Library Manager: Installing git+https://github.com/micro-ROS/micro_ros_platformio
git version 2.43.0
Cloning into '/home/paum/.platformio/.cache/tmp/pkg-installing-nieig8er'...
remote: Enumerating objects: 77, done.
remote: Counting objects: 100% (77/77), done.
remote: Compressing objects: 100% (62/62), done.
remote: Total 77 (delta 12), reused 38 (delta 4), pack-reused 0 (from 0)
Receiving objects: 100% (77/77), 132.22 KiB | 2.54 MiB/s, done.
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
Configuring upesy_wroom with transport serial
Downloading micro-ROS dev dependencies
	 - Downloaded ament_cmake
	 - Downloaded ament_lint
	 - Downloaded ament_package
	 - Downloaded googletest
	 - Downloaded ament_cmake_ros
	 - Downloaded ament_index
Building micro-ROS dev dependencies
Build dev micro-ROS environment failed: 
 [0.926s] WARNING:colcon.colcon_core.package_selection:Some selected packages are already built in one or more underlay workspaces:
	'ament_cmake_ros' is in: /home/paum/ros2_ws/install/ament_cmake_ros
	'ament_cmake_gtest' is in: /home/paum/ros2_ws/install/ament_cmake_gtest
	'ament_cmake_xmllint' is in: /home/paum/ros2_ws/install/ament_cmake_xmllint
	'ament_cmake_uncrustify' is in: /home/paum/ros2_ws/install/ament_cmake_uncrustify
	'ament_cmake_google_benchmark' is in: /home/paum/ros2_ws/install/ament_cmake_google_benchmark
	'ament_cmake_pep257' is in: /home/paum/ros2_ws/install/ament_cmake_pep257
	'ament_cmake_core' is in: /home/paum/ros2_ws/install/ament_cmake_core
	'ament_index_cpp' is in: /home/paum/ros2_ws/install/ament_index_cpp
	'ament_copyright' is in: /home/paum/ros2_ws/install/ament_copyright
	'ament_lint_auto' is in: /home/paum/ros2_ws/install/ament_lint_auto
	'ament_cmake' is in: /home/paum/ros2_ws/install/ament_cmake
	'ament_cmake_test' is in: /home/paum/ros2_ws/install/ament_cmake_test
	'ament_cmake_cppcheck' is in: /home/paum/ros2_ws/install/ament_cmake_cppcheck
	'ament_index_python' is in: /home/paum/ros2_ws/install/ament_index_python
	'ament_cmake_mypy' is in: /home/paum/ros2_ws/install/ament_cmake_mypy
	'ament_cmake_pytest' is in: /home/paum/ros2_ws/install/ament_cmake_pytest
	'ament_cmake_copyright' is in: /home/paum/ros2_ws/install/ament_cmake_copyright
	'ament_cmake_lint_cmake' is in: /home/paum/ros2_ws/install/ament_cmake_lint_cmake
	'ament_cmake_cpplint' is in: /home/paum/ros2_ws/install/ament_cmake_cpplint
	'ament_cmake_clang_format' is in: /home/paum/ros2_ws/install/ament_cmake_clang_format
	'ament_cmake_flake8' is in: /home/paum/ros2_ws/install/ament_cmake_flake8
	'ament_lint_common' is in: /home/paum/ros2_ws/install/ament_lint_common
	'ament_cmake_gmock' is in: /home/paum/ros2_ws/install/ament_cmake_gmock
	'domain_coordinator' is in: /home/paum/ros2_ws/install/domain_coordinator
If a package in a merged underlay workspace is overridden and it installs headers, then all packages in the overlay must sort their include directories by workspace order. Failure to do so may result in build failures or undefined behavior at run time.
If the overridden package is used by another package in any underlay, then the overriding package in the overlay must be API and ABI compatible or undefined behavior at run time may occur.

If you understand the risks and want to override a package anyways, add the following to the command line:
	--allow-overriding ament_cmake ament_cmake_clang_format ament_cmake_copyright ament_cmake_core ament_cmake_cppcheck ament_cmake_cpplint ament_cmake_flake8 ament_cmake_gmock ament_cmake_google_benchmark ament_cmake_gtest ament_cmake_lint_cmake ament_cmake_mypy ament_cmake_pep257 ament_cmake_pytest ament_cmake_ros ament_cmake_test ament_cmake_uncrustify ament_cmake_xmllint ament_copyright ament_index_cpp ament_index_python ament_lint_auto ament_lint_common domain_coordinator

This may be promoted to an error in a future release of colcon-override-check.
--- stderr: gtest_vendor
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_TESTING
    Python3_EXECUTABLE


---
--- stderr: gmock_vendor
CMake Warning:
  Manually-specified variables were not used by the project:

    BUILD_TESTING
    Python3_EXECUTABLE


---
--- stderr: ament_cmake_core
Traceback (most recent call last):
  File "/home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/dev/src/ament_cmake/ament_cmake_core/cmake/core/package_xml_2_cmake.py", line 22, in <module>
    from catkin_pkg.package import parse_package_string
ModuleNotFoundError: No module named 'catkin_pkg'
CMake Error at cmake/core/ament_package_xml.cmake:95 (message):
  execute_process(/home/paum/.platformio/penv/bin/python
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/dev/src/ament_cmake/ament_cmake_core/cmake/core/package_xml_2_cmake.py
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/dev/src/ament_cmake/ament_cmake_core/package.xml
  /home/paum/NR-Internship/esp_src/pio_ws/.pio/libdeps/delay/micro_ros_platformio/build/dev/build/ament_cmake_core/ament_cmake_core/package.cmake)
  returned error code 1
Call Stack (most recent call first):
  cmake/core/ament_package_xml.cmake:49 (_ament_package_xml)
  CMakeLists.txt:15 (ament_package_xml)


---
Failed   <<< ament_cmake_core [2.47s, exited with code 1]

============================================================================= [FAILED] Took 345.92 seconds =============================================================================

Environment    Status    Duration
-------------  --------  ------------
delay          FAILED    00:05:45.921
======================================================================== 1 failed, 0 succeeded in 00:05:45.921 ========================================================================
paum@Ubuntu24:~/NR-Internship/esp_src/pio_ws$ 

