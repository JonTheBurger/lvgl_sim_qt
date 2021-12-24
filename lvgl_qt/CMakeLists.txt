cmake_minimum_required(VERSION 3.10)

add_library(lvgl_qt
  LvglRenderer.cpp
  LvglRenderer.hpp
)
target_include_directories(lvgl_qt
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(lvgl_qt
  PUBLIC
    lvgl
    lvgl_examples
    lvgl::demos
    Qt::Gui
)
