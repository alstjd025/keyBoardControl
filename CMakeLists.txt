cmake_minimum_required(VERSION 3.8)
project(keyboardcontrol)

set(LIBCURSES /usr/lib/x86_64-linux-gnu/libcurses.so)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic -pthread)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED) 
find_package(ichthus_msgs REQUIRED)

# uncomment the following section in order to fill in
# further dependencies manually.
# find_package(<dependency> REQUIRED)

include_directories(include)

add_executable(getKeyBoard src/getKeyBoardInputnode.cc)
ament_target_dependencies(getKeyBoard rclcpp std_msgs ichthus_msgs)

add_executable(testKeyBoard src/testKeyBoardInputnode.cc)
ament_target_dependencies(testKeyBoard rclcpp std_msgs ichthus_msgs)


target_link_libraries(getKeyBoard dl ${LIBCURSES})

target_link_libraries(testKeyBoard dl ${LIBCURSES})

install(TARGETS
  getKeyBoard
  DESTINATION lib/${PROJECT_NAME})

install(TARGETS
  getKeyBoard
  testKeyBoard
  DESTINATION lib/${PROJECT_NAME})

ament_package()
