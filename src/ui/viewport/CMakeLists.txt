set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/viewport/ViewportWidget.ui
)

target_sources(raytracer PRIVATE
    ViewportWidget.cpp
    ViewportWidget.h
    ${UI_FILES}
)