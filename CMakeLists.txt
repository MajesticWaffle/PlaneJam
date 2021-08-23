cmake_minimum_required(VERSION 3.21)
project(Planejam)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

find_package(OpenGL REQUIRED)
add_executable(Planejam planejam.h planejam_main.cpp planejam.h planejam_rendering.cpp planejam_input.cpp playerjam_time.cpp planejam_texture.cpp)
target_link_libraries(Planejam -lGLEW -lglfw -lGL)