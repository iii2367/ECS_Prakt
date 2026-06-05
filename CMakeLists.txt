cmake_minimum_required(VERSION 4.0.1)
project(ECS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_COMPILE_COMMANDS_JSON ON)

add_executable(ECS_exe
    src/main.cpp 
    src/ecs/core/ECSCore.cpp
    src/ecs/systems/SystemManager.cpp
    src/ecs/systems/system_movement/SystemMovement.cpp
    src/ecs/systems/system_combat/SystemCombat.cpp
    src/ecs/io/ECSIO.cpp
)

target_include_directories(ECS_exe PRIVATE
    libs/nlohmann/single_include/nlohmann/
)

add_definitions(-DUNICODE -D_UNICODE)

add_custom_target(copy_compile_commands ALL
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_BINARY_DIR}/compile_commands.json"
    "${CMAKE_SOURCE_DIR}/compile_commands.json"
)
