add_subdirectory(camera)
add_subdirectory(geometry)
add_subdirectory(ui)
add_subdirectory(scene)
add_subdirectory(render)

# Main entry file
target_sources(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/raytracer.cpp
)