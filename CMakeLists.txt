cmake_minimum_required(VERSION 3.12)
project(Raytracer)

# Set C++-standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include folder
include_directories(include)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/**/*.cpp")

# Create executable
add_executable(raytracer ${SOURCES})

# Output directory for each configuration
set_target_properties(raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/Release"
)