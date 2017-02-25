cmake_minimum_required(VERSION 3.6)
project(progbase2GH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -coverage")

set(SOURCE_FILES main.c)
add_executable(progbase2GH ${SOURCE_FILES})