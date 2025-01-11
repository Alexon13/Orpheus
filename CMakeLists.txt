cmake_minimum_required(VERSION 3.10)
project(OrpheusEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Add source files
add_executable(OrpheusEngine
    src/main.cpp
    src/EntityManager.cpp
    src/PhysicsSystem.cpp
    src/SpawningSystem.cpp
    src/InputSystem.cpp
    src/DebugSystem.cpp
    src/RenderingSystem.cpp
)

# Link SDL2 libraries
target_link_libraries(OrpheusEngine ${SDL2_LIBRARIES})

# Specify include directories
target_include_directories(OrpheusEngine PRIVATE include/)