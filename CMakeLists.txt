cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(observer)

set(SRC main.cpp
)
add_definitions(-DTEST)
add_executable(${CMAKE_PROJECT_NAME} ${SRC})