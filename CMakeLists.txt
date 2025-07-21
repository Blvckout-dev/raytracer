cmake_minimum_required(VERSION 3.16)
project(Raytracer)

# Set C++-standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Function to add all ui subdirectories automatically to AUTOUIC search paths
function(set_autouic_search_paths_recursive base_dir)
    # Get all ui files recursively under base_dir
    file(GLOB_RECURSE ui_files RELATIVE ${base_dir} ${base_dir}/*.ui)

    set(paths "${base_dir}")
    foreach(ui_file ${ui_files})
        # Get directory part of each .ui file (relative to base_dir)
        get_filename_component(dir ${ui_file} PATH)
        list(APPEND paths "${base_dir}/${dir}")
    endforeach()

    # Remove duplicates from paths
    list(REMOVE_DUPLICATES paths)

    set(CMAKE_AUTOUIC_SEARCH_PATHS ${paths} PARENT_SCOPE)
endfunction()

set_autouic_search_paths_recursive("${CMAKE_SOURCE_DIR}/ui")

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
    WIN32_EXECUTABLE ON
)
