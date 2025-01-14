cmake_minimum_required(VERSION 3.15)
project(Orpheus_Engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Platform-specific definitions
if(WIN32)
    add_definitions(-DPLATFORM_WINDOWS)
elseif(APPLE)
    add_definitions(-DPLATFORM_MACOS)
elseif(UNIX)
    add_definitions(-DPLATFORM_LINUX)
endif()

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

# Add source files
add_executable(Orpheus_Engine
    src/main.cpp
    src/EntityManager.cpp
    src/WindowManager.cpp
    src/PhysicsSystem.cpp
    src/SpawningSystem.cpp
    src/InputSystem.cpp
    src/DebugSystem.cpp
    src/RenderingSystem.cpp
)

# Link SDL2 libraries
target_link_libraries(Orpheus_Engine ${SDL2_LIBRARIES})

# Specify include directories
target_include_directories(Orpheus_Engine PRIVATE include/)

# Compiler-specific options
if(MSVC)
    target_compile_options(Orpheus_Engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(Orpheus_Engine PRIVATE -Wall -Wextra -pedantic)
endif()