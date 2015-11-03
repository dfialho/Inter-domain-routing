cmake_minimum_required(VERSION 3.3)
project(Inter_domain_routing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    src/main.cpp)

add_executable(Inter_domain_routing ${SOURCE_FILES})