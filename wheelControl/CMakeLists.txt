cmake_minimum_required(VERSION 1.0)
project(test_demo) # project name
set(CMAKE_BUILD_TYPE Debug)
# add header file path
include_directories(.)
# add sources path
set(SOURCES test.cpp wheelControl.cpp)
# file(GLOB SOURCE "src/*.cpp")
# build target
add_executable(test_demo ${SOURCES})
