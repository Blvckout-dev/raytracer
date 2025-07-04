cmake_minimum_required(VERSION 3.16)
project(Raytracer)

# Set C++-standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/raytracer)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Create executable
add_executable(raytracer)

# Add main application sources (in src/raytracer)
add_subdirectory(src/raytracer)

# Include headers
target_include_directories(raytracer
    PRIVATE
        ${PROJECT_INCLUDE_DIR}
)

# Compile definitions (e.g., M_PI)
target_compile_definitions(raytracer PRIVATE _USE_MATH_DEFINES)

# Link qt widget  
target_link_libraries(raytracer PRIVATE Qt6::Widgets)

# Output directory for each configuration
set_target_properties(raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/Release"
)