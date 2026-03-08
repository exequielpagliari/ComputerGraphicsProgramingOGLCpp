cmake_minimum_required(VERSION 3.6...3.14 FATAL_ERROR)
cmake_policy(VERSION 3.6...3.14)

set(PROJECT_NAME Program4-1-2)

project(${PROJECT_NAME})

file(GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable(${PROJECT_NAME} ${SOURCES} ) 


add_definitions(-DGLEW_STATIC)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Configurar clang-tidy ANTES de crear targets
find_program(CLANG_TIDY_EXE NAMES clang-tidy)

if(CLANG_TIDY_EXE)
    message(STATUS "Using clang-tidy: ${CLANG_TIDY_EXE}")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_EXE})
endif()


include(FetchContent)
FetchContent_Declare(external-glew
GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
GIT_TAG glew-cmake-2.3.1
)
FetchContent_MakeAvailable(external-glew)

FetchContent_Declare(external-glm
GIT_REPOSITORY https://github.com/g-truc/glm.git
GIT_TAG 1.0
)
FetchContent_MakeAvailable(external-glm)

FetchContent_Declare(external-glfw
GIT_REPOSITORY https://github.com/glfw/glfw.git
GIT_TAG 3.4
)
FetchContent_MakeAvailable(external-glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw glm libglew_static OpenGL::GL)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    )
	

find_package( OpenGL REQUIRED )



if(CLANG_TIDY_EXE)
    set(CMAKE_CXX_CLANG_TIDY 
        ${CLANG_TIDY_EXE} 
        --extra-arg=/EHsc 
        --extra-arg=-std=c++17
    )
endif()

add_custom_target(
    tidy
    COMMAND ${CLANG_TIDY_EXE} 
    ${SOURCES} 
	--header-filter="${CMAKE_CURRENT_SOURCE_DIR}/src/.*"
    -- 
    -x c++
    -std=c++17
    "-I${external-glew_SOURCE_DIR}/include"
    "-I${external-glfw_SOURCE_DIR}/include"
    "-I${external-glm_SOURCE_DIR}"
    "-I${CMAKE_CURRENT_SOURCE_DIR}/src"
    COMMENT "Ejecutando clang-tidy con rutas de FetchContent..."
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}>
    ${CMAKE_SOURCE_DIR}
)
     
