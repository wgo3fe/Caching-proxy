cmake_minimum_required(VERSION 3.10)

# Project name
project(caching-proxy)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type
set(CMAKE_BUILD_TYPE Debug)

# Find Boost libraries
find_package(Boost REQUIRED COMPONENTS system program_options)

# Set the global output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable
add_executable(caching-proxy 
    src/main.cpp
    src/CacheHandler.cpp
    #src/RequestHandler.cpp
)

# Link Boost libraries
target_link_libraries(caching-proxy Boost::system Boost::program_options)