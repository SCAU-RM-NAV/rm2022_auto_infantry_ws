project(roborts_msgs)
cmake_minimum_required(VERSION 3.1)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR})
find_package(catkin REQUIRED COMPONENTS
        std_msgs
        nav_msgs
        geometry_msgs
        message_generation
        )


# message
add_message_files(
        DIRECTORY msg
        FILES
  GimbalFdb.msg
  GimbalCtrl.msg
  GameStatus.msg
  EnemyInfo.msg
  EnemyLocate.msg
)

# dependencies
generate_messages(
        DEPENDENCIES
        std_msgs
        geometry_msgs
        nav_msgs
)

catkin_package(CATKIN_DEPENDS std_msgs geometry_msgs nav_msgs message_runtime)
