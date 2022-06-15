# Install script for directory: /home/misys/keyBoardControl

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/misys/keyBoardControl/install/keyboardcontrol")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol" TYPE EXECUTABLE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/getKeyBoard")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard"
         OLD_RPATH "/home/misys/ros2_galactic/install/rclcpp/lib:/home/misys/ros2_galactic/install/ament_index_cpp/lib:/home/misys/ros2_galactic/install/libstatistics_collector/lib:/home/misys/ros2_galactic/install/std_msgs/lib:/home/misys/ros2_galactic/install/rcl/lib:/home/misys/ros2_galactic/install/rcl_interfaces/lib:/home/misys/ros2_galactic/install/rmw_implementation/lib:/home/misys/ros2_galactic/install/rcl_logging_spdlog/lib:/home/misys/ros2_galactic/install/rcl_logging_interface/lib:/home/misys/ros2_galactic/install/rcl_yaml_param_parser/lib:/home/misys/ros2_galactic/install/rmw/lib:/home/misys/ros2_galactic/install/libyaml_vendor/lib:/home/misys/ros2_galactic/install/rosgraph_msgs/lib:/home/misys/ros2_galactic/install/statistics_msgs/lib:/home/misys/ros2_galactic/install/builtin_interfaces/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_c/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_c/lib:/home/misys/ros2_galactic/install/rcpputils/lib:/home/misys/ros2_galactic/install/rosidl_runtime_c/lib:/home/misys/ros2_galactic/install/rcutils/lib:/home/misys/ros2_galactic/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol" TYPE EXECUTABLE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/getKeyBoard")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard"
         OLD_RPATH "/home/misys/ros2_galactic/install/rclcpp/lib:/home/misys/ros2_galactic/install/ament_index_cpp/lib:/home/misys/ros2_galactic/install/libstatistics_collector/lib:/home/misys/ros2_galactic/install/std_msgs/lib:/home/misys/ros2_galactic/install/rcl/lib:/home/misys/ros2_galactic/install/rcl_interfaces/lib:/home/misys/ros2_galactic/install/rmw_implementation/lib:/home/misys/ros2_galactic/install/rcl_logging_spdlog/lib:/home/misys/ros2_galactic/install/rcl_logging_interface/lib:/home/misys/ros2_galactic/install/rcl_yaml_param_parser/lib:/home/misys/ros2_galactic/install/rmw/lib:/home/misys/ros2_galactic/install/libyaml_vendor/lib:/home/misys/ros2_galactic/install/rosgraph_msgs/lib:/home/misys/ros2_galactic/install/statistics_msgs/lib:/home/misys/ros2_galactic/install/builtin_interfaces/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_c/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_c/lib:/home/misys/ros2_galactic/install/rcpputils/lib:/home/misys/ros2_galactic/install/rosidl_runtime_c/lib:/home/misys/ros2_galactic/install/rcutils/lib:/home/misys/ros2_galactic/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/getKeyBoard")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol" TYPE EXECUTABLE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/testKeyBoard")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard"
         OLD_RPATH "/home/misys/ros2_galactic/install/rclcpp/lib:/home/misys/ros2_galactic/install/ament_index_cpp/lib:/home/misys/ros2_galactic/install/libstatistics_collector/lib:/home/misys/ros2_galactic/install/std_msgs/lib:/home/misys/ros2_galactic/install/rcl/lib:/home/misys/ros2_galactic/install/rcl_interfaces/lib:/home/misys/ros2_galactic/install/rmw_implementation/lib:/home/misys/ros2_galactic/install/rcl_logging_spdlog/lib:/home/misys/ros2_galactic/install/rcl_logging_interface/lib:/home/misys/ros2_galactic/install/rcl_yaml_param_parser/lib:/home/misys/ros2_galactic/install/rmw/lib:/home/misys/ros2_galactic/install/libyaml_vendor/lib:/home/misys/ros2_galactic/install/rosgraph_msgs/lib:/home/misys/ros2_galactic/install/statistics_msgs/lib:/home/misys/ros2_galactic/install/builtin_interfaces/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_introspection_c/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_cpp/lib:/home/misys/ros2_galactic/install/rosidl_typesupport_c/lib:/home/misys/ros2_galactic/install/rcpputils/lib:/home/misys/ros2_galactic/install/rosidl_runtime_c/lib:/home/misys/ros2_galactic/install/rcutils/lib:/home/misys/ros2_galactic/install/tracetools/lib:"
         NEW_RPATH "")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/keyboardcontrol/testKeyBoard")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/package_run_dependencies" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_index/share/ament_index/resource_index/package_run_dependencies/keyboardcontrol")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/parent_prefix_path" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_index/share/ament_index/resource_index/parent_prefix_path/keyboardcontrol")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol/environment" TYPE FILE FILES "/home/misys/ros2_galactic/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/ament_prefix_path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol/environment" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/ament_prefix_path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol/environment" TYPE FILE FILES "/home/misys/ros2_galactic/install/ament_cmake_core/share/ament_cmake_core/cmake/environment_hooks/environment/path.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol/environment" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/path.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/local_setup.bash")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/local_setup.sh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/local_setup.zsh")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/local_setup.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_environment_hooks/package.dsv")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ament_index/resource_index/packages" TYPE FILE FILES "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_index/share/ament_index/resource_index/packages/keyboardcontrol")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol/cmake" TYPE FILE FILES
    "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_core/keyboardcontrolConfig.cmake"
    "/home/misys/keyBoardControl/build/keyboardcontrol/ament_cmake_core/keyboardcontrolConfig-version.cmake"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/keyboardcontrol" TYPE FILE FILES "/home/misys/keyBoardControl/package.xml")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/home/misys/keyBoardControl/build/keyboardcontrol/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
