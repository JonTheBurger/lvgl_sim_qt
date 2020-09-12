cmake_minimum_required(VERSION 3.10)

add_executable(lvgl_qt_quick
  LvglImageProvider.cpp
  LvglImageProvider.hpp
  main.cpp
  qml.qrc
)
target_include_directories(lvgl_qt_quick
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(lvgl_qt_quick
  PRIVATE
    lvgl_qt
    Qt${QT_VERSION_MAJOR}::Quick
)
target_compile_definitions(lvgl_qt_quick
  PRIVATE
    $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>
)
