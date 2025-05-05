cmake_minimum_required(VERSION 3.16)

project(Pendulum VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src)

include(cmake/fetch_gtest.cmake)
add_subdirectory(test)

include(CTest)
enable_testing()

add_test(NAME Vec2Test
         COMMAND Vec2Test
)
