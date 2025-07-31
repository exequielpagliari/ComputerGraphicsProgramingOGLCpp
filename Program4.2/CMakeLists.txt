cmake_minimum_required(VERSION 3.10)
project(Program2-1)

add_executable(Program2-1 main.cpp  "Utils.h" "Utils.cpp" "Transform.h" "Transform.cpp" ) # Reemplaza main.cpp con tus archivos fuente
add_definitions(-DGLEW_STATIC)
add_subdirectory(lib/glfw EXCLUDE_FROM_ALL)
add_subdirectory(lib/glew EXCLUDE_FROM_ALL)
add_subdirectory(lib/glm EXCLUDE_FROM_ALL)

target_link_libraries(Program2-1
  PRIVATE glfw
  PRIVATE libglew_static
  PRIVATE glm
)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}

    )
find_package( OpenGL REQUIRED )
     
