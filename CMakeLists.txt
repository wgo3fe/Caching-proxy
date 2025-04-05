cmake_minimum_required(VERSION 3.10)

# Project name
project(CachingProxy)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the global output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add the executable
add_executable(CachingProxy src/main.cpp)