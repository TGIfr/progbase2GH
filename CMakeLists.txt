cmake_minimum_required(VERSION 3.6)
project(progbase2GH)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99 -coverage")
set(HEADER check.h)

set(SOURCE_FILES tests.c csv.c csv.h list.c list.h)
add_executable(progbase2GH ${SOURCE_FILES})
target_link_libraries(progbase2GH check )