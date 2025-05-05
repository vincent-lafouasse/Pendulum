add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
PRIVATE
	main.cpp

	RenderingCtx.cpp
	RenderingCtx.hpp

	Timer.cpp
	Timer.hpp

	Config.hpp

	shapes/Sphere.hpp

	math/Vec2.cpp
	math/Vec2_arithmetic.cpp
	math/Vec2.hpp
)

target_include_directories(${PROJECT_NAME}
PUBLIC
	./
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
	${SDL2_LIBRARIES}
)
