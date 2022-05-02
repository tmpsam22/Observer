cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)

project(observer)
set (CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE
     ${CURRENT_DIR}/src/main.cpp
     ${CURRENT_DIR}/src/subject.cpp
     ${CURRENT_DIR}/src/custom_file.cpp
     ${CURRENT_DIR}/src/file_observer.cpp
)
add_definitions(-DTEST)
include_directories(${CMAKE_PROJECT_NAME} ${CURRENT_DIR}/include)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})