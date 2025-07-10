cmake_minimum_required(VERSION 3.16)
project(Raytracer)

# Set C++-standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
list(APPEND CMAKE_AUTOUIC_SEARCH_PATHS "${CMAKE_CURRENT_SOURCE_DIR}/ui/menu")
set(CMAKE_AUTORCC ON)

# Find Qt packages
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Define include directory variable
set(RAYTRACER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

# Create executable
add_executable(raytracer)

# Add main application sources
add_subdirectory(src)

# Include headers
target_include_directories(raytracer
    PRIVATE
        ${RAYTRACER_INCLUDE_DIR}
)

# Compile definitions (e.g., M_PI)
target_compile_definitions(raytracer PRIVATE _USE_MATH_DEFINES)

# Recursively grab headers for IDE visibility
file(GLOB_RECURSE PROJECT_HEADERS
    CONFIGURE_DEPENDS
    ${RAYTRACER_INCLUDE_DIR}/*.h
)
target_sources(raytracer PRIVATE ${PROJECT_HEADERS})

# Link Qt libraries 
target_link_libraries(raytracer PRIVATE Qt6::Widgets)

# Set output directories per build configuration
set_target_properties(raytracer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_SOURCE_DIR}/bin/Debug"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_SOURCE_DIR}/bin/Release"
)