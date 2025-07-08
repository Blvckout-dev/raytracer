set(UI_FILES
    ${CMAKE_SOURCE_DIR}/ui/mainwindow.ui
)

target_sources(raytracer PRIVATE
    MainWindow.cpp
    MainWindow.h
    ${UI_FILES}
)