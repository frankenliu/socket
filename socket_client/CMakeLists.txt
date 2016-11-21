cmake_minimum_required(VERSION 2.8)
project(socket_client)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(inc)

set(SOURCE_FILES
        src/ClientSocket.cpp
        src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})