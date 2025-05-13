cmake_minimum_required(VERSION 3.10.2)

project(tutorial_03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(behaviortree_cpp REQUIRED)

add_executable(${PROJECT_NAME} "ports_bt")
target_link_libraries(${PROJECT_NAME} behaviortree_cpp::behaviortree_cpp)