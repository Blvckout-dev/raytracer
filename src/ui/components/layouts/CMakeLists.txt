target_include_directories(raytracer
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(raytracer PRIVATE
    SquareLayout.cpp
    SquareLayout.h
)