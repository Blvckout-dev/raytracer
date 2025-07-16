add_subdirectory(style)
add_subdirectory(components)
add_subdirectory(viewport)
add_subdirectory(menu)

set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/MainWindow.ui
)

target_sources(raytracer PRIVATE
    MainWindow.cpp
    MainWindow.h
    ${UI_FILES}
)