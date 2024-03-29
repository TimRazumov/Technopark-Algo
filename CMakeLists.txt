cmake_minimum_required(VERSION 3.8)
project(...)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "--coverage")
set(CMAKE_C_FLAGS "--coverage")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -std=c++0x -Wall -Wextra -Werror -Wpedantic")

include_directories(${SOURCE_DIR})

set(LIB_...
    ${SOURCE_DIR}/
)

add_library(_... STATIC ${LIB_GRAPH})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test.out ${SOURCE_DIR}/test.cpp)
target_link_libraries(test.out _...)
target_link_libraries(test.out ${GTEST_LIBRARIES})
target_link_libraries(test.out pthread)
