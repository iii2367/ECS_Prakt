cmake_minimum_required(VERSION 4.0.1)
project(ECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_COMPILE_COMMANDS_JSON ON)

add_executable(ECS_exe
    src/main.cpp 
    src/ecs/ecs_core.cpp
)

#if(CMAKE_BUILD_TYPE STREQUAL "Debug")
#    message(STATUS "Debug build")
#    add_compile_definitions(DEBUG_BUILD)
#    target_compile_options(ECS_exe PRIVATE -Wall -O0 -g)
#elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
#    message(STATUS "Release build")
#    add_compile_definitions(RELEASE_BUILD)
#    target_compile_options(ECS_exe PRIVATE -Wall -O2)
#endif()


add_definitions(-DUNICODE -D_UNICODE)

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_SOURCE_DIR}/compile_commands.json"
)
