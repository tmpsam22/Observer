cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 17)

project(observer)

set(SRC main.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})