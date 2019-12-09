cmake_minimum_required(VERSION 3.8)
project(graph)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -Wpedantic")

include_directories(${SOURCE_DIR})
include_directories(${SOURCE_DIR}/matrix_graph/)

set(LIB_GRAPH
    ${SOURCE_DIR}/matrix_graph/matrix_graph.cpp
)

add_library(_graph STATIC ${LIB_GRAPH})

add_executable(test.out ${SOURCE_DIR}/test.cpp)
target_link_libraries(test.out _graph)
