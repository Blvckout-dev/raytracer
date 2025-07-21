set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/menu/MenuWidget.ui
)

target_sources(raytracer PRIVATE
    MenuWidget.cpp
    MenuWidget.h
    ${UI_FILES}
)