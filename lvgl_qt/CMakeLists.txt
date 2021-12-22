cmake_minimum_required(VERSION 3.10)

add_library(lvgl_qt
  LvglRenderer.cpp
  LvglRenderer.hpp
)
target_include_directories(lvgl_qt
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/external/lvgl/src
    ${PROJECT_SOURCE_DIR}/external/lvgl/examples
)
target_link_libraries(lvgl_qt
  PUBLIC
    lvgl
    lvgl_examples
    Qt${QT_VERSION_MAJOR}::Gui
)
