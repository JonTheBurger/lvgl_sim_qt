cmake_minimum_required(VERSION 3.10)

add_executable(lvgl_qt_widgets
  main.cpp
  LvglGraphicsView.cpp
  LvglGraphicsView.hpp
  MainWindow.cpp
  MainWindow.hpp
  MainWindow.ui
)
target_include_directories(lvgl_qt_widgets
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(lvgl_qt_widgets
  PRIVATE
    lvgl::demos
    lvgl_qt
    Qt::Widgets
)
