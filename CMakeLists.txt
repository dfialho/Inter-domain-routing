cmake_minimum_required(VERSION 3.3)
project(Inter_domain_routing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES
        src/Node.h
        src/Network.cpp src/Network.h
        src/NetworkIdGenerator.cpp src/NetworkIdGenerator.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(Inter_domain_routing ${SOURCE_FILES} src/main.cpp)
add_executable(Test ${SOURCE_FILES} tests/network.cpp)