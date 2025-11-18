
cmake_minimum_required(VERSION 3.15...3.27)

project(tower-defense-cli VERSION 0.1.0 LANGUAGES C CXX)

# Check if compilers are available
if(WIN32)
    set(CMAKE_C_COMPILER "C:/msys64/ucrt64/bin/gcc.exe")
    set(CMAKE_CXX_COMPILER "C:/msys64/ucrt64/bin/g++.exe")
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories for source code
include_directories(src)

# Add source files for the main executable
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.h)
add_executable(tower-defense-cli ${SOURCE_FILES})

# Platform-specific configurations
if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    message(STATUS "Configuring for macOS")
    if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm64")
        message(STATUS "Building for Apple Silicon (arm64)")
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
        message(STATUS "Building for Intel (x86_64)")
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
endif()

# Enable testing
enable_testing()

# Add test executable
add_executable(tower-defense-cli-test src/tests.cpp ${SOURCE_FILES})
target_compile_definitions(tower-defense-cli-test PRIVATE RUNNING_TESTS)

add_test(NAME TowerDefenseTest
         COMMAND tower-defense-cli-test
         WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
