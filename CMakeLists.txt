cmake_minimum_required(VERSION 3.3)
project(PA2_INT)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Point.cpp Point.h Cluster.cpp Cluster.h points.txt KMeans.cpp KMeans.h)
add_executable(PA2_INT ${SOURCE_FILES})