add_subdirectory(camera)
add_subdirectory(geometry)
add_subdirectory(ui)
add_subdirectory(scene)

# Main entry file
target_sources(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/raytracer.cpp
)