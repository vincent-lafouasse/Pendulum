cmake_minimum_required(VERSION 3.16)

project(Pendulum VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -pedantic -fdiagnostics-color=always")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	src/main.cpp

	src/RenderingCtx.cpp
	src/RenderingCtx.hpp

	src/Timer.cpp
	src/Timer.hpp

	src/Config.hpp

	src/shapes/Sphere.hpp

	src/math/Vec2.hpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	src/
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	${SDL2_LIBRARIES}
)

