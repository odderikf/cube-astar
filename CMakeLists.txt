cmake_minimum_required(VERSION 3.10)
project(cubing)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)

include_directories(inc/algdat)
add_executable(cubing src/main.cpp src/cube.cpp src/astar_s.cpp src/graph.cpp)

target_compile_options(cubing PRIVATE -Wall -Wextra -pedantic -Werror -Wno-reorder -Wno-unused)

target_link_libraries(cubing opengl32 gdi32 glfw3dll glew32)