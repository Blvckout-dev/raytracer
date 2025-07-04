add_subdirectory(camera)
add_subdirectory(geometry)

# Main entry file
target_sources(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/raytracer.cpp
)