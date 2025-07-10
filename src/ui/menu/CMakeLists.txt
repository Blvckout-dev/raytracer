set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/menu/Menu.ui
)

target_sources(raytracer PRIVATE
    Menu.cpp
    Menu.h
    ${UI_FILES}
)