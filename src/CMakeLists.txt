add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
		main.cpp

		World.cpp
		World.hpp

		Renderer.cpp
		Renderer.hpp

		Timer.cpp
		Timer.hpp

		Config.hpp
		Viewport.hpp

		shapes/Sphere.hpp

		math/math.hpp
		math/Vec2.cpp
		math/Vec2_arithmetic.cpp
		math/Vec2.hpp
		math/float_equal.cpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	./
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	${SDL2_LIBRARIES}
)
