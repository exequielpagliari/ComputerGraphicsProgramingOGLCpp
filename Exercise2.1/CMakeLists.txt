cmake_minimum_required(VERSION 3.10)
project(Program2-1)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)


add_executable(Program2-1 main.cpp)
target_link_libraries(Program2-1 PRIVATE glfw GLEW::GLEW OpenGL::GL)
