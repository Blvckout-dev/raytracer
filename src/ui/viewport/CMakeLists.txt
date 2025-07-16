set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/viewport/Viewport.ui
)

target_sources(raytracer PRIVATE
    Viewport.cpp
    Viewport.h
    ${UI_FILES}
)