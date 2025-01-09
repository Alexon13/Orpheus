cmake_minimum_required(VERSION 3.10)
project(Orpheus)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)

# Include SDL2 headers
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(Orpheus src/main.cpp)

# Link SDL2 libraries
target_link_libraries(Orpheus ${SDL2_LIBRARIES})