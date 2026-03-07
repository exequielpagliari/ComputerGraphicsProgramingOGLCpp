cmake_minimum_required(VERSION 3.10)
project(Program4-2-2)

add_executable(Program4-2-2 main.cpp  "Utils.h" "Utils.cpp" "Transform.h" "Transform.cpp" ) # Reemplaza main.cpp con tus archivos fuente
add_definitions(-DGLEW_STATIC)

include(FetchContent)
FetchContent_Declare(external-glew
GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
GIT_TAG master
)
FetchContent_MakeAvailable(external-glew)
target_link_libraries(Program4-2-2 PRIVATE libglew_static)

include(FetchContent)
FetchContent_Declare(external-glm
GIT_REPOSITORY https://github.com/g-truc/glm.git
GIT_TAG master
)
FetchContent_MakeAvailable(external-glm)
target_link_libraries(Program4-2-2 PRIVATE glm::glm)

include(FetchContent)
FetchContent_Declare(external-glfw
GIT_REPOSITORY https://github.com/glfw/glfw.git
GIT_TAG master
)
FetchContent_MakeAvailable(external-glfw)
target_link_libraries(Program4-2-2 PRIVATE glfw)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}

    )
find_package( OpenGL REQUIRED )
     
add_custom_command(TARGET Program4-2-2 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:Program4-2-2>
    ${CMAKE_SOURCE_DIR}
)
     