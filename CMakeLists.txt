cmake_minimum_required(VERSION 3.16)

project(Pendulum VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	src/main.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	src/
)
