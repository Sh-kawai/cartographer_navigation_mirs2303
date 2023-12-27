cmake_minimum_required(VERSION 3.0.2)
project(cartographer_navigation_mirs2303)

find_package(catkin REQUIRED
  rospy
  roscpp
  roslib
  move_base
  actionlib
  cartographer_ros
  geometry_msgs
  rospy
  sensor_msgs
  std_msgs
  std_srvs
  tf
  nav_msgs # add
)

find_package(cartographer REQUIRED)
include("${CARTOGRAPHER_CMAKE_DIR}/functions.cmake")

catkin_package(
#  INCLUDE_DIRS include
  LIBRARIES cartgrapher_navigation
  CATKIN_DEPENDS actionlib geometry_msgs move_base rospy roscpp tf std_msgs nav_msgs
  DEPENDS system_lib
)

install(DIRECTORY launch configuration_files param urdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

# header files
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  FILES_MATCHING PATTERN "*.h"
)

# add
catkin_package(
  CATKIN_DEPENDS nav_msgs tf
  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

# add_executable(simple_odom_generator_node src/simple_odom_generator.cpp)

# target_link_libraries(sample_odom_generator_node
#    ${catkin_LIBRARIES}
# )