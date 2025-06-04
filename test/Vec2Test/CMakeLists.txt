set(testedSourceDir ${CMAKE_SOURCE_DIR}/src)

add_executable(Vec2Test)
target_sources(Vec2Test
PRIVATE
	./main.cpp
	./Vec2Test.cpp

	${testedSourceDir}/Vec2.hpp
)

target_include_directories(Vec2Test
PUBLIC
	./
	${testedSourceDir}
)

target_link_libraries(Vec2Test
PRIVATE
	gtest
	raylib
)
